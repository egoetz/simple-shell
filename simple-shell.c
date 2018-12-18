#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


/* Acts as a simple shell to process commands with up to 64 args.
 * Precondition: None.
 * Postcondition: The main process does not return  The user must terminate it.
 * However, its children will return 1 if the command they were given is not
 * recognized or 0 if they were able to exit successfully.
 * Side effects: Whenever a command is entered into the shell prompt, the current
 * process will attempt to create a new process to run the command. This will
 * produce any side effects that command might have.
*/
int main() {
    size_t nbytes = 0;
    char *string = NULL;
    char *space = " ";
    fprintf(stderr, "input> ");
    while(getline(&string, &nbytes, stdin) != -1){
        string[strlen(string) - 1] = '\0';
        char *ptr = strtok(string, space);
        char *argv[66];
        int count = 0;
        while(ptr != NULL && count < 65){
            argv[count] = ptr;
            ptr = strtok(NULL, space);
            count++;
        }
        if(ptr != NULL){
            fprintf(stderr, "Warning: More than 64 arguments passed, ignoring arguments " \
            "from %s onwards...\n", ptr);
        }
        argv[count] = NULL;

        pid_t pid = fork();
        if(pid == 0){
            if(execvp(argv[0], argv) == -1){
                fprintf(stderr, "Error: The command %s could not be found.\n", argv[0]);
                return 1;
            }
        }
        else{
            int status;
            waitpid(pid, &status, 0);
            fprintf(stderr, "<exit status %d>\n", WEXITSTATUS(status));
            fprintf(stderr, "input> ");

        }

    }

    return 0;
}
