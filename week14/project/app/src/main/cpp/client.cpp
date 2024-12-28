#include "../headers/client.h"
#include <iostream>

Client::Client(const std::string& name, const std::string& userID, const std::string& clientID)
    : Customer(name, userID), clientID(clientID) {}

void Client::processOrder(std::shared_ptr<Order> order) {
    std::cout << "Client " << name << " processing order " << order->getOrderID() << std::endl;
}

void Client::cancelOrder(std::shared_ptr<Order> order) {
    std::cout << "Client " << name << " cancelling order " << order->getOrderID() << std::endl;
}

std::string Client::getClientID() const {
    return clientID;
}
