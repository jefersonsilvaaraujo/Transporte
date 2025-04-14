// servidor_windows_comentado.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>  // Biblioteca para programação de sockets no Windows

int main() {
    WSADATA wsa;                // Estrutura para armazenar informações da biblioteca Winsock
    SOCKET server, client;      // Descritores de socket para servidor e cliente
    struct sockaddr_in server_addr, client_addr; // Estruturas para armazenar os endereços
    int client_size;            // Tamanho do endereço do cliente
    char buffer[1024];          // Buffer para armazenar mensagens recebidas
    char *msg = "Conexao TCP com sucesso!"; // Mensagem de resposta do servidor

    // Inicializa a biblioteca Winsock versão 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erro WSAStartup\n");
        return 1;
    }

    // Cria o socket do tipo TCP (SOCK_STREAM)
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        printf("Erro ao criar socket\n");
        return 1;
    }

    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;               // Família de endereços IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;       // Aceita conexões de qualquer IP
    server_addr.sin_port = htons(8080);             // Porta 8080, convertida para ordem de rede

    // Associa o socket ao endereço configurado
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erro no bind\n");
        return 1;
    }

    // Coloca o socket em modo de escuta para aceitar conexões
    listen(server, 1);
    printf("Servidor aguardando conexao na porta 8080...\n");

    // Aguarda e aceita uma conexão de um cliente
    client_size = sizeof(client_addr);
    client = accept(server, (struct sockaddr *)&client_addr, &client_size);

    // Recebe dados do cliente
    recv(client, buffer, sizeof(buffer), 0);
    printf("Mensagem recebida: %s\n", buffer);

    // Envia resposta ao cliente
    send(client, msg, strlen(msg), 0);

    // Fecha as conexões
    closesocket(client);
    closesocket(server);
    WSACleanup();  // Finaliza a biblioteca Winsock
    system("pause");  // Pausa a execução para visualizar a saída
    return 0;
}
// Compilação: gcc servidor.c -o servidor -lws2_32