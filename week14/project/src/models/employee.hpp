#pragma once
#include "user.hpp"

class Employee : public User {
public:
    Employee(const std::string& name, const std::string& userID) 
        : User(name, userID) {}

    void placeOrder(std::shared_ptr<Order> order) override {
        // Логика размещения заказа сотрудником
        std::cout << "Employee " << name << " placing order " << order->getOrderID() << std::endl;
    }

    void processOrder(std::shared_ptr<Order> order) override {
        // Логика обработки заказа сотрудником
        std::cout << "Employee " << name << " processing order " << order->getOrderID() << std::endl;
    }

    void processPayment(std::shared_ptr<Order> order) {
        // Логика обработки платежа
        std::cout << "Employee " << name << " processing payment for order " << order->getOrderID() << std::endl;
    }

    void shipOrder(std::shared_ptr<Order> order) {
        // Логика отправки заказа
        std::cout << "Employee " << name << " shipping order " << order->getOrderID() << std::endl;
    }
};
