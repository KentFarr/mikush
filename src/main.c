#include <stdio.h>
#include <stdlib.h>
#include "../include/shell.h"

int main(void) {
    shell_init();
    shell_loop();
    shell_cleanup();
    return 0;
}
