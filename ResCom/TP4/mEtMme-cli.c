#include "bor-util.h"

typedef struct {
  char* listen_pipe_name;
  int listen_pipe;
  char* pipe_to_server_name;
  char* pipe_from_server_name;
  int pipe_to_server;
  int pipe_from_server;
} Client;

void check_nbr_of_args(int);
int create_service_pipes(Client *);
int contact_with_server(Client *);
int open_services_pipe(Client *);
void start_dialog(Client *);
void close_services_pipe(Client *);
void unlink_services_pipe(Client *);

int main(int argc, char* argv[]){

  Client* param = malloc(sizeof(Client));

  check_nbr_of_args(argc);

  param->listen_pipe_name = argv[1];

  if(create_service_pipes(param) < 0){
    perror("create_service_pipes error:");
    exit(-1);
  }

  if(contact_with_server(param) < 0){
    perror("contact_with_server error:");
    goto end;
  }

  if(open_services_pipe(param) < 0){
    perror("open_services_pipe error:");
    goto end;
  }

  start_dialog(param);

  close_services_pipe(param);

  end:
  unlink_services_pipe(param);

  exit(0);
}

void check_nbr_of_args(int argc){

  if(argc != 2){
      printf("Syntax error: mEtMme-cli <listen_pipe_name>\n");
      exit(1);
  }

}

int create_service_pipes(Client *param){

  param->pipe_to_server_name = malloc(sizeof(char) * 100);
  param->pipe_from_server_name = malloc(sizeof(char) * 100);

  sprintf(param->pipe_to_server_name, "tub-cs-%d", (int) getpid());
  sprintf(param->pipe_from_server_name, "tub-sc-%d", (int) getpid());

  if(mkfifo(param->pipe_to_server_name, 0644) < 0)
    return -1;

  if(mkfifo(param->pipe_from_server_name, 0622) < 0){
    unlink(param->pipe_to_server_name);
    return -1;
  }

  return 0;
}

int contact_with_server(Client *param){
  char msg[200];

  sprintf(msg, "%s %s", param->pipe_to_server_name, param->pipe_from_server_name);

  param->listen_pipe = open(param->listen_pipe_name, O_WRONLY);

  if(param->listen_pipe < 0){

    return -1;
  }

  int n = bor_write_str(param->listen_pipe, msg);

  return (n <= 0 ? -1 : 0);
}

int open_services_pipe(Client *param){

  param->pipe_to_server = open(param->pipe_to_server_name, O_WRONLY);

  if(param->pipe_to_server < 0)
    return -1;

  param->pipe_from_server = open(param->pipe_from_server_name, O_RDONLY);

  if(param->pipe_from_server < 0){
    close(param->pipe_to_server);
    return -1;
  }

  return 0;
}

void start_dialog(Client *param){
  char buffer[200];

  while(1){
    int length = bor_read(0, buffer, 200);

    if(length <= 0)
      break;

    int sent = bor_write(param->pipe_to_server, buffer, length);

    if(sent <= 0)
      break;

    length = bor_read(param->pipe_from_server, buffer, 200);

    if(length <= 0)
      break;

    bor_write(1, buffer, length);
  }
}

void close_services_pipe(Client *param){

  close(param->pipe_to_server);
  close(param->pipe_from_server);

}

void unlink_services_pipe(Client *param){

  unlink(param->pipe_to_server_name);
  unlink(param->pipe_from_server_name);

}
