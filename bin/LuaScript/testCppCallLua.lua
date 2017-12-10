-- testCppCallLua.lua
print("[testCppCallLua.lua begin--------------------]")

--Get cppStr from cpp file
print("cppStr:" .. cppStr)

--Transfer luaStr to cpp file
luaStr = "This is a String defined in testCppCallLua.lua"

luaTable = {}
luaTable["name"] = "ZhangSanfeng"
luaTable["age"] = 101
luaTable["isMale"] = true

--Get cppTable from cpp file
print("cppTable.name:" .. cppTable.name)
print("cppTable.age:" .. cppTable.age)
print("cppTable.isMale:", cppTable.isMale)

function luaFunction01()
	print("Enter luaFunction01")
	print("Exit  luaFunction01")
end

function luaFunction02(argv1)
	print("Enter luaFunction02")
	print("argv1:", argv1)
	print("Exit  luaFunction02")
end

function luaFunction03(argv1)
	print("Enter luaFunction03")
	print("argv1:", argv1)
	print("Exit  luaFunction03")

	return "Return Value from luaFunction03"
end

function luaFunction04(argv1)
	print("Enter luaFunction04")
	print("argv1:", argv1)
	print("Exit  luaFunction04")

	return "Return Value from luaFunction03"
end

function luaErrorProcessFunction(argv1)
	print("Enter luaErrorProcessFunction")
	print("My Error:" .. argv1)
	print("Exit  luaErrorProcessFunction")
	return "luaErrorProcessFunction Return Str."
end

function luaFunction05(argv1, argv2)
	print("Enter luaFunction05")
	print("argv1:", argv1)
	print("argv1.name:", argv2.name)
	print("argv1.age:", argv2.age)
	print("argv1.isMale:", argv2.isMale)

	local guoJing = {name="GuoJing", age=45, isMale=true}
	print("Exit  luaFunction05")

	return guoJing
end

print("[testCppCallLua.lua end----------------------]")