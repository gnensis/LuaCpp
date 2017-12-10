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

int getValueFromLua(lua_State* lua)
{
	printf("Enter callLuaTest\n");
	printf("top is %d\n", lua_gettop(lua));
	//Get variable from Lua
	lua_getglobal(lua, "luaStr");
	printf("top is %d\n", lua_gettop(lua));
	printf("luaStr:%s\n", lua_tostring(lua, -1));
	lua_pop(lua, 1);
	printf("top is %d\n", lua_gettop(lua));

	//Get Table from Lua
	lua_getglobal(lua, "luaTable");		//push luaTable to top
	printf("top is %d\n", lua_gettop(lua));
	lua_getfield(lua, -1, "name");		//push name to top
	printf("top is %d\n", lua_gettop(lua));
	printf("luaTable.name:%s\n", lua_tostring(lua, -1));
	lua_pop(lua, 1);					//pop name from top
	printf("top is %d\n", lua_gettop(lua));

	lua_getfield(lua, -1, "age");		//push age to top
	printf("top is %d\n", lua_gettop(lua));
	printf("luaTable.age:%d\n", lua_tointeger(lua, -1));
	lua_pop(lua, 1);					//pop age from top
	printf("top is %d\n", lua_gettop(lua));

	lua_getfield(lua, -1, "isMale");	//push isMale to top
	printf("top is %d\n", lua_gettop(lua));
	printf("luaTable.isMale:%d\n", lua_toboolean(lua, -1));
	lua_pop(lua, 2);					//pop isMale and luaTable from top
	printf("top is %d\n", lua_gettop(lua));

	return 0;
}

int transferValueToLua(lua_State* lua)
{
	//Cpp Transfer variable to Lua
	lua_pushstring(lua, "This is a String from Cpp");
	printf("top is %d after lua_pushstring(lua, \"This is a String from Cpp\")\n", lua_gettop(lua));
	lua_setglobal(lua, "cppStr");
	printf("top is %d after lua_setglobal(lua, \"cppStr\")\n", lua_gettop(lua));
	printf("\n");

	//Cpp Transfer Table to Lua
	lua_newtable(lua);
	printf("top is %d after lua_newtable(lua)\n", lua_gettop(lua));
	lua_pushstring(lua, "name");
	printf("top is %d after lua_pushstring(lua, \"name\")\n", lua_gettop(lua));
	lua_pushstring(lua, "LingHuchong");
	printf("top is %d after lua_pushstring(lua, \"LingHuchong\")\n", lua_gettop(lua));
	lua_settable(lua, -3);
	printf("top is %d after lua_settable(lua, -3)\n", lua_gettop(lua));

	lua_pushstring(lua, "age");
	printf("top is %d after lua_pushstring(lua, \"age\")\n", lua_gettop(lua));
	lua_pushinteger(lua, 20);
	printf("top is %d after lua_pushinteger(lua, 20)\n", lua_gettop(lua));
	lua_settable(lua, -3);
	printf("top is %d after lua_settable(lua, -3)\n", lua_gettop(lua));

	lua_pushstring(lua, "isMale");
	printf("top is %d after lua_pushstring(lua, \"isMale\")\n", lua_gettop(lua));
	lua_pushboolean(lua, 1);
	printf("top is %d after lua_pushboolean(lua, 1)\n", lua_gettop(lua));
	lua_settable(lua, -3);
	printf("top is %d after lua_settable(lua, -3)\n", lua_gettop(lua));
	lua_setglobal(lua, "cppTable");
	printf("top is %d after lua_setglobal(lua, \"cppTable\")\n", lua_gettop(lua));
	printf("\n");

	return 0;
}

int main(int argc, char* argv[])
{
	int err = 0;

	lua_State *lua = lua_open();
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);

	//Register Cpp function to Lua
	lua_register(lua, "calledByLua", calledByLua);
	lua_register(lua, "calledByLuaArray", calledByLuaArray);
	lua_register(lua, "calledByLuaTable", calledByLuaTable);
	lua_register(lua, "calledByLuaTable2", calledByLuaTable2);
	lua_register(lua, "calledByLuaReturn", calledByLuaReturn);
	lua_register(lua, "calledByLuaReturnTable", calledByLuaReturnTable);

	//
	err = luaL_loadfile(lua, "main.lua");
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Lua load error: %s\n", errStr);
		goto EXIT;
	}

	transferValueToLua(lua);
	err = lua_pcall(lua, 0, 0, 0);
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Lua run error: %s\n", errStr);
		lua_pop(lua, -1);	//Pop err message from Top
		goto EXIT;
	}

	//
	getValueFromLua(lua);

	////Call Lua Function without Parameter
	printf("top is %d before lua_getglobal(lua, \"luaFunction01\")\n", lua_gettop(lua));
	lua_getglobal(lua, "luaFunction01");
	printf("top is %d after lua_getglobal(lua, \"luaFunction01\")\n", lua_gettop(lua));
	err = lua_pcall(lua, 0, 0, 0);
	printf("top is %d after err = lua_pcall(lua, 0, 0, 0)\n", lua_gettop(lua));
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Run Lua function luaFunction01 error: %s\n", errStr);
		lua_pop(lua, -1);	//Pop err message from Top
		goto EXIT;
	}

	//Call Lua Function with a Parameter
	lua_getglobal(lua, "luaFunction02");
	lua_pushstring(lua, "parameter From cpp");
	err = lua_pcall(lua, 1, 0, 0);
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Run Lua function luaFunction02 error: %s\n", errStr);
		lua_pop(lua, -1);
		goto EXIT;
	}

	//Call Lua Function with a Parameter and Get the Return Value
	lua_getglobal(lua, "luaFunction03");
	lua_pushstring(lua, "parameter From cpp");
	err = lua_pcall(lua, 1, 1, 0);
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Run Lua function luaFunction03 error: %s\n", errStr);
		lua_pop(lua, -1);
		goto EXIT;
	}
	else
	{
		printf("luaFunction03 return:%s\n", lua_tostring(lua, -1));
		lua_pop(lua, -1);
	}

	//
	//Call Lua Function with a Parameter and Get the Return Value
	printf("Top is %d befor lua_getglobal(lua, \"luaErrorProcessFunction\")\n", lua_gettop(lua));
	int luaErrFun = lua_gettop(lua);
	lua_getglobal(lua, "luaErrorProcessFunction");
	luaErrFun++;
	lua_getglobal(lua, "luaFunction04");
	lua_pushstring(lua, "parameter From cpp");
	printf("Top is %d befor lua_pcall(lua, 1, 1, luaErrFun)\n", lua_gettop(lua));
	err = lua_pcall(lua, 1, 1, luaErrFun);
	if(err)
	{
		//const char* errStr = lua_tostring(lua, -1);
		//printf("Run Lua function luaFunction03 error: %s\n", errStr);
		//lua_pop(lua, -1);
		//goto EXIT;
	}
	else
	{
		printf("luaFunction03 return:%s\n", lua_tostring(lua, -1));
		lua_pop(lua, -1);
	}


	//Transfer a table to Lua Function
	lua_getglobal(lua, "luaFunction05");
	lua_pushstring(lua, "parameter From cpp");
	lua_newtable(lua);
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "XieXun");
	lua_settable(lua, -3);
	lua_pushstring(lua, "age");
	lua_pushinteger(lua, 88);
	lua_settable(lua, -3);
	lua_pushstring(lua, "isMale");
	lua_pushboolean(lua, true);
	lua_settable(lua, -3);
	err = lua_pcall(lua, 2, 1, 0);
	if(err)
	{
		const char* errStr = lua_tostring(lua, -1);
		printf("Run Lua function luaFunction05 error: %s\n", errStr);
		lua_pop(lua, -1);
		goto EXIT;
	}
	else
	{
		lua_getfield(lua, -1, "name");
		printf("return.name:%s\n", lua_tostring(lua, -1));
		lua_pop(lua, -2);
		lua_getfield(lua, -1, "age");
		printf("return.age:%d\n", lua_tointeger(lua, -1));
		lua_pop(lua, -2);
		lua_getfield(lua, -1, "isMale");
		printf("return.isMale:%d\n", lua_toboolean(lua, -1));
		lua_pop(lua, -2);
	}

	

EXIT:
	getchar();

	lua_close(lua);

	return 0;
}