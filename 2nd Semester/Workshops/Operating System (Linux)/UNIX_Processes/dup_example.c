//Let's implement in C a program that does the equivalent of running the command ps -ef | grep -E "^root" | awk '{print $2}', by running the three programs and transferring the data between them using pipes.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int p2g[2], g2a[2];
	if (pipe(p2g) == -1) {
		printf("First pipe could not open!");
	}
	if (pipe(g2a) == -1) {
		printf("Second pipe could not open!");
	}
	if (fork() == 0) {
		close(p2g[0]); close(g2a[0]); close(g2a[1]);
		dup2(p2g[1], 1); //se va scrie in p2g[1] in loc de stdout
		close(p2g[1]);
		execlp("ps","ps","-ef",NULL);
		exit(1);
	}
	if (fork() == 0) {
		close(p2g[1]); close(g2a[0]);
		dup2(p2g[0], 0); //se va prelua input din p2g[0] in loc de stdin
		close(p2g[0]);
		dup2(g2a[1], 1); //se va scrie in g2a[1] in loc de stdout
		close(g2a[1]);
		execlp("grep","grep","-E","^root",NULL);
		exit(1);
	}
	if (fork() == 0) {
		close(p2g[0]); close(p2g[1]); close(g2a[1]);
		dup2(g2a[0],0); //se va prelua input din g2a[0] in loc de stdin
		close(g2a[0]);
		execlp("awk","awk","{print $2}",NULL);
		exit(1);
	}
	close(p2g[0]); close(p2g[1]);
	close(g2a[0]); close(g2a[1]);
	wait(0); wait(0); wait(0);
	return 0;
}