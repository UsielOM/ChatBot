#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){

    struct sockaddr_in server;
    char ip[16];
    int fd, numbytes, puerto;
    char buf[1024];

    system("clear");

    printf("ingrese la ip del servidor \n");
    scanf("%s", ip);

    printf("ingrese la ip del servidor\n");
    scanf("%s",ip);

    if((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("socket() error\n");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(puerto);
    server.sin_addr.s_addr = inet_addr(ip);
    bzero(&(server.sin_zero),8);

    if(connect(fd, (struct sockaddr *)&server,
    sizeof(struct sockaddr)) == -1){
        printf("connect () error\n");
        exit(-1);
    }

    if((numbytes=recv(fd,buf,1024,0))  == -1){
        printf("Error recv()\n");
        exit(-1);
    }
    printf("%s\n", buf);

    while (1)
    {
      printf("Escribir mensaje: ");
      scanf("%*c%[^\n]",enviar);
      send(fd,enviar,1024,0);
      if(strcmp(enviar, "salir") == 0){
        break;
      }

      recv(fd,buf,1024,0);
      if(strcmp(buf, "salir") == 0){
        break;
      }
      printg("Servidor: %s\n",buf);
    }
    close(fd);
    

}