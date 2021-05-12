#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Include our own header files */
#include "parser.h"

#define VERSION "1.0"
#define PROMPT ">"

int main(int argc, char *argv[])
{
  /* The shell functions as an infinite loop
     * until interrupted. */
  while (1)
  {
    int argc = 0;
    pid_t cpid;
    /* TODO: Print the prompty string using PROMPT constant */
    printf("%s", PROMPT);

    /* Read a line from terminal and tokenize it from spaces into
         * an array of strings. */
    char **argv = shell_process_line(&argc);
    /* If argv == NULL, the user just pressed Enter key without any
         * command. */

    if (argv)
    {
      /* TODO: Add support for exit and version commands.
             *
             * if argv[0] is "version" or "exit", you have to process
             * them right here. */

      if (strcmp(argv[0], "version") == 0)
      {
        /* TODO: If command == version, print the version
                 * of the shell. Example usage scenario from terminal:
                 *
                 * > version
                 * GSU Shell Version: ...
                 *
                 * Version is defined as VERSION symbolic constant
                 * in the beginning of this .c file.
                 *
                 * Also, free the argv array using
                 * the relevant function from parser.c
                 * */
        printf("GSU Shell Version: %s\n", VERSION);
      }

      else if (strcmp(argv[0], "exit") == 0)
      {
        /* TODO */
        /* If command == exit, you should terminate
                 * the shell using exit(). The return value should denote
                 * a success (0 or EXIT_SUCCESS).
                 *
                 * You also have to free the argv array using
                 * the relevant function from parser.c before exiting.
                 */

        printf("Returning back to the main shell that GSU Shell runs on...\n");
        return EXIT_SUCCESS;
      }

      /* If the typed command is not a built-in one (like exit or
             * version), you have to fork a new process and the new child
             * process should execute the given command using execvp().
             *
             */
      else
      {
        /* This is to store the PID of the child process */
        pid_t child_pid = -1;

        /* TODO: Now it's time to fork! Go back to TP from moodle if you
                 * do not understand the below switch structure.
                 */
        switch (child_pid = fork())
        {
        case -1:
          perror("fork");
          break;
        case 0:
          /*****************/
          /* Child process */
          /*****************/
          /* TODO: Child process should now execute the program.
                         * You should also give all the arguments with the
                         * command.
                         * Example:
                         * > ls -l --color
                         * After you read this line with shell_process_line,
                         * you have argv  = {"ls", "-l", "--color", NULL}
                         * When you execvp(), make sure you pass the
                         * parameters correctly! */
          execvp(argv[0], argv);

          /* TODO: If the code reaches here, it means that execvp()
                         * failed for some reason. Investigate errno
                         * variable and print the problem.
                         *
                         * errno is a global variable which is modified by
                         * various library functions to report the cause of
                         * error. You can look at the related man page
                         * to see the error constants that can be returned by
                         * exec() call family.
                         *
                         * Find out the reason of problem by looking at the global variable errno.
                         *
                         * If errno == EACCES (Execute permission is not set), you should print:
                         *   Permission denied.
                         * If errno == ENOENT (The file does not exist), you should print:
                         *   Command not found.
                         *
                         * In the first case the child process should exit
                         * with the return code 126 whereas in the second case
                         * 127.
                         */
          if (errno == EACCES)
          {
            printf("Persmission denied.\n");
            exit(126);
          }
          else if (errno == ENOENT)
          {
            printf("The file does not exist.\n");
            exit(127);
          }

          /* TODO: Free argv array. */
          shell_free_args(argv);

          /* TODO: Exit with the relevant status code. */
          exit(0);
          break;

        default:
          /******************/
          /* Parent process */
          /******************/

          /* TODO: No need for the argv array in the parent process. Free it. */
          shell_free_args(argv);

          /* Define variables status and child_retval */
          int status;
          int child_retval = -1;

          /* TODO: Wait for the forked child to complete. */

          while ((cpid = waitpid(child_pid, &status, 0)) > 0)
          {
          }
          child_retval = status;
          /* TODO: If the child process exited normally
                         * store the return value of the child process into
                         * child_retval variable (See TP1) */
          if (WIFSIGNALED(child_retval))
          {
            printf("Error:%d\n", WTERMSIG(child_retval));
          }
          else if (WIFEXITED(child_retval))
          {
            printf("Exited Normally and WEXITSTATUS:%d\n", WEXITSTATUS(child_retval));
          }
          break;
        } /* switch */
      }   /* else */
    }     /* if (argv) */
  }       /* while(1) */

  return 0;
}
