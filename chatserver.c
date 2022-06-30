#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

int main (int atgc, char **argv){

    struct sockaddr_in server;
    struct sockaddr_in client;
    int fd,fd2,longitud_cliente,numbytes,puerto;
    char buf[1024]; 
    char enviar2[1024];
    char enviar[1024];

    system("clear");
    printf("La direccion del servidor es 127.0.0.1\n\n");
    printf("Por favor introduzca el puerto de escucha: \n\n");
    scanf("%d", &puerto);
    server.sin_family = AF_INET;
    server.sin_port = htons(puerto);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero),8);

    if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Error de apertura de socket");
        exit(-1);
    }

    if(bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr))== -1){
        printf("error en bind()\n");
        exit(-1);
    }
    if(listen(fd,5) == -1){
        printf("error en listen()\n");
        exit(-1);
    }
    printf("SERVIDOR EN ESPERA...\n");
    longitud_cliente = sizeof(struct sockaddr_in);
    if((fd2 = accept(fd, (struct sockaddr *)&client,&longitud_cliente)) == -1){
        printf("error en accept()\n");
        exit(-1);
    }

    printf("------SESION INICIADA------\n");
    printf("CLIENTE CONECTADO\n");
    strcpy(enviar, "SERVIDOR CONECTADO");
    send(fd2,enviar,1024,0);


    while (1)
    {
        recv(fd2,buf,1024,0);
        if(strcmp(buf,"salir") == 0){
            break;
        }

        printf("Cliente: %s\n",buf);

        printf("Escribir mensaje: ");
        scanf("%*c%[^\n]", enviar2);
        send(fd2, enviar2,1024,0);
        if(strcmp(enviar2, "salir") == 0){
            break;
        }
    }

    close(fd2);
    close(fd);
    return 0;
    
}
