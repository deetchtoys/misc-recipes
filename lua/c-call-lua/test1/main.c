#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* void error(lua_State *L, const char *fmt, ...) */
/* { */
/*   va_list argp; */
/*   va_start(argp, fmt); */
/*   vfprintf(stderr, argp); */
/*   va_end(argp); */
/*   lua_close(L); */
/*   exit(EXIT_FAILURE); */
/* } */


int getField(lua_State *L, const char *fieldName, void *value)
{
  lua_pushstring(L, fieldName);
  lua_gettable(L, -2);
  if (!lua_isnumber(L, -1))
  {
    printf("`%s' should be a number\n", fieldName);
    return -1;
  }
  double *tmpValue = (double *)value;
  *tmpValue = (double)lua_tonumber(L, -1);
  lua_pop(L, 1);
  return 0;
}

void test1()
{
  char *filename = "tabVar.lua";
  int width = 0;
  int height = 0;
  lua_State *L = luaL_newstate();
  /* luaopen_base(L); */
  /* luaopen_io(L); */
  /* luaopen_string(L); */
  /* luaopen_math(L); */

  luaL_openlibs(L);

  if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
  {
    printf("cannot run configuration file: %s", lua_tostring(L, -1));
    exit(-1);
    lua_close(L);
  }

  lua_getglobal(L, "width");
  if (!lua_isnumber(L, -1))
  {
    printf("`width' should be a number\n");
    exit(-1);
    lua_close(L);
  }
  width = (int)lua_tonumber(L, -1);

  lua_getglobal(L, "height");
  if (!lua_isnumber(L, -1))
  {
    printf("`height' should be a number\n");
    exit(-1);
    lua_close(L);
  }
  height = (int)lua_tonumber(L, -1);

  lua_getglobal(L, "background");
  if (!lua_istable(L, -1))
  {
    printf("`height' should be a table\n");
    exit(-1);
    lua_close(L);
  }
  double r = 0, g = 0, b = 0;
  getField(L, "r", (void *)(&r));
  getField(L, "g", (void *)(&g));
  getField(L, "b", (void *)(&b));

  printf("%d ---- %d ---- %f ---- %f ---- %f\n",width, height, r, g, b);
  lua_close(L);
}

#define MAX_COLOR 10

typedef struct ColorTableS {
  char *name;
  unsigned char red, green, blue;
} ColorTableT;

int setField(lua_State *L, const char *index, int value)
{
  lua_pushstring(L, index);
  lua_pushnumber(L, (double)value/MAX_COLOR);
  lua_settable(L, -3);

  return 0;
}

void setcolor(lua_State *L, ColorTableT *ct)
{
  lua_newtable(L);
  setField(L, "r", ct->red);
  setField(L, "g", ct->green);
  setField(L, "b", ct->blue);
  lua_setglobal(L, ct->name);
}

void test2()
{
  ColorTableT colortable[] = {
    {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"RED", MAX_COLOR, 0, 0},
    {"GREEN", 0, MAX_COLOR, 0},
    {"BLUE", 0, 0, MAX_COLOR},
    {"BLACK", 0, 0, 0},
    {NULL, 0, 0, 0},
  };


  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  int i = 0;
  while (colortable[i].name != NULL)
  {
    setcolor(L, &colortable[i++]);
  }


  lua_getglobal(L, "background");
}

int main(void)
{
  test1();
  return 0;
}
