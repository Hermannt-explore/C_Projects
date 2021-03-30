#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Function declarations
void triangle (int lines);
void diamond (int lines);
void hexagon (int lines);

//structure
typedef struct commands {
	int lines [20];
	char shape [11] [20];
}command;

void main(){
//declare variables
int lines;
int num;
int i;
char h[2][8]={"hexagon", "Hexagon"};
char t[2][9]={"triangle", "Triangle"};
char d[2][8]={"diamond", "Diamond"};
char shape[11];
char * point=shape;
//Welcome message
printf("Welcome to Shape drawer!\n");
sleep(1);	       	
printf("This tool can draw triangles, diamonds and hexagons.\n");
sleep(2);
//Prompt for number of shapes to be drawn
printf("How many shapes would you like to draw? ");
//scan for number of shapes
scanf("%d", &num);
//create the structure
command c;
//push data in struct
for (i=0; i<num; i++){
	//promp for shape name
	printf("Enter shape name number %d. ", i+1);
	scanf("%s", shape);
	//promp for number of lines
	printf("Enter number of lines for shape number %d. ", i+1);
	scanf("%d", &lines);
	c.lines[i] = lines;
	strcpy(c.shape[i], point);
}
//determine which function to call
for (i=0; i<num; i++){
	if ( (strcmp(c.shape[i], t[0]) == 0) || (strcmp(c.shape[i], t[1]) == 0)){
		triangle((int) c.lines[i]);
	}
	else if( (strcmp(c.shape[i], d[0]) == 0) || (strcmp(c.shape[i], d[1]) == 0) ){
		diamond((int) c.lines[i]);
	}
	else if( (strcmp(c.shape[i], h[0]) == 0) || (strcmp(c.shape[i], h[1]) == 0) ){
		hexagon((int) c.lines[i]);
	}
	else{
	exit;
	}
}
}

//triangle function 
void triangle(int lines){
int i;
int j;
int k;
int spaces;
int stars;
spaces = lines-1;
stars = 1;
for(i=0; i<lines; i++){
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for(k=0; k<stars; k++){
		printf("* ");
	}
	printf("\n");
	spaces =spaces-1;
	stars = stars +1;
}
printf("\n");
}

//diamond function
void diamond(int lines){
int i;
int j;
int k;
int spaces;
int stars;
spaces = (lines/2);
stars = 1;
printf("\n");
for(i=0; i<(lines/2)+1; i++){
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for(k=0; k<stars; k++){
		printf("* ");
	}
	printf("\n");
	spaces = spaces-1;
	stars = stars+1;
}
spaces=1;
stars=stars - 2;
for(i=0; i<(lines/2); i++){
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for(k=0; k<stars; k++){
		printf("* ");
	}
	printf("\n");
	spaces = spaces+1;
	stars = stars -1;
}
printf("\n");
}

//hexagon function
void hexagon(int lines){
int i;
int j;
int k;
int spaces;
int stars;

if (lines == 1 ){
printf("*");
printf("\n");}
else if(lines == 2){
printf(" * *");
printf("\n");}
else if( lines%2 == 0 ){
spaces = (lines/2)-1;
stars=lines/2;

for(i=0; i<(lines/2); i++){	
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for (k=0; k<stars; k++){
		printf(" *");
	}
	printf("\n");
	spaces-=1;
	stars+=1;
}
spaces+=1;
stars-=1;
for(i=0; i<(lines/2); i++){
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for (k=0; k<stars; k++){
		printf(" *");
	}
	printf("\n");
	spaces+=1;
	stars-=1;
}

}//end else if
else if ( lines%2 == 1 ){
spaces = lines/2;
stars=spaces+1;

for(i=0; i<(lines/2)+1; i++){	
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for (k=0; k<stars; k++){
		printf("* ");
	}
	printf("\n");
	spaces-=1;
	stars+=1;
}
spaces+=2;
stars-=2;
for(i=0; i<(lines/2); i++){
	for(j=0; j<spaces; j++){
		printf(" ");
	}
	for (k=0; k<stars; k++){
		printf("* ");
	}
	printf("\n");
	spaces+=1;
	stars-=1;
}

}//end else if
else{
printf("\n");
}
}//end hex function
