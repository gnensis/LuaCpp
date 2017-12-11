width = 600
height = 400

local pathdlg = 1000
local contentdlg = 1001
function loadfile()
	local path = GetText(pathdlg)
	local inp = io.open(path, "rb")
	local data = inp:read("*all")
	SetText(contentdlg, data)

	--Alert(text)
end