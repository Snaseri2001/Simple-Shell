#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include<unistd.h>
#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"

char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);
char *prompt  ;
char *abc[100];

void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C \n");


}

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int dash_execute(char **args ) {
  pid_t cpid;
  int status;



   FILE *fPtr;

    char dataToAppend[100] = "the instruction  is change the dirctory " ;
    fPtr = fopen("/home/soroush/Desktop/CPrograms/shell_Project/history.txt", "a");
    int counter = 0  ;
    while(args[counter] != NULL){
     fprintf(fPtr, "%s ", args[counter]);
     counter++ ;
    }
    fprintf(fPtr, "\n");
    fclose(fPtr) ;

//......................exit ......................
  if (strcmp(args[0], "exit") == 0) {

    return 0;
  }
//..................................................

//....... read instructions from another file ..............
 if(strcmp(args[0] , "bash") == 0 ){

 FILE* file = fopen(args[1], "r");

if(!file){
printf(" there is not any diroctory \n" );
return 1;
}

char *line[100] ;
int counter = 0 ;
while (fgets(line, sizeof(line), file) ) {
args = split_line(line);

dash_execute(args );


counter++ ;
}


fclose(file);
exit(0) ;





 }




//.......................................................




//..................change directory ................
if(strcmp(args[0] , "cd")==0){


    int i =  chdir(args[1] ) ;
    if(i < 0){
    return 1;
   }else{
      printf("change directory secsseful \n") ;
      prompt = args[1] ;
     return 1;
}
}

if(strcmp(args[0] , "echo") == 0 ){
  int counter = 1  ;
      while(args[counter] != NULL){


     printf("%s " , args[counter]  ) ;
     counter += 1 ;
  }
  printf("\n") ;
 return 1 ;
}
 cpid = fork() ;
  if (cpid == 0) {



if(strcmp(args[0] , "history")==0){

 FILE* file = fopen( "/home/soroush/Desktop/CPrograms/shell_Project/history.txt","r");

if(!file){
printf(" there is not any diroctory \n" );
return 1;
}

char *line[100] ;
int counter = 0 ;
while (fgets(line, sizeof(line), file) ) {
printf("%s " , line) ;

counter++ ;
}


fclose(file);
return 0 ;

}



if(strcmp(args[0] , "pipe")==0){


 int pipefd[2];
 int childpid,childpid2;
 char* cmd[3]={args[1],NULL,NULL};
 char* cmd2[3]={args[2],args[3],NULL};
 pipe(pipefd);
 if(childpid=fork()){
   //parent
   close(pipefd[1]);
   dup2(pipefd[0],STDIN_FILENO);
   execvp(cmd2[0],cmd2);
 }else{
   //child
   //write
   close(pipefd[0]);
   dup2(pipefd[1],STDOUT_FILENO);
   execvp(cmd[0], cmd);
 }
 return 0;
}





if(strcmp(args[0]  , "mkdir") == 0){

      int check;

    char* dirname =args[1];


    check = mkdir(dirname,0770);

  //   check if directory is created or not
    if (!check)
        printf("Directory created\n");
    else {
        printf("Unable to create directory\n");



    }

    return 0 ;
    }













 if (execvp(args[0], args) < 0){
      printf(" dash: command not found: %s\n", args[0]);
    exit(1) ;
}



  }else if (cpid < 0){
    printf(RED "Error forking"RESET "\n");
 } else {
    waitpid(cpid, & status, WUNTRACED);
    }
  return 1;
}

int dash_exit(char **args) {
  return 0;
}

char **split_line(char * line) {
  int buffsize = 1024 , position = 0;
  char **tokens = malloc(buffsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
    exit(EXIT_FAILURE);
  }
  token = strtok(line, TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= buffsize) {
      buffsize += 1024 ;
      tokens = realloc(tokens, buffsize * sizeof(char * ));

      if (!tokens) {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;

  return tokens;
}
char *read_line() {
  int buffsize = 1024;
  int position = 0;
  char *buffer = malloc(sizeof(char) * buffsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      if(position == 0 ){
     buffer[position] = "aa";
    }else{
      buffer[position] = '\0';
      }
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= buffsize) {
      buffsize += 1024;
      buffer = realloc(buffer, buffsize);
      if (!buffer) {
        fprintf(stderr, "dash: Allocation error\n");
        exit(EXIT_FAILURE);

      }
    }
  }
}

void loop() {
  char *line;
  char **args;
// signal(SIGINT, sigintHandler);
  int status = 1;

  do {


     printf("%s @user > " ,prompt);

    line = read_line();
    args = split_line(line);
    status = dash_execute(args );




  } while (status);
}

int main() {
 signal(SIGINT, sigintHandler);
  //signal(SIGINT, intHandler);


//   while () {
  loop();
///}
  return 0;
}

