#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in endereco;
    int tam_cliente;
    char buffer[1024];
//servidor web simples em C utilizando HTML e JavaScript
    const char *resposta_http =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html>"
        "<html><head><title>Exemplo</title>"
        "<style>body{font-family:sans-serif;text-align:center;margin-top:50px;}</style>"
        "<script>function ola(){alert('Ola do JavaScript!');}</script>"
        "</head><body>"
        "<h1>Servidor em C respondendo HTML!</h1>"
        "<button onclick='ola()'>Clique aqui</button>"
        "</body></html>";

    WSAStartup(MAKEWORD(2, 2), &wsa);

    servidor = socket(AF_INET, SOCK_STREAM, 0);

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(8080);

    bind(servidor, (struct sockaddr *)&endereco, sizeof(endereco));
    listen(servidor, 1);
    printf("Servidor HTTP escutando na porta 8080...\n");

    tam_cliente = sizeof(endereco);
    cliente = accept(servidor, (struct sockaddr *)&endereco, &tam_cliente); //realiza a aceitação de conexões (handshake)

    recv(cliente, buffer, sizeof(buffer), 0);
    printf("Requisicao recebida:\n%s\n", buffer);

    send(cliente, resposta_http, strlen(resposta_http), 0);

    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();
    system("pause");
    return 0;
}

// Compilar com o comando:
// gcc servidor-web.c -o servidor-web.exe -lws2_32
// Executar o servidor:
// servidor-web.exe
// Acessar o servidor no navegador:
// http://localhost:8080