#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "HelperFuncs.h"

static double base = 10;

static int add(lua_State *L)
{
  double a = luaL_checknumber(L, 1);
  double b = luaL_checknumber(L, 2);
  lua_pushnumber(L, a + b + base);
  lua_pushnumber(L, base);
  base =10 * 2;

  return 2;
}

static const char key = 'k';
static int save2RegistryIndex(lua_State *L)
{
  double savedNumber = lua_tonumber(L, -1);
  lua_pushlightuserdata(L, (void *)&key);
  lua_pushnumber(L, savedNumber);
  lua_settable(L, LUA_REGISTRYINDEX);
  lua_pushstring(L, "success");
  return 1;
}

static int getFromRegistryIndex(lua_State *L)
{
  lua_pushlightuserdata(L, (void *)&key);
  lua_gettable(L, LUA_REGISTRYINDEX);
  return 1;
}

static int saveString(lua_State *L)
{
  const char *key = lua_tostring(L, -2);
  printf("c api : %s\n", key);
  const char *str = lua_tostring(L, -1);
  printf("c api : %s\n", str);
  lua_pushlightuserdata(L, (void *)key);
  lua_pushstring(L, str);
  lua_settable(L, LUA_REGISTRYINDEX);
  /* lua_settop(L, 0); */
  lua_pushstring(L, "success");
  return 1;
}

static int getString(lua_State *L)
{
  const char *key = lua_tostring(L, -1);
  printf("c api : %s\n", key);
  lua_pushlightuserdata(L, (void *)key);
  lua_gettable(L, LUA_REGISTRYINDEX);
  return 1;
}

static int saveRef(lua_State *L)
{
  int keyNum = luaL_ref(L, LUA_REGISTRYINDEX);
  printf("c api : %d\n", keyNum);
  lua_pushnumber(L, keyNum);
  return 1;
}

static int getRef(lua_State *L)
{
  int keyNum = lua_tonumber(L, -1);
  lua_rawgeti(L, LUA_REGISTRYINDEX, keyNum);
  luaL_unref(L, LUA_REGISTRYINDEX, keyNum);
  return 1;
}

static int counter(lua_State *L)
{
  double first = lua_tonumber(L, lua_upvalueindex(1));
  printf("c api : %f\n", first);
  lua_pushnumber(L, ++first);
  lua_pushvalue(L, -1);
  lua_replace(L, lua_upvalueindex(1));
  return 1;
}

static int subCounter(lua_State *L)
{
  double first = lua_tonumber(L, lua_upvalueindex(1));
  printf("c api : %f\n", first);
  lua_pushnumber(L, --first);
  lua_pushvalue(L, -1);
  lua_replace(L, lua_upvalueindex(1));

  return 1;
}

static int getClosure(lua_State *L)
{
  lua_pushnumber(L, 0);
  lua_pushcclosure(L, &counter, 1);
  lua_pushnumber(L, 100);
  lua_pushcclosure(L, &subCounter, 1);

  return 2;
}

typedef struct NumArrayS
{
  int size;
  double values[1];
} NumArray;

static int newArray(lua_State *L)
{
  luaL_newmetatable(L, "LuaBook.array");
  lua_pop(L, 1);
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

static NumArray *checkarray(lua_State *L)
{
  void *ud = luaL_checkudata(L, 1, "LuaBook.array");
  luaL_argcheck(L, ud != NULL, 1, "array expected");

  return (NumArray *)ud;
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

static const struct luaL_Reg mylib[] = {
  {"add", add},
  {"save2RegistryIndex", save2RegistryIndex},
  {"getFromRegistryIndex", getFromRegistryIndex},
  {"saveString", saveString},
  {"getString", getString},
  {"saveRef", saveRef},
  {"getRef", getRef},
  {"getClosure", getClosure},
  {"newArray", newArray},
  {"setArray", setArray},
  {"printArray", printArray},
  {NULL, NULL}
};


extern int luaopen_mylib(lua_State *L)
{
  /* luaL_newlib(L, mylib); */
  luaL_register(L, "mylib", mylib);

  return 1;
}
