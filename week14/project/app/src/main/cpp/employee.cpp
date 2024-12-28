#include "../headers/employee.h"
#include <iostream>

Employee::Employee(const std::string& name, const std::string& userID)
    : User(name, userID) {}

void Employee::placeOrder(std::shared_ptr<Order> order) {
    std::cout << "Employee " << name << " placing order " << order->getOrderID() << std::endl;
}

void Employee::processOrder(std::shared_ptr<Order> order) {
    std::cout << "Employee " << name << " processing order " << order->getOrderID() << std::endl;
}

void Employee::processPayment(std::shared_ptr<Order> order) {
    std::cout << "Employee " << name << " processing payment for order " << order->getOrderID() << std::endl;
}

void Employee::shipOrder(std::shared_ptr<Order> order) {
    std::cout << "Employee " << name << " shipping order " << order->getOrderID() << std::endl;
}
