local Account = {}

function Account:new(opt)
   local o = opt or {}
   setmetatable(o, self)
   self.__index = self

   return o
end


local a = Account:new()
for k, v in pairs(a.__index.__index) do
   print(k)
end


return Account
