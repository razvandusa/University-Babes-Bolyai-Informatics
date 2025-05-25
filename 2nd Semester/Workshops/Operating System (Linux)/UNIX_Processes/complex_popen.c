//Write a C program that displays the user with the most processes in the system, and how many processes he or she has. Use a Shell command to find the data.
#include <stdio.h>

int main() {
	FILE* fd = popen("ps -ef | awk '{print $1}' | sort | uniq -c | sort -r | head -n 1", "r");
	int n;
	char user[64];
	fscanf(fd, "%d", &n);
	fscanf(fd, "%s", user);
	pclose(fd);
	printf("Total user with the most processes in the system is %s, with a total of %d processes\n", user, n);
}