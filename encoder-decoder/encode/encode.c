#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void main(){
int i=0;
int j;
int k;
int key;
char c;
char d;
char e;
FILE *in;
FILE *read;
FILE *out;
FILE *prnt;

in = fopen("in.txt", "w");
out = fopen("output.txt", "w");
while( (c=fgetc(stdin)) != '\n') { 
	fputc ( c, in);	
}
scanf("%d", &key);
fclose(in);

read = fopen("in.txt", "r");
while( (d=fgetc(read)) != EOF) { 
	if(i< key){
		fputc(d, out);
	}
	else{
		fprintf(out, "\n");
		fputc(d, out);
		i=0;
	}
	i++;
}
fclose(read);
fclose(out);

k=0;
prnt = fopen("output.txt", "r");
for(i=0; i<key; i++){
	j=0;
	lseek (fileno(prnt), 0, SEEK_SET);
	while( (e=fgetc(prnt)) != EOF){
		if( j==k){
			printf("%c", e);
		}
		if(j == 22){
			j=0;
			continue;
		}
		j=j+ sizeof(char);
	}		
	k++;
}
fclose(prnt);
}
