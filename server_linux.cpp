// server_linux.cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <set>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

std::set<int> clients;
std::mutex client_mutex;

void broadcast(const std::string& msg, int sender) {
    std::lock_guard<std::mutex> lock(client_mutex);
    for (auto client : clients) {
        if (client != sender) {
            send(client, msg.c_str(), msg.size(), 0);
        }
    }
}

void handle_client(int client) {
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
    close(client);
    std::cout << "Client disconnected.\n";
}

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    listen(server, SOMAXCONN);
    std::cout << "Server listening on port 5555...\n";

    while (true) {
        int client = accept(server, nullptr, nullptr);
        if (client < 0) continue;

        {
            std::lock_guard<std::mutex> lock(client_mutex);
            clients.insert(client);
        }
        std::cout << "New client connected.\n";
        std::thread(handle_client, client).detach();
    }

    close(server);
    return 0;
}
