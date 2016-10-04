#include "bor-util.h"

int do_fork();
void execute_child();
void check_nbr_of_args(int argc);
void initialise_signal_handlers();
void catch_signal();
void send_signal(int pid);

int pid_target;

int fils_1_pid, fils_2_pid, pere_pid;

int main(int argc, char * argv[])
{

    check_nbr_of_args(argc);

    initialise_signal_handlers();

    int fils_1 = do_fork();
    int fils_2 = do_fork();

    printf("ppid : %d\nfils1 pid : %d\nfils2 pid : %d\n", getpid(), fils_1, fils_2);
    pid_target = fils_2;

    fils_1_pid = fils_1;
    fils_2_pid = fils_2;
    pere_pid = getpid();

    catch_signal();

return 0;
}

void check_nbr_of_args(int argc){
  if(argc != 1){
    perror("Nombre de paramètre incorrect , 0 attendus");
    exit(1);
  }
}

int do_fork(int pid_target){
  int result = fork();

  if(result == -1){
    perror("\nFork error");
    exit(1);
  }

  if(result == 0){
    execute_child(pid_target);
    //exit(0);
  }

  return result;
}

void execute_child(pid_target){
  initialise_signal_handlers();
  //pid_target = getpid();
}

void initialise_signal_handlers(){
  bor_signal(SIGUSR1, catch_signal, SA_RESTART);
}

void catch_signal(){
  sleep(1);
  printf("PID %d envoie SIGUSR1 à %d\n", getpid(), pid_target);
  kill(pid_target, SIGUSR1);


  if(pid_target == fils_1_pid){
    pid_target = fils_2_pid;
  } else if(pid_target == fils_2_pid){
    pid_target = pere_pid;
  } else {
    pid_target = pere_pid;
  }
}
