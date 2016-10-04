#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void check_nbr_of_args(int argc);
void process_child_1(int * pipe_1);
void process_child_2(int * pipe_1, int * pipe_2);
void process_parent(int * pipe_1, int * pipe_2);
void fork_error_test(int fork);

int main (int argc, char * argv[])
{
  check_nbr_of_args(argc);

  int my_pipe_1[2], my_pipe_2[2];

  pipe(my_pipe_1);
  pipe(my_pipe_2);

  int p1, p2;

  p1 = fork();
  fork_error_test(p1);

  if(p1 == 0){//FILS1
    process_child_1(my_pipe_1);
  }

  p2 = fork();
  fork_error_test(p2);

  if(p2 == 0){//FILS2
    process_child_2(my_pipe_1, my_pipe_2);
  }

  process_parent(my_pipe_1, my_pipe_2);

  exit(0);

}

void process_child_1(int * pipe_1){
  close(pipe_1[0]);
  dup2(pipe_1[1], 1);

  execlp("ls", "ls", "-t", NULL);
  printf("ls err");
}

void process_child_2(int * pipe_1, int * pipe_2){
  close(pipe_1[1]);
  dup2(pipe_1[0], 0);

  close(pipe_2[0]);
  dup2(pipe_2[1], 1);

  execlp("sort", "sort", NULL);
  printf("sort err");
}

void process_parent(int * pipe_1, int * pipe_2){
  close(pipe_1[0]);
  close(pipe_1[1]);
  dup2(pipe_2[0], 0);

  execlp("head", "head", "-3", NULL);
  printf("head err");

}

void check_nbr_of_args(int argc){
  if (argc != 1) {
    printf("Should have 0 params");
    exit(1);
  }
}

void fork_error_test(int fork){
  if(fork < 0){
    perror("fork");
    exit(1);
  }
}
