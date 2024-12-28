#pragma once
#include "order_processor.hpp"
#include "customer.hpp"

class Client : public Customer, public OrderProcessor {
private:
    std::string clientID;

public:
    Client(const std::string& name, const std::string& userID, const std::string& clientID)
        : Customer(name, userID), clientID(clientID) {}

    void processOrder(std::shared_ptr<Order> order) override {
        // Логика обработки заказа
        std::cout << "Client " << name << " processing order " << order->getOrderID() << std::endl;
    }

    void cancelOrder(std::shared_ptr<Order> order) override {
        // Логика отмены заказа
        std::cout << "Client " << name << " cancelling order " << order->getOrderID() << std::endl;
    }

    std::string getClientID() const { return clientID; }
};
