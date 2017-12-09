-- testString.lua
print("[testString.lua begin--------------]")
local str = "This is a Lua String"
print("str:"..str)

local htmlStr = [[
<html>
	<head>
		<title>HTML in Lua</title>
	</head>
	<body>
		<H1>This is a Lua HTML page.</H1>
	</body>
</html>
]]
print("htmlStr:"..htmlStr)
print("Length of htmlStr:"..string.len(htmlStr))

local subStr = string.sub(str, 2, 4)
print("str:"..str)
print("string.sub(str, 2, 4):", subStr)

local b, e = string.find(htmlStr, "head")
print("b:"..b)
print("e:"..e)

local xmlStr = string.gsub(htmlStr, "html", "xml")
print("xmlStr:"..xmlStr)
print("[testString.lua end----------------]")