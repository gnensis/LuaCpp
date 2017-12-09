-- testFunction.lua
--[[
function func_name(arguments-list)
	statements-list;
end;
]]
print("[testFunction.lua begin--------------------]")
function test(p1)
	print("p1:"..p1)
	print("in test() function")
end

function test2(...)
	local count = table.getn(arg)
	print("count:"..count)
	for k, v in pairs(arg) do
		print("k:"..k, "v:"..v)
	end
end
test("v1")
test2("v1", "v2", "v3")

--
function test3(...)
	return 0,"error"
end
local t31,t32 = test3()
print("t31:"..t31, "t32:"..t32)


--
local event = function(p1)
	print("p1 in event:".. p1)
end

event("Key")
print("[testFunction.lua end----------------------]")