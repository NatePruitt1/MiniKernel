#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ACK 0x06 //Acknowledge
#define EOT 0x04 //End of text
#define SOT 0x00 //Start of text
                 //
static const char ack = ACK;
static const char end_of_text = EOT; 
static const char start_of_text = 0;

static char* args[] = {
  "qemu-system-aarch64",
  "-M", "raspi3",
  "-serial", "null",
  "-serial", "stdio",
  "-kernel", "natekernel.elf",
  0
};

int shell_to_em[2];
int em_to_shell[2];

void emulator_start();
void shell_start();
void send_byte(char* c);
int read_transmission(char* buffer, size_t buf_size);
//Takes stdin and attempts to push it all into stdout, but only after a 'ok' character is echoed back
//the format means that we wait until this character is received, meaning that on the other side, there will 
//be no lost data. After data is sent and the sending buffer is over, we wait for more characters to enter 
//stdin, or for more characters to come out of the emulator
int main() {
  //create two pipes
  pipe(shell_to_em);
  pipe(em_to_shell);
  int pid = fork();
  switch(pid) {
    case 0:
      //child
      emulator_start();
      break;
    case -1:
      exit(-1);
    default:
      shell_start();
  }
}

void emulator_start() {
  //close the read end of emulator to shell
  close(em_to_shell[0]);
  close(shell_to_em[1]);
  dup2(shell_to_em[0], 0);
  dup2(em_to_shell[1], 1);
  execvp(args[0], args);
}

void shell_start() {
  close(em_to_shell[1]);
  close(shell_to_em[0]);
  
  int status = 0;
  char recv;
  char* line;
  size_t size;
  char send_buff;

  write(shell_to_em[1], &ack, 1);

  read(em_to_shell[0], &recv, 1);

  if(recv != ACK){
    //big error
    exit(-1);
  }

  while(status == 0){
    size_t len = getline(&line, &size, stdin);
    //send with wait
    for(int i = 0; i < len; i++) {
      send_buff = line[i];
      write(shell_to_em[1], &send_buff, 1);

      read(em_to_shell[0], &recv, 1);
      if(recv != ACK) {
        exit(-1);
      }
    }

    write(shell_to_em[1], &end_of_text, 1);

    read(em_to_shell[0], &recv, 1);
    if(recv != SOT) {
      exit(-1);
    }


  }
}
