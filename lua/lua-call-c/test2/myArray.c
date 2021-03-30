#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "HelperFuncs.h"

typedef struct NumArrayS
{
  int size;
  double values[1];
} NumArray;

static NumArray *checkarray(lua_State *L)
{
  void *ud = luaL_checkudata(L, 1, "LuaBook.array");
  luaL_argcheck(L, ud != NULL, 1, "array expected");

  return (NumArray *)ud;
}

static int newArray(lua_State *L)
{
  int n = luaL_checkint(L, 1);
  size_t nbytes = sizeof(NumArray) + (n - 1) * sizeof(double);
  NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
  for (int i = 0; i < n; ++i)
  {
    a->values[i] = 0;
  }
  luaL_getmetatable(L, "LuaBook.array");
  lua_setmetatable(L, -2);
  a->size = n;

  return 1;
}

static int setArray(lua_State *L)
{

  NumArray *a = checkarray(L);
  int index = luaL_checkint(L, 2);
  double value = luaL_checknumber(L, 3);

  luaL_argcheck(L, a != NULL, 1, "array expected");

  luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index our of range");
  a->values[index-1] = value;

  return 0;
}

static int printArray(lua_State *L)
{
  NumArray *a = checkarray(L);
  for (int i = 0; i < a->size; ++i)
  {
    printf("%f\n", a->values[i]);
  }

  return 0;
}

static const struct luaL_Reg myArray[] =
{
  {"newArray", newArray},
  {NULL, NULL}
};

static const struct luaL_Reg arrayLibM[] =
{
  {"setArray", setArray},
  {"printArray", printArray},
  {NULL, NULL}
};


extern int luaopen_myArray(lua_State *L)
{
  luaL_newmetatable(L, "LuaBook.array");

  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, arrayLibM);
  /* luaL_newlib(L, mylib); */
  luaL_register(L, "myArray", myArray);

  return 1;
}
