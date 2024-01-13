#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Função para processar a solicitação de login
void processarSolicitacaoLogin(int sockCliente) {
    char usuarioSenha[256];
    char resposta[256];

    // Receber nome de usuário e senha do cliente
    ssize_t bytesRecebidos = recv(sockCliente, usuarioSenha, sizeof(usuarioSenha), 0);

    if (bytesRecebidos <= 0) {
        std::cerr << "Erro ao receber dados do cliente.\n";
        return;
    }

    std::string usuarioSenhaStr(usuarioSenha, bytesRecebidos);

    if (usuarioSenhaStr == "user:password") {
        // Se o login for bem-sucedido, envie uma resposta com código de status OK
        std::strcpy(resposta, "OK");
    } else {
        // Se o login falhar, envie uma resposta com código de status FAILED
        std::strcpy(resposta, "FAILED");
    }

    // Enviar a resposta de login de volta ao cliente
    ssize_t bytesEnviados = send(sockCliente, resposta, std::strlen(resposta), 0);

    if (bytesEnviados <= 0) {
        std::cerr << "Erro ao enviar resposta ao cliente.\n";
    }

    if (usuarioSenhaStr != "user:password") {
        close(sockCliente);
    }
}

int main() {
  
    
    std::cout << "Cliente conectado.\n";

    processarSolicitacaoLogin(sockCliente);


}
