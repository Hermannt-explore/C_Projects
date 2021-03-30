#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#define Max_LINE 80
#define limit " \t\r\n\a"

int main(void){
	int buffer = Max_LINE/2 +1;
	int should_run = 1;
	int status;
	int i;
	char *arg;
	char **args = malloc (buffer * sizeof(char));
	char **hstry = malloc (buffer * sizeof(char));
	char **com1 = malloc (buffer * sizeof(char));
	char **com2 = malloc (buffer * sizeof(char));
	int file;

	pid_t pid, sid, pid_new;

	/*main loop*/
	while(should_run){
		int normal = 0;
		int other = 0;
		int amp_stat = 0;
		int index = 0;
		int pipe_num = 0;
		int dup_stat = 0;
		int pipe1_stat;
		int pipe2_stat;
		char *pipe_c = "|";
		char *line = NULL;
		char *comp = "!!";
		char *amp = "&";
		char *f_dir = ">";
		char *b_dir = "<";
		char *done = "exit";
		printf("mysh:~$ ");
		/*Avoids double printing*/
		fflush(stdout);
		/*buffer for line*/
		ssize_t buffer_l = 0;
		/*get line form stdin*/
		getline(&line, &buffer_l, stdin); 
		/*parses line into args*/
		arg = strtok(line, limit );
		/*enter arg in args array*/
		while(arg != NULL){
			args[index] = arg;
			index++;
			arg = strtok(NULL, limit);
		}
		/*ignore null entry*/	
		if(index == 0){continue;}
		/*sets last argument as NULL*/
		args[index]=NULL;
		if ( index != 0) {	
			if( strcmp(args[0], done) == 0){
				free(args);
				free(hstry);				
				free(com1);
				free(com2);
				should_run=0;
				exit(0);
			}
		}

		/*pipping*/
		for(i=0; i<index; i++){
			if( strcmp(args[i], pipe_c) == 0 ){
				pipe_num = 1;
			}
		}
		if(pipe_num == 1){
			com1[0]=args[0];
			com1[1]=NULL;
			for(i=0;i<index+1;i++){
				com2[i]=args[i+2];
			}
			pid = fork();
			if(pid == 0){
				file = open( "tmp", O_RDWR | O_CREAT, S_IRWXU );
				dup2(file, fileno(stdout));
				pipe1_stat = execvp(com1[0], com1);		
				if(pipe1_stat==-1){exit(0);}
				else{}
				close(file);
			}
			else if( pid!=-1 ){
				wait(NULL);
			}
			else{
				perror("Error while forking process");
			}
			pid_new = fork();
			if(pid_new == 0){
				file = open( "tmp", O_RDONLY | O_CREAT, S_IRWXU );
				dup2(file, fileno(stdin));
				pipe2_stat = execvp(com2[0], com2);		
				if(pipe2_stat==-1){exit(0);}
				else{}
				close(file);
			}
			else if( pid_new!=-1 ){
				wait(NULL);
			}
			else{
				perror("Error while forking process");
			}							
			continue;
		}		

		/*Redirection*/
		if(index >= 2){
			if( strcmp(args[index-2], f_dir) == 0){
				file = open(args[index-1], O_RDWR | O_CREAT, S_IRWXU );
				args [index-2] = NULL;
				args [index-1] = NULL;		
				pid = fork();
				if( pid == 0 ){
					dup2(file, fileno(stdout));
					dup_stat = execvp(args[0], args);
					if(dup_stat==-1){exit(0);}
					close(file);
				}
				else if( pid!=-1 ){
					wait(NULL);
				}
				else{
					perror("Error while forking process");
				}			
				continue;
			}		
			else if( strcmp(args[index-2],  b_dir) == 0){
				args [index-2] = args[index-1];
				args [index-1] = NULL;
				pid = fork();
				if( pid == 0 ){
					dup_stat = execvp(args[0], args);
					if(dup_stat==-1){exit(0);}
					close(file);
				}
				else if( pid!=-1 ){
					wait(NULL);
				}
				else{
					perror("Error while forking process");
				}
				continue;
			}
			else{}
		}

		/*Ampersant handling*/
		if( strcmp(args[index-1], amp) == 0){
			args[index-1] = NULL;
			sid = setsid ();
			if( sid == 0 ){
				amp_stat = execvp(args[0], args);
			}
			if (amp_stat == -1){exit(0);}
			continue;
		}
		
		/*General command execution*/
		pid = fork();
		if( pid == 0 ){
			if( (strcmp(args[0], comp) == 0) & (args[1] == NULL) ){
				if(hstry[0] == NULL){
					printf("No commands in history.\n");
				}
				else{
					other = execvp(hstry[0], hstry);
				}
			}
			else{
				normal = execvp(args[0], args); 
			}
		}
		else if( pid!=-1 ){
			wait(NULL);
		}
		else{
			perror("Error while forking process");
		}
		if(normal == -1 | other == -1){
			exit(0);
		}
			
		if ( index != 0) {
			if( (strcmp(args[0], comp) != 0) ){
				for(i=0; i<index+1; i++){
					memcpy(hstry, args, (buffer*sizeof(char)));
				}
			}
		}
		else{
		}
	}
	return 0;
}
