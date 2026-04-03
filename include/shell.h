#ifndef SHELL_H
#define SHELL_H

#include "base.h"

#define MIKUSH_VERSION "0.1.0"
#define MIKUSH_HISTORY "~/.mikush_history"
#define MIKUSH_RC      "~/.mikushrc"
#define MAX_ARGS       128

void  shell_init(void);
void  shell_loop(void);
void  shell_cleanup(void);
i32   shell_execute(char **args);
char **shell_parse(char *line);

#endif
