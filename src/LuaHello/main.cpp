#include <stdio.h>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int main(int argc, char* argv[])
{
	int err = 0;

	lua_State *lua = lua_open();
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);

	err = luaL_loadfile(lua, "main.lua");
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Lua load error: %s\n", errStr);
		goto EXIT;
	}

	err = lua_pcall(lua, 0, 0, 0);
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Lua run error: %s\n", errStr);
		goto EXIT;
	}

EXIT:
	getchar();
	return 0;
}