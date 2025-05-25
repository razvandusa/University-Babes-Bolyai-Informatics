#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int a[4] = {2, 5, 3 ,7};
	int p[2];
	pipe(p);
	if (fork() == 0) {
		close(p[0]);
		a[0] = a[0] + a[1];
		write(p[1], &a[0], sizeof(int));
		close(p[1]);
		exit(0);
	}
	close(p[1]);
	a[2] = a[2] + a[3];
	wait(0);
	read(p[0], &a[0], sizeof(int));
	close(p[0]);
	a[2] = a[2] + a[0];
	printf("The sum is : %d\n", a[2]);
}