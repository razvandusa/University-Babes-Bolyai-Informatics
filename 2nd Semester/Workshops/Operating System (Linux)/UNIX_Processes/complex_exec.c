#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (fork() == 0) {
		printf("Child process starts\n");
		if(execlp("ps","ps","-f",NULL) == -1) {
			printf("Exec did not work!\n");
			exit(0);
		}
	}
	if (fork() == 0) {
                printf("Child process starts\n");
                if(execl("/bin/ps","/bin/ps","-f",NULL) == -1) {
                        printf("Exec did not work!\n");
                        exit(0);
                }
        }
	if (fork() == 0) {
                printf("Child process starts\n");
		char* a[] = {"ps","-f",NULL};
                if(execvp("ps", a) == -1) {
                        printf("Exec did not work!\n");
                        exit(0);
                }
        }
	if (fork() == 0) {
                printf("Child process starts\n");
		char* a[] = {"/bin/ps","-f",NULL};
                if(execv("/bin/ps", a) == -1) {
                        printf("Exec did not work!\n");
                        exit(0);
                }
        }
	wait(0); wait(0); wait(0); wait(0);
	printf("Parent process finished\n");
}