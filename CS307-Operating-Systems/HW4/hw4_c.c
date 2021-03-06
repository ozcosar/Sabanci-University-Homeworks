#include<stdio.h>
#include<stdlib.h>

int main(){
	char ch;
	int count;
	FILE *fp;
	fp = fopen("loremipsum.txt", "r");
	while(ch != EOF){
		ch = fgetc(fp);
		if(ch == 'a'){
			count++;
		}
	}
	printf("%d \n", count);
	fclose(fp);
	return 0;
}