// client_linux.cpp
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void reader(int sock) {
    char buffer[1024];
    int bytes;
    while ((bytes = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "[remote] " << std::string(buffer, bytes) << std::endl;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    std::thread t(reader, sock);

    std::string line;
    while (std::getline(std::cin, line)) {
        send(sock, line.c_str(), line.size(), 0);
    }

    close(sock);
    t.join();
    return 0;
}
