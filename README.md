# Fila de Mensagens
Códigos feitos em C para criar uma Fila de Mensagens, além de escrever, ler e apagar o conteúdo.

# Observações adicionais:
Para compilar: `cc progN.c -o progN`  
Para executar: `./progN`  
Obter informações do IPC (semáforos, memória compartilhada e filas de mensagens): `ipcs`

## Bibliotecas:
`#include <unistd.h>`  
`#include <sys/ipc.h>`  
`#include <sys/msg.h>`

## Criando variáveis.
```
key_t  key;
int    msgid;
```
- "key" do tipo "key_t" para armazenar a chave hexadecimal de acesso do segmento.
- "msgid" para armazenar o endereço (id) da fila.

## Comando para criar uma chave hexadecimal.
```
...
key=ftok("/tmp",'a');
...
```
Os parâmetros são: nome do diretório de armazenamento e nome arquivo de armazenamento.

## Comando para **criar** uma fila de mensagens.
```
...
msgid=msgget(key, 0600|IPC_CREAT);
...
```
Os parâmetros são: variável da chave e permissões para a fila junto do comando de criar.

- **OBSERVAÇÃO: O comando msgget() pode ser usado também apenas para descobrir se uma fila existe.**

## Comando para **descobrir** uma fila de mensagens.
```
...
msgid=msgget(key, tamanho, 0);
...
```
Os parâmetros são: variável da chave e 0.

- Se o msgget não conseguir criar ou descobrir o segmento de memória, irá retorna -1, caso contrári, irá retorna qualquer outro valor.
**Os comandos de descobrir e criar chave são usados em todos os programas, porém decidi ocultá-los para melhor explicação dos outros**.

## Comando para **escrever** alguma mensagem na fila de mensagens(P1 - Produtor).
```
...
char mensagem[80];
...
if ( msgid == -1 ){
   printf("Não foi possível identificar a fila de mensagens.\n");
} else {
   printf("Digite a mensagem: ");
   gets(mensagem);
   msgsnd(msgid,mensagem,sizeof(mensagem),0);
}
...
```
O comando msgsnd envia a mensagem para a fila.  
Os parâmetros são: o endereço (id) do segmento, variável com a mensagem, tamanho da mensagem e 0.
- Função Produtor.
- Neste código, estamos obtendo a mensagem do usuário através da função `gets`, passando para a variável `mensagem` e então colocando na fila.
- **A vantagem da Fila de Mensagens é podermos enviar N mensagens e as mesmas não se sobreporem, pois são colocadas em fila.**

## Comando para **ler** uma fila de mensagens(P1 - Consumidor).
```
...
if ( msgid == -1 ){
   printf("Não foi possível identificar a fila de mensagens.\n");
} else {
   msgrcv(msgid,mensagem,sizeof(mensagem),0,0);
   printf("Recuperei a mensagem %s da fila %d.\n",mensagem,msgid);
}
...
```
O comando msgrcv **RECUPERA** e **APAGA** a mensagem da fila.  
Os parâmetros são: o endereço (id) do segmento, variável para salvar a mensagem, tamanho da mensagem, 0 e 0.
- Função Consumidor.
- Código deve ser repetido para imprimir as N mensagens ques estão na fila
- Caso não tenha mensagens na fila, tela do terminal fica vazia esperando que surja alguma mensagem para impressão.

## Comando para **remover** uma fila de mensagens.
```
...
msgctl(msgid,IPC_RMID,0);
...
```
Este comando examina e modificar a fila.  
Os parâmetros são: endereço (id) do segmento, ação que desejar executar e 0.
- A instrução IPC_RMID é a responsável pela remoção.# Fila-de-Mensagens
