#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/shell.h"
#include <unistd.h>
#include <sys/wait.h>



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

    // builtin: exit
    if (strcmp(args[0], "exit") == 0) {
        shell_cleanup();
        exit(0);
    }

    // builtin: cd
    if (strcmp(args[0], "cd") == 0) {
        const char *dir = args[1] ? args[1] : getenv("HOME");
        if (chdir(dir) != 0)
            perror("mikush: cd");
        return 1;
    }

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

  while (1) {
    line = readline("\001\033[38;2;57;197;187m\002🌸 ミク ❯\001\033[0m\002 ");
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
