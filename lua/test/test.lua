-- a = {}
-- b = {}
-- setmetatable(a, b)
-- b.__mode = "k"
-- key = {}
-- a[key] = 1
-- key = {}
-- a[key] = 2

-- collectgarbage()


-- for k, v in pairs(a) do
--     print(v)
-- end

-- print("################################################")

-- Account = {name = 1}
-- print(Account)
-- setmetatable(Account, {__index = function(t,arg1, arg2)
--                            print("t:", t)
--                            print("arg1:", arg1)
--                            print("arg2:", arg2)
-- end})

-- print(Account.name1())


local defaults = {}
setmetatable(defaults, {__mode = "k"})
local mt = {__index = function (t) return defaults[t] end}


function setDefault1(t, d)
    defaults[t] = d
    setmetatable(t, mt)
end


Account = {}

setDefault1(Account, 10)

print(Account.a)


local metas = {}
setmetatable(metas, {__mode = "v"})

function setDefault2(t, d)
    local mt = metas[d]
    if mt == nil then
        mt = {__index = function () return d end}
        metas[d] = mt
    end

    setmetatable(t, mt)
end
