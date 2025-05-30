#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	execlp("ls","ls","-all",NULL);
	printf("If execlp succeeds this will never be printed.\n");
}