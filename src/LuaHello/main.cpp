#include <stdio.h>
#include <string.h>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

//Common Type Parameter
int calledByLua(lua_State* L)
{
	printf("Enter calledByLua\n");
	size_t len;

	if(lua_type(L, 1) == LUA_TSTRING)
	{
		const char* name = lua_tolstring(L, 1, &len);
		printf("name:%s\n", name);
		printf("len:%d\n", len);
	}
	else
	{
		printf("name type is not LUA_TSTRING\n");
	}

	if(lua_type(L, 2) == LUA_TNUMBER)
	{
		int age = lua_tonumber(L, 2);
		printf("age:%d\n", age);
	}
	else
	{
		printf("age type is not LUA_TNUMBER\n");
	}

	if(lua_type(L, 3) == LUA_TBOOLEAN)
	{
		bool isMale = lua_toboolean(L, 3);
		printf("isMale:%d\n", isMale);
	}
	else
	{
		printf("isMale type is not LUA_TBOOLEAN\n");
	}

	return 0;
}

//Array Type Parameter
int calledByLuaArray(lua_State* L)
{
	printf("Enter calledByLuaArray\n");
	luaL_checktype(L, 1, LUA_TTABLE);

	size_t len = luaL_getn(L, 1);
	for(int i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i);	//push a number at the top of the stack.
		lua_gettable(L, 1);		//pop index, push table[i]
		size_t size = 0;

		switch(i)
		{
		case 1:
			if(lua_type(L, -1) == LUA_TSTRING)
			{
				printf("name:%s\n", lua_tolstring(L, -1, &size));
			}
			else
			{
				printf("ERROR:name type is not LUA_TSTRING\n");
			}
			break;
		case 2:
			if(lua_type(L, -1) == LUA_TNUMBER)
			{
				printf("age(integer):%d\n", lua_tointeger(L, -1));		//correct.
				printf("age(number):%d\n", lua_tonumber(L, -1));		//get 0
			}
			else
			{
				printf("ERROR:age type is not LUA_TNUMBER\n");
			}
			break;
		case 3:
			if(lua_type(L, -1) == LUA_TBOOLEAN)
			{
				printf("isMale:%d\n", lua_toboolean(L, -1));
			}
			else
			{
				printf("ERROR:isMale type is not LUA_TBOOLEAN\n");
			}
			break;
		default:
			printf("default: %s\n", lua_tolstring(L, -1, &size));
		}

		lua_pop(L, 1);
	}
	return 0;
}

//Table Type Paramter
int calledByLuaTable(lua_State* L)
{
	printf("Enter calledByLuaTable\n");
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_pushnil(L);
	while(lua_next(L, 1) != 0)
	{
		const char *key = lua_tostring(L, -2);
		printf("key=%s\n", key);

		if(strcmp(key, "isMale") == 0)	//boolean can not tolstring.
		{
			luaL_checktype(L, -1, LUA_TBOOLEAN);
			bool isMale = lua_toboolean(L, -1);
			printf("value=%d\n", isMale);
		}
		else if(strcmp(key, "name") == 0)
		{
			luaL_checktype(L, -1, LUA_TSTRING);
			const char *value = lua_tostring(L, -1);
			printf("value=%s\n", value);
		}
		else
		{
			luaL_checktype(L, -1, LUA_TNUMBER);
			const char *value = lua_tostring(L, -1);
			printf("value=%s\n", value);
		}
		
		lua_pop(L, 1);
	}
	return 0;
}

//Table Type Paramter
int calledByLuaTable2(lua_State* L)
{
	printf("Enter calledByLuaTable2\n");
	luaL_checktype(L, 1, LUA_TTABLE);

	//name
	lua_getfield(L, 1, "name");
	luaL_checktype(L, -1, LUA_TSTRING);
	printf("name:%s\n", lua_tostring(L, -1));

	//age
	lua_getfield(L, 1, "age");
	luaL_checktype(L, -1, LUA_TNUMBER);
	printf("age:%d\n", lua_tointeger(L, -1));	//lua_tonumber is not working.

	//isMale
	lua_getfield(L, 1, "isMale");
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	printf("isMale:%d\n", lua_toboolean(L, -1));
	return 0;
}

int calledByLuaReturn(lua_State* L)
{
	printf("Enter calledByLuaReturn\n");
	const char* name = "XiaoLongnv";
	int age = 18;
	bool isMale = false;

	lua_pushstring(L, name);
	lua_pushnumber(L, age);
	lua_pushboolean(L, isMale);
	return 3;
}

int calledByLuaReturnTable(lua_State* L)
{
	printf("Enter calledByLuaReturnTable\n");
	lua_newtable(L);				//-1
	lua_pushstring(L, "name");		//-2
	lua_pushstring(L, "YangGuo");	//-3
	lua_settable(L, -3);			//-1

	lua_pushstring(L, "age");		//-2
	lua_pushnumber(L, 16);			//-3
	lua_settable(L, -3);			//-1

	lua_pushstring(L, "isMale");	//-2
	lua_pushboolean(L, false);		//-3
	lua_settable(L, -3);			//-1

	return 1;
}

int main(int argc, char* argv[])
{
	int err = 0;

	lua_State *lua = lua_open();
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);

	lua_register(lua, "calledByLua", calledByLua);
	lua_register(lua, "calledByLuaArray", calledByLuaArray);
	lua_register(lua, "calledByLuaTable", calledByLuaTable);
	lua_register(lua, "calledByLuaTable2", calledByLuaTable2);
	lua_register(lua, "calledByLuaReturn", calledByLuaReturn);
	lua_register(lua, "calledByLuaReturnTable", calledByLuaReturnTable);

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