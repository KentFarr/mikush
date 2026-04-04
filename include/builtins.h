#ifndef BUILTINS_H
#define BUILTINS_H

#include "base.h"

// ANSI colors
#define COLOR_RESET   "\033[0m"
#define COLOR_MIKU    "\033[38;2;57;197;187m"   // teal — directories
#define COLOR_GREEN   "\033[38;2;80;200;120m"    // executables
#define COLOR_YELLOW  "\033[38;2;255;215;100m"   // symlinks
#define COLOR_PINK    "\033[38;2;255;121;198m"   // special files
#define COLOR_DIM     "\033[38;2;100;100;100m"   // hidden files

#define LS_MAX_SHOWN  20
#define MAX_ALIASES   100


typedef struct { 
  char *name; 
  char *description;
  i32 (*func)(char **);
} Builtin;



typedef struct {
  char *name; 
  char *value; 

} Alias; 



i32 run_builtin(char **args);
i32 is_builtin(char *name);
i32 builtin_cd(char **args);
i32 builtin_pwd(char **args);
i32 builtin_history(char **args);
i32 builtin_alias(char **args);
i32 builtin_unalias(char **args);
i32 builtin_help(char **args);
i32 builtin_sing(char **args);
i32 builtin_miku(char **args);  

#endif
