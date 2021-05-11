#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

/**
 * This file contains helper functions for command-line
 * parsing which are used by the main shell code and/or
 * other functions.
 */

/**
 * Reads a line from standard input and returns tokens out of it.
 *
 * shell_process_line() reads a line from standard input
 * (max size 2048 bytes) and returns an array of
 * tokens.
 *
 * @param argc Address of an integer to be filled
 * with the number of arguments parsed.
 *
 * @return Array of strings containing the space-delimited
 * words read from command-line. NULL if only newline \n
 * has been entered.
 */
char** shell_process_line(int *argc) {
    /* Reads a new line of maximum size 2048 bytes */
    char line[2048];
    char **argv = NULL;
    if (fgets(line, sizeof(line), stdin)) {
        if (line[0] != '\n') {
            int i;
            int nr_args = 1;

            /* Smash the newline character */
            line[strlen(line) - 1] = '\0';

            /* First count the number of spaces to find
             * the number of arguments */
            for (i = 0; line[i] != '\0'; ++i) {
                if (line[i] == ' ') {
                    nr_args++;
                }
            }

            *argc = nr_args;

            /* Now allocate an array of strings. The +1
             * is for the termination NULL ptr. */
            argv = malloc(sizeof(char *) * (nr_args + 1));
            if (argv) {
                char *token = strtok(line, " ");
                i = 0;
                while (token) {
                    argv[i++] = strdup(token);
                    token = strtok(NULL, " ");
                }
                /* Put a NULL at the end */
                argv[i] = NULL;
            }
            else {
                perror("malloc");
            }
        }
    }
    return argv;
}

/**
 * Free the argv array previously allocated.
 *
 * shell_free_args() traverses the array of string argv
 * and frees its members. It finally frees the **argv
 * pointer.
 *
 * @param argv Array of list to be freed.
 */
void shell_free_args(char **argv) {
    int i = 0;
    while (argv[i]) {
        free(argv[i++]);
    }
    free(argv);
}


