#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000];

    // Crea el socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("No se pudo crear el socket");
    }

    // Especifica la dirección IP y el puerto del servidor al que se conectará
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Cambia la dirección IP aquí
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 ); // Cambia el puerto aquí

    // Conecta al servidor remoto
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("Error al conectar");
        return 1;
    }

    puts("Conectado\n");

    // Envía datos al servidor
    message = "Hola, servidor!\n";
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        puts("Error al enviar");
        return 1;
    }

    puts("Datos enviados\n");

    // Recibe respuesta del servidor
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        puts("Error al recibir");
        return 1;
    }

    puts("Respuesta recibida\n");
    puts(server_reply);

    close(socket_desc);
    return 0;
}
