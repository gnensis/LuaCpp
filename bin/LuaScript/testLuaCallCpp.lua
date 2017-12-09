-- test.lua
print("[testLuaCallCpp.lua begin--------------------]")
local name = "LingHuchong"
local age = 20
local isMale = true
calledByLua(name, age, isMale)
print("")

--Array
local userInfo = {name, age, isMale}
calledByLuaArray(userInfo)
print("")

--Pass Table
local userInfoTb = {}
userInfoTb["name"] = "LingHuchong"
userInfoTb["age"] = 20
userInfoTb["isMale"] = true
calledByLuaTable(userInfoTb)
print("")

--Pass Table2
calledByLuaTable2(userInfoTb)
print("")

--Get Returned value
local xName, xAge, xIsMale = calledByLuaReturn()
print("xName:\t", xName)
print("xAge:\t", xAge)
print("xIsMale:", xIsMale)
print("")

--Get Returned Table
local yangGuo = calledByLuaReturnTable()
for k, v in pairs(yangGuo) do
	print(k, ":", v)
end

print("[testLuaCallCpp.lua end----------------------]")