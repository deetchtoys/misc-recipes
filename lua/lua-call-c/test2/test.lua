local function test1()
    local mylib = require "mylib"
    print("lua:", mylib.add(10, 20))
    print("lua:", mylib.add(10, 20))

    print("lua:", mylib.save2RegistryIndex(110))
    print("lua:", mylib.getFromRegistryIndex())

    print("lua:", mylib.saveString("wdq-key", "wdq"))
    print("lua:", mylib.getString("wdq-key"))

    local arr = {1,2,3,4}
    local keyNum = mylib.saveRef(arr)
    print("lua:", keyNum)
    local savedRef = mylib.getRef(keyNum)
    print("lua:", type(savedRef))
    for k, v in pairs(savedRef) do
        print("lua:", k, " ### ", v)
    end


    local addClosure, subClosue = mylib.getClosure()
    print("lua:", "add closure:", addClosure())
    print("lua:", "add closure:", addClosure())
    print("lua:", "add closure:", addClosure())

    print("lua:", "sub closure:", subClosue())
    print("lua:", "sub closure:", subClosue())
    print("lua:", "sub closure:", subClosue())


    local function getClosure()
        num = 0

        return function()
            num = num + 1
            return num
        end
    end


    local luaClosureFunc = getClosure()
    print("lua:", "lua closure:", luaClosureFunc())
    print("lua:", "lua closure:", luaClosureFunc())
    print("lua:", "lua closure:", luaClosureFunc())
end

local function test2()
    local myArray = require "myArray"
    for k, v in pairs(myArray) do
        print("lua:", k)
    end

    print("--------------------------------------------------")
    local array = myArray.newArray(10)
    for k, v in pairs(getmetatable(array)) do
        print("lua:", k)
    end

    print("--------------------------------------------------")
end

local function test3()
    local Account = require "Account"
    for k, v in pairs(Account) do
        print("lua:", k)
    end

    print("--------------------------------------------------")
    local account = Account.newInstance(10, 1, 20);
    for k, v in pairs(getmetatable(account)) do
        print("lua:", k)
    end

    print("--------------------------------------------------")
    account:setField("name", "wangdiqi")
    print(account)
end

local function test4()
   local t = require "myDir"
   print(t)
   local d = dir("/home/wdq")
   print(d())
   print(d())
   print(d())
   print(d())
end

print("#########################test2()#####################################")
test2()
print("#########################test2() end#################################")

print("#########################test3()#####################################")
test3()
print("#########################test3() end#################################")

print("#########################test4()#####################################")
test4()
print("#########################test4() end#################################")
