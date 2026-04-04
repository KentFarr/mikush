#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/shell.h"
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "../include/builtins.h"
#include <linux/limits.h>


void shell_init(void){
  using_history();
  read_history(MIKUSH_HISTORY);

  printf("\033[38;2;57;197;187m");
  printf("  mikush v%s — 🌸 ようこそ\n", MIKUSH_VERSION);
  printf("\033[0m\n");

}


void shell_cleanup(void) {
  write_history(MIKUSH_HISTORY);
}



char **shell_parse(char *line) {
  char **args = malloc(MAX_ARGS * sizeof(char*));
  if (!args) return NULL;

  i32 i = 0;
  char *token = strtok(line, " \t\r\n");
  while (token && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \t\r\n");
  }
  args[i] = NULL;
  return args;

}

i32 shell_execute(char **args) {
    if (!args || !args[0]) return 1;

    if (strcmp(args[0], "cd")   == 0) return builtin_cd(args);
    if (strcmp(args[0], "history") == 0) return builtin_history(args);
    if (strcmp(args[0], "alias") == 0) return builtin_alias(args);
    if (strcmp(args[0], "unalias") == 0) return builtin_unalias(args);
    if (strcmp(args[0], "pwd")  == 0) return builtin_pwd(args);
    if (strcmp(args[0], "help") == 0) return builtin_help(args);
    if (strcmp(args[0], "sing") == 0) return builtin_sing(args);
    if (strcmp(args[0], "miku") == 0) return builtin_miku(args);
    if (strcmp(args[0], "exit") == 0) { shell_cleanup(); exit(0); }

    pid_t pid = fork();

    if (pid == 0) {
      execvp(args[0], args);
      perror("mikush");
      exit(1);
    } else if (pid > 0) {
      i32 status; 
      waitpid(pid, &status, 0);
    } else {
      perror("mikush: fork");
      return 1; 
    }

    return 0; 
}



void shell_loop(void) {
  char *line;
  char **args;
  char cwd[PATH_MAX];
  char prompt[PATH_MAX + 64];

  while (1) {
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      strcpy(cwd, "?");
    const char *home = getenv("HOME");
    const char *display = cwd;
    char tilde_cwd[PATH_MAX];
    if (home && strncmp(cwd, home, strlen(home)) == 0) {
      snprintf(tilde_cwd, sizeof(tilde_cwd), "~%s", cwd + strlen(home));
      display = tilde_cwd;
    }
    snprintf(prompt, sizeof(prompt),
      "\001\033[38;2;57;197;187m\002%s\001\033[0m\002 🌸 ミク ❯ ", display);
    line = readline(prompt);
    if (!line) {
      printf("\n");
      break;
    }

    if (*line) {
      add_history(line);
      args = shell_parse(line);
      shell_execute(args);
      free(args);
    }
    free(line);
  }
}
