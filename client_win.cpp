#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

void reader(SOCKET sock) {
    char buffer[1024];
    int bytes;
    while ((bytes = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "[remote] " << std::string(buffer, bytes) << std::endl;
    }
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (sockaddr*)&server, sizeof(server));

    std::thread t(reader, sock);

    std::string line;
    while (std::getline(std::cin, line)) {
        send(sock, line.c_str(), (int)line.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
