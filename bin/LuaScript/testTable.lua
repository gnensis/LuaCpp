-- testTable.lua
print("[testTable.lua begin--------------------]")

local tab1 = {"001", "002", "003"}
table.insert(tab1, 3, "002-2")
for i,v in ipairs(tab1) do
	print("value ="..v)
end

--insert
table.insert(tab1, "004")
print("after inserter(tab1, \"004\")")
for i,v in ipairs(tab1) do
	print("value ="..v)
end

--remove
table.remove(tab1, 3)
print("after remove(tab1, 3)")
for i,v in ipairs(tab1) do
	print("value ="..v)
end

--remove
table.remove(tab1)
print("after remove(tab1)")
for i,v in ipairs(tab1) do
	print("value ="..v)
end

--
local tab2 = {id=123, age=23}
tab2["name"] = "xiaogang"
for k, v in pairs(tab2) do
	print(k .. ":" .. v)
end

tab2["id"] = nil
print("after tab2[\id\"] = nil")
for k, v in pairs(tab2) do
	print(k .. ":" .. v)
end


local tab3 = {}
tab3[1] = {"name1", "name2"}
tab3[2] = {"value1", "value2"}

for k, v in pairs(tab3) do
	for k2, v2 in pairs(v) do
		print("k2:"..k2, "v2:"..v2)
	end
end
print("[testTable.lua end----------------------]")