local heapModule = {
    data = {}
}

function heapModule:new(opt)
    local obj = opt or {}
    self.__index = self
    setmetatable(obj, self)

    return obj
end

function heapModule:getLeftPos(currentPos)
    return currentPos * 2
end

function heapModule:getRightPos(currentPos)
    return currentPos * 2 + 1
end

function heapModule:getParentPos(currentPos)
    return math.floor(currentPos / 2)
end

function heapModule:sortPosInHeapDown(targetPos)
    local leftPos = self:getLeftPos(targetPos)
    local rightPos = self:getRightPos(targetPos)
    local largePos = targetPos
    if leftPos <= #self.data and self.data[leftPos] > self.data[targetPos] then
        largePos = leftPos
    end

    if rightPos <= #self.data and self.data[rightPos] > self.data[largePos] then
        largePos = rightPos
    end

    if largePos ~= targetPos then
        local tmp = self.data[targetPos]
        self.data[targetPos] = self.data[largePos]
        self.data[largePos] = tmp
        self:sortPosInHeapDown(largePos)
    end
end

function heapModule:makeHeap()
    for i = #self.data / 2, 1, -1 do
        self:sortPosInHeapDown(math.floor(i))
    end
end

function heapModule:showHeapInfo()
    for _, v in pairs(self.data) do
        print(v)
    end
end

function heapModule:showAsTree()
    local treeHigh = math.log(#self.data, 2)
    print(treeHigh)
end

function heapModule:initData(data)
    self.data = data
    print(#self.data)
end

function heapModule:pop()
    local headValue = self.data[1]
    self.data[1] = self.data[#self.data]
    table.remove(self.data, #self.data)
    self:sortPosInHeapDown(1)

    return headValue
end

function heapModule:sortPosInHeapUp(currentPos)
    local parentPos = self:getParentPos(currentPos)
    if parentPos ~= 0 and self.data[currentPos] > self.data[parentPos] then
        local tmp = self.data[parentPos]
        self.data[parentPos] = self.data[currentPos]
        self.data[currentPos] = tmp
        self:sortPosInHeapUp(parentPos)
    end
end

function heapModule:push(value)
    table.insert(self.data, value)
    self:sortPosInHeapUp(#self.data)
end

function heapModule:size()
    return #self.data
end

return heapModule
