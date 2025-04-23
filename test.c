#include <unistd.h>
#include <stdio.h>

int main(int, char **argv) {
	char path[500] = {0};
	getcwd(path, 499);
	printf("%s\n", path);	
	chdir(argv[1]);
	getcwd(path, 499);
	printf("%s\n", path);
	return (0);
}
