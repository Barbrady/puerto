#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

int main() {
    int server_fd, client_fd, valread;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    
    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Asociar el socket con la dirección del servidor
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Escuchar por conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Servidor esperando conexiones en el puerto %d...\n", PORT);
    
    // Aceptar una conexión entrante
    if ((client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    
    // Leer el mensaje enviado por el cliente
    valread = read(client_fd, buffer, 1024);
    printf("Mensaje recibido: %s\n", buffer);
    
    // Cerrar los sockets
    close(client_fd);
    close(server_fd);
    
    return 0;
}
