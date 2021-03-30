#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void test1()
{
  double x = 12, y = 20;
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  if (luaL_dofile(L, "func1.lua"))
  {
    printf("loadfile error\n");
    lua_close(L);
    return;
  }

  lua_getglobal(L, "f");
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);

  if (lua_pcall(L, 2, 1, 0))
  {
    printf("pcall error\n");
    lua_close(L);
    return;
  }

  if (!lua_isnumber(L, -1))
  {
    printf("function f must return a number\n");
  }

  double z = lua_tonumber(L, -1);
  lua_pop(L, 1);

  printf("%f\n", z);
}

int main(void)
{
  test1();
  return 0;
}
