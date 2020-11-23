#include<stdio.h>
#include<stdlib.h>


void main(){

int i;
int j;
int k;
int key;
char c;
FILE *in;
FILE *out;

in = fopen("input.txt", "w");


while( (c=fgetc(stdin)) != '\n'){
	fputc (c, in);
}
//scan for decode key
scanf("%d", &key);






}
