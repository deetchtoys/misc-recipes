package.path = './modules/?.lua;'
package.cpath = './solibs/?.so'

local cjson = require("cjson.safe")
local tableUtil = require("TableModule"):new()
local heap = require("HeapModule"):new()
local solutionUtil = require("SolutionModule"):new()

local data
local data2

-- heap:initData({1,2,3,4,5})
-- heap:makeHeap()


-- heap:push(10)
-- heap:push(7)
-- heap:showHeapInfo()
-- print("===========================")

-- print(heap:showAsTree())

-- print(cjson.encode(solutionUtil:findMaxRange({-1,2,3})))

data = {5, 1, 2, 9, 8, 3, 6, 7, 4}
solutionUtil:quickSort(data)

print(table.concat(data, ","))

-- data = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"}
data = {"A", "B", "C"}
solutionUtil:getAllOrderSet(data)

print("#########################################")

local allSubSet = solutionUtil:getAllSubSet(data)
print(table.concat(allSubSet, ","))

print("#########################################")
local priceItems = {
    [1] = 1,
    [2] = 5,
    [3] = 8,
    [4] = 9,
    [5] = 10,
    [6] = 17,
    [7] = 17,
    [8] = 20,
    [9] = 24,
    [10] = 30,
}

local n = 10
local cutRodSolution = solutionUtil:cutRod(priceItems, n)

while n > 0 do
    print(cutRodSolution.cutSize[n])
    n = n - cutRodSolution.cutSize[n]
end

print("#########################################")

data = {"A", "B", "C", "B", "D", "A", "B"}
data2 = {"B", "D", "C", "A", "B", "A"}
solutionUtil:getSetLCS(data, data2)


print("#########################################")

data = {"A", "B", "C", "B", "D", "A", "B"}
data2 = {"B", "D", "C", "A", "B", "A"}
solutionUtil:getStringLCS(data, data2)


print("#########################################")

local kChances = {
    [1] = 0.15,
    [2] = 0.10,
    [3] = 0.05,
    [4] = 0.10,
    [5] = 0.20,
}

local dChances = {
    [0] = 0.05,
    [1] = 0.10,
    [2] = 0.05,
    [3] = 0.05,
    [4] = 0.05,
    [5] = 0.10,
}

solutionUtil:optimizedBinarySearchTree(kChances, dChances)

local allActivitySet = {
    [0] = {start = 0, stop = 0},
    [1] = {start = 1, stop = 4},
    [2] = {start = 3, stop = 5},
    [3] = {start = 0, stop = 6},
    [4] = {start = 5, stop = 7},
    [5] = {start = 3, stop = 9},
    [6] = {start = 5, stop = 9},
    [7] = {start = 6, stop = 10},
    [8] = {start = 8, stop = 11},
    [9] = {start = 8, stop = 12},
    [10] = {start = 2, stop = 14},
    [11] = {start = 12, stop = 16},
}


solutionUtil:maxActivitySet(allActivitySet)


data = {"A", "B", "C", "B", "D", "A", "B"}
solutionUtil:longestPalindrome(data)
