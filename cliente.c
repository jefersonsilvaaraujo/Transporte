// cliente_windows_comentado.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>  // Biblioteca para programação de sockets no Windows

int main() {
    WSADATA wsa;           // Estrutura para armazenar dados da biblioteca Winsock
    SOCKET sock;           // Socket do cliente
    struct sockaddr_in server;  // Estrutura para o endereço do servidor
    char buffer[1024] = {0};    // Buffer para armazenar a resposta do servidor

    // Inicializa a biblioteca Winsock versão 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erro WSAStartup\n");
        return 1;
    }

    // Cria um socket TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Erro ao criar socket\n");
        return 1;
    }

    // Configura o endereço do servidor (localhost:127.0.0.1 e porta 8080)
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conecta ao servidor
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Erro na conexao\n");
        return 1;
    }

    // Envia mensagem ao servidor
    send(sock, "Ola servidor!", strlen("Ola servidor!"), 0);

    // Recebe resposta do servidor
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Resposta do servidor: %s\n", buffer);

    // Encerra o socket e a biblioteca
    closesocket(sock);
    WSACleanup();
    system("pause");  // Pausa a execução para visualizar a saída
    return 0;
}
// gcc cliente.c -o cliente.exe -lws2_32