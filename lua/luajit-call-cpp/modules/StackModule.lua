local stackModule = {
    data = {},
    top = 0
}

function stackModule:new(opt)
    local obj = opt or {}
    self.__index = self
    setmetatable(obj, self)

    return obj
end

function stackModule:push(value)
    top = top + 1
    table.insert(self.data, top, value)
end

function stackModule:pop()

end

function stackModule:top()

end

return stackModule
