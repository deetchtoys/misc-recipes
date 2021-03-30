#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

static int add(lua_State *L)
{
  double a = luaL_checknumber(L, 1);
  double b = luaL_checknumber(L, 2);
  lua_pushnumber(L, a + b);

  return 1;
}


int main(void)
{
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  /* lua_pushcfunction(L, add); */
  /* lua_setglobal(L, "add"); */
  lua_register(L, "add", add);
  const char *testfunc = "print(add(10, 20))";
  if (luaL_dostring(L, testfunc))
    printf("failed to invoke.\n");

  lua_close(L);

  return 0;
}
