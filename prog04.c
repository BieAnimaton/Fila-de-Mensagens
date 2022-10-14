#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main (int argc, char * argv[]) {

  key_t   key;
  int     msgid, retorno;

  system("clear");

  key=ftok("/home",'a');

  msgid=msgget(key,0);

  if ( msgid == -1 ){
    printf("Não foi possível identificar a fila de mensagens.\n");
  } else {
    retorno=msgctl(msgid,IPC_RMID,0);
    if ( retorno == 0) {
      printf("A fila de mensagens %d foi removida.\n",msgid);
    } else {
      printf("A fila de mensagens %d não foi removida.\n",msgid);
    }
  }

  return 0;

}
