#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

#include "HelperFuncs.h"

void stackDump(lua_State *L)
{
  printf("###################stackDump-start###################\n\n");
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; ++i)
  {
    int t = lua_type(L, i);
    switch (t) {
      case LUA_TSTRING:
        printf("[%d] : %s\n", i, lua_tostring(L, i));
        break;

      case LUA_TBOOLEAN:
        printf("[%d] : %s\n", i, lua_toboolean(L, i) ? "true" : "false");
        break;

      case LUA_TNUMBER:
        printf("[%d] : %g\n", i, lua_tonumber(L, i));
        break;

      default:
        printf("[%d] : %s\n", i, lua_typename(L, t));
        break;
    }
  }
  printf("\n");
  printf("###################stackDump-end###################\n\n");
}

void debugInfo(const char *log, const char *funcName)
{
  if (funcName == NULL)
  {
    funcName = "Unknown";
  }
  printf("###################c api log start###################\n\n");
  printf("FuncName: [%s]\n%s\n", funcName, log);
  printf("###################c api log end###################\n\n");
}
