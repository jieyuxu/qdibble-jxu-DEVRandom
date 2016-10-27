#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int random_num() {
	int rand_file = open("/dev/random", O_RDONLY);
	int buff;
	int read_ = read(rand_file, &buff, 4);
	close(rand_file);
	return buff;
}

int main() {
	umask(0000);
	int i, buff, fd, fd2;

	int nums_initial[10];
	int nums_final[10];
	printf("Generating Random Numbers:\n");
	fd = open("output.txt", O_CREAT|O_WRONLY, 0666);
	for (i = 0; i < 10; i++) {
		nums_initial[i] = random_num();
		buff = nums_initial[i];
		write(fd, &buff, sizeof(buff));
		printf("\t random %d:\t%d\n", i, nums_initial[i]);
	}
	close(fd);

	printf("writing numbers to file...\n");
	printf("reading numbers from file...\n");
	printf("verification that written values were the same\n");
	
	fd2 = open("output.txt", O_RDONLY);
	for (i = 0; i < 10; i++){
		read(fd2, &buff, sizeof(buff));
		nums_final[i] = buff;
		printf("\t random %d:\t%d\n", i, nums_final[i]);
	}

	return 0;

}

