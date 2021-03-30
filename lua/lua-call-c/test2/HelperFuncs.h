#ifndef _STACK_DUMP_H
#define _STACK_DUMP_H

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>

  void stackDump(lua_State *L);

  void debugInfo(const char *log, const char *funcName);

#ifdef __cplusplus
}
#endif

#endif
