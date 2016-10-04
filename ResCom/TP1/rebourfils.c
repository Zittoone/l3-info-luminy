#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void check_nbr_of_args(int argc);
void read_key();
void do_fork();
void execute_child();
void wait_childs();

int main(int argc, char * argv[])
{
  check_nbr_of_args(argc);
  read_key();

  return 0;
}

void check_nbr_of_args(int argc){
  if(argc != 1){
    perror("Nombre de paramètre incorrect , 0 attendus");
    exit(1);
  }
}

void read_key(){

int c;

scanf(" %d", &c);

  while (c != 0) {
    for (int i = 0; i < c; i++) {
      do_fork();
    }

    scanf(" %d", &c);
  }

  wait_childs();
}

void do_fork(){
  int result = fork();

  if(result == -1){
    perror("\nFork error");
    exit(1);
  }

  if(result == 0){
    execute_child();
    exit(0);
  }
}

void execute_child(){

  for (int i = 10; i > 0; i--) {
    printf("PID %d : %d\n", getpid(), i);
    sleep(1);
  }
}

void wait_childs() {
  while (waitpid(-1, NULL, 0)) {
   if (errno == ECHILD) {
      break;
   }
 }
}
