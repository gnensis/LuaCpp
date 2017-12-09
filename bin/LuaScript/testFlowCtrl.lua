--testFlowCtrl.lua
print("[testFlowCtrl.lua begin--------------------]")

-- if
local num = 1
if (num == 1) then
	print("num == 1")
elseif (num == 2) then
	print("num == 2")
else
	print("num != 1")
	print("num != 2")
end

-- while
while (num < 10) do
	num = num + 1
	print("num:"..num)

	if(num > 6) then
		print("break from (num > 6)")
		break
	end
end

-- repeat
repeat
	num = num + 1
	print("num:"..num)

	if(num > 25) then
		print("break from (num > 25)")
		break
	end
until (num > 30)


-- for
for numfor = 1, 10, 2 do
	print("numfor:"..numfor)
end

-- for
local weekDay = {"Sun", "Mon", "Tue", "Wed"}
for i, v in ipairs(weekDay) do
	print(i..":"..v)
end

-- pairs vs ipairs



print("[testFlowCtrl.lua end----------------------]")