local tableModule = {}

function tableModule:new(opt)
    local obj = opt or {}
    self.__index = self
    setmetatable(obj, self)

    return obj
end

local function wrapIndent(indentLevel)
    local indentPrefix = ""
    for i = 1, indentLevel, 1 do
        indentPrefix = indentPrefix .. "  "
    end

    return indentPrefix
end

local function wrapKey(key)
    if type(key) == "string" then
        return '["' .. key .. '"]'
    elseif type(key) == "number" then
        return '[' .. tostring(key) .. ']'
    else
        return '[' .. tostring(key) .. ']'
    end
end

local function wrapValue(value)
    if type(value) == "string" then
        return '"' .. value .. '",'
    elseif type(value) == "number" then
        return tostring(value) .. ","
    else
        return tostring(value) .. ","
    end
end

local function _dump(tableInstance, indentLevel)
    local debugInfo = {}
    indentLevel = indentLevel or 0
    if type(tableInstance) == "table" then
        for key, value in pairs(tableInstance) do
            if type(value) == "table" then
                table.insert(debugInfo, wrapIndent(indentLevel) .. wrapKey(key) .. ":{")
                table.insert(debugInfo, _dump(value, indentLevel + 1))
                table.insert(debugInfo, wrapIndent(indentLevel) .. "},")
            else
                table.insert(debugInfo, wrapIndent(indentLevel) .. wrapKey(key) .. ":" .. wrapValue(value))
            end
        end

        return table.concat(debugInfo, "\n")
    else
        print("something error")
    end
end

function tableModule:dump(tableInstance, indentLevel)
    return "{\n" .. _dump(tableInstance, 1) .. "\n}"
end

function tableModule:deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[self:deepcopy(orig_key)] = self:deepcopy(orig_value)
        end
        setmetatable(copy, self:deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end

    return copy
end

function tableModule:swap(arrayData, left, right)
    local tmp = arrayData[left]
    arrayData[left] = arrayData[right]
    arrayData[right] = tmp
end

return tableModule
