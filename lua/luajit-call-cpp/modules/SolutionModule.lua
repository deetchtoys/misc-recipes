local tableUtil = require("TableModule"):new()

local solutionModule = {}

function solutionModule:new(opt)
    local obj = opt or {}
    self.__index = self
    setmetatable(obj, self)

    return obj
end

function solutionModule:bubbleSort(arrayData)

end

function solutionModule:pickSort(arrayData)

end

-- local function _permutation(arrayData, low, high)
--     local left = low + 1;
--     local right = high
--     local key = arrayData[low]

--     while (left < right) do
--         while arrayData[right] < key and right > left do
--             right = right - 1
--         end

--         while arrayData[left] > key and right > left do
--             left = left + 1
--         end

--         if left < right then
--             tableUtil:swap(arrayData, left, right)
--         end
--     end

--     tableUtil:swap(arrayData, left, low)

--     return left
-- end

-- a better implement
local function _permutation(arrayData, low, high)
    local i = low - 1;
    local key = arrayData[high]
    for j = low, high - 1, 1 do
        if arrayData[j] > key then
            i = i + 1
            tableUtil:swap(arrayData, i, j)
        end
    end

    tableUtil:swap(arrayData, i+1, high)

    return i+1
end

local function _partialArray(arrayData, low, high)
    if low < high then
        local r = _permutation(arrayData, low, high)
        _partialArray(arrayData, low, r-1)
        _partialArray(arrayData, r+1, high)
    end
end

function solutionModule:quickSort(arrayData)
    _partialArray(arrayData, 1, #arrayData)
end


local function _crossMaxRange(arrayData, low, middle, high)
    local leftMaxValue
    local leftMaxPos
    local tmpValue = 0
    for i = middle, low, -1 do
        tmpValue = tmpValue + arrayData[i]
        if not leftMaxValue then
            leftMaxValue = tmpValue
            leftMaxPos = i
        else
            if tmpValue > leftMaxValue then
                leftMaxValue = tmpValue
                leftMaxPos = i
            end
        end
    end

    local rightMaxValue
    local rightMaxPos
    tmpValue = 0
    for i = middle + 1, high, 1 do
        tmpValue = tmpValue + arrayData[i]
        if not rightMaxValue then
            rightMaxValue = tmpValue
            rightMaxPos = i
        else
            if tmpValue > rightMaxValue then
                rightMaxValue = tmpValue
                rightMaxPos = i
            end
        end
    end

    return {value = rightMaxValue + leftMaxValue,
            low = leftMaxPos,
            high = rightMaxPos,}

end

local function _findMaxRange(arrayData, low, high)
    if low == high then
        return {value = arrayData[low],
                low = low,
                high = high,}
    end

    local middle = math.floor((low + high) / 2)
    local low2Middle = _findMaxRange(arrayData, low, middle)
    local middle2High = _findMaxRange(arrayData, middle + 1, high)
    local crossMiddle = _crossMaxRange(arrayData, low, middle, high)

    if low2Middle.value >= crossMiddle.value and low2Middle.value >= middle2High.value then
        return low2Middle
    end

    if middle2High.value >= crossMiddle.value and middle2High.value >= low2Middle.value then
        return middle2High
    end

    if crossMiddle.value >= low2Middle.value and crossMiddle.value >= middle2High.value then
        return crossMiddle
    end
end

function solutionModule:findMaxRange(arrayData)
    local middle = math.floor((#arrayData+1) / 2)

    return _findMaxRange(arrayData, 1, #arrayData)
end

local function _getAllOrderSet(arrayData, start, stop)
    if start == stop then
        print(table.concat(arrayData, ","))
    else
        for i = start, stop, 1 do
            tableUtil:swap(arrayData, start, i)
            _getAllOrderSet(arrayData, start + 1,stop)
            tableUtil:swap(arrayData, i, start)
        end
    end
end

function solutionModule:getAllOrderSet(arrayData)
    _getAllOrderSet(arrayData, 1 , #arrayData)
end

local function _getAllSubSet(arrayData, start, stop, allSet)
    if start > stop then

    else
        _getAllSubSet(arrayData, start + 1, stop, allSet)
        local currentSet = {}
        table.insert(currentSet, arrayData[start])
        for _, v in pairs(allSet) do
            table.insert(currentSet, arrayData[start] .. v)
        end

        for _, v in pairs(currentSet) do
            table.insert(allSet, v)
        end
    end
end

function solutionModule:getAllSubSet(arrayData)
    local allSubSet = {}
    _getAllSubSet(arrayData, 1, #arrayData, allSubSet)

    return allSubSet
end

local function _cutRodPartial(priceItems, n)
    if n == 0 then
        return 0
    else
        local soldPrice = 0
        for i = 1, n, 1 do
            local currentPrice = priceItems[i] + _cutRodPartial(priceItems, n - i)
            if currentPrice > soldPrice then
                soldPrice = currentPrice
            end
        end

        return soldPrice
    end
end

local function _dpCutRodPartialDown(priceItems, n, buffer)
    if buffer[n] then
        return buffer[n]
    end

    if n == 0 then
        return 0
    else
        local soldPrice = 0
        for i = 1, n, 1 do
            local currentPrice = priceItems[i] + _dpCutRodPartialDown(priceItems, n - i, buffer)
            if currentPrice > soldPrice then
                soldPrice = currentPrice
            end
        end

        buffer[n] = soldPrice

        return soldPrice
    end
end

local function _dpCutRodPartialUp(priceItems, n)
    local buffer = {
        value = {},
        cutSize = {}
    }
    buffer.value[0] = 0

    for i = 1, n, 1 do
        local soldPrice = 0
        for j = 1, i, 1 do
            local currentPrice = priceItems[j] + buffer.value[i - j]
            if currentPrice > soldPrice then
                soldPrice = currentPrice
                buffer.cutSize[i] = j
            end
        end

        buffer.value[i] = soldPrice
    end

    return buffer
end

function solutionModule:cutRod(priceItems, n)
    local buffer = {}
    -- return _cutRodPartial(priceItems, n)
    -- return _dpCutRodPartialDown(priceItems, n, buffer)
    return _dpCutRodPartialUp(priceItems, n)
end

local function _getSetLCSPartialUp(leftData, rightData)
    local leftLength = #leftData
    local rightLength = #rightData
    local lcsValueArray = {
        [0] = {}
    }
    local routeBuffer = {}
    for i = 1, leftLength, 1 do
        lcsValueArray[i] = {[0] = 0}
    end

    for j = 0, rightLength, 1 do
        lcsValueArray[0][j] = 0
    end

    for i = 1, leftLength, 1 do
        routeBuffer[i] = {}
        for j = 1, rightLength, 1 do
            routeBuffer[i][j] = ""
        end
    end

    for i = 1, leftLength, 1 do
        routeBuffer[i] = {}
        for j = 1, rightLength, 1 do
            if leftData[i] == rightData[j] then
                lcsValueArray[i][j] = lcsValueArray[i-1][j-1] + 1
                routeBuffer[i][j] = "ALL"
            elseif lcsValueArray[i][j-1] > lcsValueArray[i-1][j] then
                lcsValueArray[i][j] = lcsValueArray[i][j-1]
                routeBuffer[i][j] = "LEFT"
            else
                lcsValueArray[i][j] = lcsValueArray[i-1][j]
                routeBuffer[i][j] = "UP"
            end
        end
    end

    return {lcsValueArray = lcsValueArray,
            routeBuffer = routeBuffer}
end

local function _getSetLCSPartialDown(leftData, leftIndex, rightData, rightIndex, lcsValueArray, routeBuffer)
    if leftIndex == 0 or rightIndex == 0 then
        lcsValueArray[leftIndex][rightIndex] = 0
        return 0
    else
        if lcsValueArray[leftIndex][rightIndex] then
            return lcsValueArray[leftIndex][rightIndex]
        end

        if leftData[leftIndex] == rightData[rightIndex] then
            local nums = _getSetLCSPartialDown(leftData, leftIndex - 1, rightData, rightIndex - 1, lcsValueArray, routeBuffer) + 1
            lcsValueArray[leftIndex][rightIndex] = nums
            routeBuffer[leftIndex][rightIndex] = "ALL"

            return nums
        else
            local lhs = _getSetLCSPartialDown(leftData, leftIndex, rightData, rightIndex - 1, lcsValueArray, routeBuffer)
            local rhs = _getSetLCSPartialDown(leftData, leftIndex - 1, rightData, rightIndex, lcsValueArray, routeBuffer)
            local max
            if lhs > rhs then
                max = lhs
                routeBuffer[leftIndex][rightIndex] = "LEFT"
            else
                max = rhs
                routeBuffer[leftIndex][rightIndex] = "UP"
            end

            lcsValueArray[leftIndex][rightIndex] = max

            return max
        end
    end
end

local function _printSetLCSRoute(routeBuffer, leftData, leftDataLength, rightDataLength)
    if leftDataLength == 0 or rightDataLength == 0 then
    else
        if routeBuffer[leftDataLength][rightDataLength] == "ALL" then
            _printSetLCSRoute(routeBuffer, leftData, leftDataLength - 1, rightDataLength - 1)
            print(leftDataLength, ", ", rightDataLength, "; ", leftData[leftDataLength])
        elseif routeBuffer[leftDataLength][rightDataLength] == "LEFT" then
            _printSetLCSRoute(routeBuffer, leftData, leftDataLength, rightDataLength - 1)
            -- print(leftData[leftDataLength])
        else
            _printSetLCSRoute(routeBuffer, leftData, leftDataLength - 1, rightDataLength)
            -- print(leftData[leftDataLength])
        end
    end
end

function solutionModule:getSetLCS(leftData, rightData)
    --version v1
    local lcsInfo = _getSetLCSPartialUp(leftData, rightData)
    -- print(tableUtil:dump(lcsInfo.lcsValueArray))
    -- print(tableUtil:dump(lcsInfo.routeBuffer))
    _printSetLCSRoute(lcsInfo.routeBuffer, leftData, #leftData, #rightData)

    -- version v2
    local lcsValueArray = {}
    local routeBuffer = {}
    for i = 0, #leftData, 1 do
        lcsValueArray[i] = {}
        routeBuffer[i] = {}
    end

    local size = _getSetLCSPartialDown(leftData, #leftData, rightData, #rightData, lcsValueArray, routeBuffer)
    print(size)
    _printSetLCSRoute(routeBuffer, leftData, #leftData, #rightData)
end

local function _getStringLCSUp(leftData, rightData)
    local lcsValueArray = {}
    local maxRoute = {}
    local max = 0
    for i = 0, #leftData, 1 do
        lcsValueArray[i] = {[0] = 0}
    end

    for j = 0, #rightData, 1 do
        lcsValueArray[0][j] = 0
    end

    for i = 1, #leftData, 1 do
        for j = 1, #rightData, 1 do
            if leftData[i] == rightData[j] then
                lcsValueArray[i][j] = lcsValueArray[i-1][j-1] + 1
                if lcsValueArray[i][j] > max then
                    maxRoute = {}
                    table.insert(maxRoute, {i, j})
                    max = lcsValueArray[i][j]
                elseif lcsValueArray[i][j] == max then
                    table.insert(maxRoute, {i, j})
                end
            else
                lcsValueArray[i][j] = 0
            end
        end
    end

    return {lcsValueArray = lcsValueArray,
            maxRoute = maxRoute}
end

local function _printStringLCSRoute(lcsValueArray, maxRoute, leftData)
    local maxSize
    if next(maxRoute) then
        maxSize = lcsValueArray[maxRoute[1][1]][maxRoute[1][2]]
        for _, v in pairs(maxRoute) do
            print("======================================")
            local start = v[1] - maxSize + 1
            local stop = v[1]
            for i = start, stop, 1 do
                print(leftData[i])
            end

            print("======================================")
        end
    else
        return 0
    end
end

function solutionModule:getStringLCS(leftData, rightData)
    -- version 1
    local lcsInfo = _getStringLCSUp(leftData, rightData)
    local lcsValueArray = lcsInfo.lcsValueArray
    local maxRoute = lcsInfo.maxRoute
    _printStringLCSRoute(lcsValueArray, maxRoute, leftData)

    -- version 2
end

local function _optimizedBinarySearchTreePartialUp(kChances, dChances)
    local e = {}
    local w = {}
    local root = {}
    local n = #kChances
    for i = 1, n + 1, 1 do
        e[i] = {[i-1] = dChances[i-1]}
        w[i] = {[i-1] = dChances[i-1]}
    end

    for i = 1, n, 1 do
        root[i] = {}
    end

    for l = 1, n, 1 do
        for i = 1, n - l + 1, 1 do
            j = i + l - 1
            w[i][j] = w[i][j-1] + kChances[j] + dChances[j]
            for r = i, j, 1 do
                local currentValue = w[i][j] + e[i][r-1] + e[r+1][j]
                if not e[i][j] then
                    e[i][j] = currentValue
                    root[i][j] = r
                else
                    if e[i][j] > currentValue then
                        e[i][j] = currentValue
                        root[i][j] = r
                    end
                end
            end
        end
    end

    return {e = e,
            w = w,
            root = root}
end

local function _wPartial(w, startPos, endPos, kChances, dChances)
    if endPos == startPos - 1 then
        return dChances[startPos - 1]
    else
        w[startPos][endPos] = _wPartial(w, startPos, endPos - 1, kChances, dChances) + kChances[endPos] + dChances[endPos]

        return w[startPos][endPos]
    end
end

local function _optimizedBinarySearchTreePartialDown(kChances, dChances, startPos, endPos, e, w, root)
    if startPos - 1 == endPos then
        return dChances[startPos - 1]
    else
        if not w[startPos][endPos] then
            w[startPos][endPos] = _wPartial(w, startPos, endPos, kChances, dChances)
        end

        for r = startPos, endPos, 1 do
            local currentValue = w[startPos][endPos] +
                _optimizedBinarySearchTreePartialDown(kChances, dChances, startPos, r - 1, e, w, root) +
                _optimizedBinarySearchTreePartialDown(kChances, dChances, r + 1, endPos, e, w, root)

            if not e[startPos][endPos] then
                e[startPos][endPos] = currentValue
                root[startPos][endPos] = r
            else
                if e[startPos][endPos] > currentValue then
                    e[startPos][endPos] = currentValue
                    root[startPos][endPos] = r
                end
            end
        end

        return e[startPos][endPos]
    end
end

local function _printOptimizedBinarySearchTree(root, e, w, startPos, stopPos)
    if startPos == stopPos then
        print(root[startPos][stopPos])
    else
        local rootPos = root[startPos][stopPos]
        print(rootPos .. "的左孩子:")
        _printOptimizedBinarySearchTree(root, e, w, startPos, rootPos - 1)
        print(rootPos .. "的右孩子:")
        _printOptimizedBinarySearchTree(root, e, w, rootPos + 1, stopPos)
    end
end

function solutionModule:optimizedBinarySearchTree(kChances, dChances)
    local e
    local w
    local root
    local n = #kChances
    -- version 1
    local result = _optimizedBinarySearchTreePartialUp(kChances, dChances)
    e = result.e
    w = result.w
    root = result.root
    _printOptimizedBinarySearchTree(root, e, w, 1, n)

    print("===========================================")
    -- version 2
    e = {}
    w = {}
    root = {}
    for i = 1, n + 1, 1 do
        e[i] = {}
        w[i] = {}
    end

    for i = 1, n, 1 do
        root[i] = {}
    end

    _optimizedBinarySearchTreePartialDown(kChances, dChances, 1, n, e, w, root)
    -- print("e:", tableUtil:dump(e))
    -- print("w:", tableUtil:dump(w))
    -- print("root:", tableUtil:dump(root))
    _printOptimizedBinarySearchTree(root, e, w, 1, n)
end


-- function solutionModule:squareMatrixMultiply(data)
-- end

-- local function _maxActivitySetPartialDown(allActivitySet, startPos, stopPos, setBuffer)
--     if startPos == stopPos then

--     else
--         for i = startPos, stopPos, 1 do
--             setBuffer[startPos][stopPos] =
--         end
--     end
-- end

-- local function _maxActivitySetPartialUp(allActivitySet)

-- end

-- function solutionUtil:maxActivitySet(allActivitySet)

-- end

local function longestPalindromeUp(data)
    for i = 1, #data, 1 do
        for j = 1, i, 1 do

        end
    end
end

function solutionModule:longestPalindrome(data)

end


return solutionModule
