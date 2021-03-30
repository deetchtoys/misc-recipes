#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdlib.h>

#include "HelperFuncs.h"

typedef struct Account{
  int age;
  int sex;
  int nameLen;
  char name[1];
}Account;

static int newInstance(lua_State *L)
{
  int age = luaL_checkint(L, 1);
  int sex = luaL_checkint(L, 2);
  int nameLen = luaL_checkint(L, 3);
  int memSize = sizeof(Account) + (nameLen - 1) * sizeof(char);
  void *instance = lua_newuserdata(L, memSize);
  luaL_argcheck(L, instance != NULL, -1, "failed new userdata");
  Account *account = (Account *)instance;
  account->age = age;
  account->sex = sex;
  account->nameLen = nameLen;
  luaL_getmetatable(L, "TEST2.Acount");
  lua_setmetatable(L, -2);

  return 1;
}

static Account *checkType(lua_State *L)
{
  void *account = lua_touserdata(L, 1);
  luaL_argcheck(L, account != NULL, 1, "account expected");

  return (Account *)account;
}

static int getField(lua_State *L)
{
  Account *account = checkType(L);
  const char *fieldName = luaL_checkstring(L, 2);
  if (strcmp("age",fieldName) == 0)
  {
    lua_pushinteger(L, account->age);
  }
  else if (strcmp("sex",fieldName) == 0)
  {
    lua_pushinteger(L, account->sex);
  }
  else if (strcmp("nameLen",fieldName) == 0)
  {
    lua_pushinteger(L, account->nameLen);
  }
  else if (strcmp("name",fieldName) == 0)
  {
    lua_pushstring(L, account->name);
  }

  return 1;
}


static int setField(lua_State *L)
{
  Account *account = checkType(L);
  const char *fieldName = luaL_checkstring(L, 2);
  const char *isOk = "success";
  if (strcmp("age",fieldName) == 0)
  {
    int age = luaL_checkint(L, 3);
    account->age = age;
  }
  else if (strcmp("sex",fieldName) == 0)
  {
    int sex = luaL_checkint(L, 3);
    account->sex = sex;
  }
  else if (strcmp("name",fieldName) == 0)
  {
    const char *name = luaL_checkstring(L, 3);
    strncpy(account->name, name, account->nameLen - 1);
  }
  else
  {
    isOk = "failed";
  }

  lua_pushstring(L, isOk);
  return 1;
}


static int tostring(lua_State *L)
{
  Account *account = checkType(L);
  /* char buff[255]; */
  /* memset(buff, 255, sizeof(char)); */
  /* sprintf(buff,                                                         \ */
  /*         "age:%d\n"                                                    \ */
  /*         "sex:%d\n"                                                    \ */
  /*         "nameLen:%d\n"                                                \ */
  /*         "name:%s\n", account->age, account->sex, account->nameLen, account->name); */
  /* debugInfo(buff, "tostring"); */
  /* lua_pushstring(L, buff); */
  lua_pushfstring(L,
                  "age:%d\n"                                            \
                  "sex:%d\n"                                            \
                  "nameLen:%d\n"                                        \
                  "name:%s\n", account->age, account->sex, account->nameLen, account->name);
  return 1;
}

static const struct luaL_Reg accountSelfMethod[] = {
  {"getField", getField},
  {"setField", setField},
  {"__tostring", tostring},
  {NULL, NULL}
};

static const struct luaL_Reg accountPubMethod[] = {
  {"newInstance", newInstance},
  {NULL, NULL}
};


extern int luaopen_Account(lua_State *L)
{
  luaL_newmetatable(L, "TEST2.Acount");
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, accountSelfMethod);
  luaL_register(L, "Account", accountPubMethod);

  return 1;
}
