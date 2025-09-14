#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <set>

#pragma comment(lib, "Ws2_32.lib")

std::set<SOCKET> clients;
std::mutex client_mutex;

void broadcast(const std::string& msg, SOCKET sender) {
    std::lock_guard<std::mutex> lock(client_mutex);
    for (auto client : clients) {
        if (client != sender) {
            send(client, msg.c_str(), (int)msg.size(), 0);
        }
    }
}

void handle_client(SOCKET client) {
    char buffer[1024];
    int bytes;
    while ((bytes = recv(client, buffer, sizeof(buffer), 0)) > 0) {
        std::string msg(buffer, bytes);
        broadcast(msg, client);
    }
    {
        std::lock_guard<std::mutex> lock(client_mutex);
        clients.erase(client);
    }
    closesocket(client);
    std::cout << "Client disconnected.\n";
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, SOMAXCONN);

    std::cout << "Server listening on port 5555...\n";

    while (true) {
        SOCKET client = accept(server, nullptr, nullptr);
        if (client == INVALID_SOCKET) break;

        {
            std::lock_guard<std::mutex> lock(client_mutex);
            clients.insert(client);
        }
        std::cout << "New client connected.\n";
        std::thread(handle_client, client).detach();
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
