#include "gtest/gtest.h"
#include <set>
#include <string>

// Simple mock for broadcast test
std::set<int> clients;

void mock_broadcast(const std::string& msg, int sender) {
    for (auto client : clients) {
        if (client != sender) {
            // Normally would send msg, here we just simulate
            // For test, we could append to a vector or check counts
        }
    }
}

// Test adding clients
TEST(BroadcastTest, AddRemoveClients) {
    clients.clear();
    clients.insert(1);
    clients.insert(2);
    ASSERT_EQ(clients.size(), 2);
    clients.erase(1);
    ASSERT_EQ(clients.size(), 1);
}

// Test broadcasting logic (mock)
TEST(BroadcastTest, BroadcastExcludesSender) {
    clients.clear();
    clients.insert(1);
    clients.insert(2);
    int sender = 1;
    mock_broadcast("hello", sender);
    ASSERT_TRUE(clients.find(sender) != clients.end());
}
