#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>

int main(){
	unsigned char *f;
	int size,count;
	struct stat s;
	int fd = open("loremipsum.txt",O_RDONLY);
	int status = fstat(fd,&s);
	size = s.st_size;
	f = (char*) mmap(0,size,PROT_READ,MAP_PRIVATE,fd,0);
	int i;
	for(i = 0; i < size; i++){
		char ch;
		ch = f[i];
		if(ch == 'a'){
			count++;
		}
	}
	printf("%d \n", count);
	close(fd);
	return 0;
}