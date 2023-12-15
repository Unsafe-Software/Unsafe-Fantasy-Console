#pragma once
#include <string>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

lua_State* L;

static int average(lua_State *L) {
   int n = lua_gettop(L);
   double sum = 0;
   int i;

   for (i = 1; i <= n; i++) {
       sum += lua_tonumber(L, i);
   }

   lua_pushnumber(L, sum / n);
   lua_pushnumber(L, sum);
   return 2;
}

void init(std::string file) {
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "average", average);
    luaL_dofile(L, file.c_str());
}

void close() {
    lua_close(L);
}
