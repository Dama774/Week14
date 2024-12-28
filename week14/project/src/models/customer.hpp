#pragma once
#include "user.hpp"

class Customer : public User {
public:
    Customer(const std::string& name, const std::string& userID) 
        : User(name, userID) {}

    void placeOrder(std::shared_ptr<Order> order) override {
        // Логика размещения заказа клиентом
        std::cout << "Customer " << name << " placing order " << order->getOrderID() << std::endl;
    }

    void processOrder(std::shared_ptr<Order> order) override {
        // Логика обработки заказа клиентом
        std::cout << "Customer " << name << " processing order " << order->getOrderID() << std::endl;
    }

    void makePayment(std::shared_ptr<Order> order) {
        // Логика оплаты заказа
        std::cout << "Customer " << name << " making payment for order " << order->getOrderID() << std::endl;
    }
};
