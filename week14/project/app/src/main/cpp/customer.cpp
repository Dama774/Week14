#include "../headers/customer.h"
#include <iostream>

Customer::Customer(const std::string& name, const std::string& userID)
    : User(name, userID) {}

void Customer::placeOrder(std::shared_ptr<Order> order) {
    std::cout << "Customer " << name << " placing order " << order->getOrderID() << std::endl;
}

void Customer::processOrder(std::shared_ptr<Order> order) {
    std::cout << "Customer " << name << " processing order " << order->getOrderID() << std::endl;
}

void Customer::makePayment(std::shared_ptr<Order> order) {
    std::cout << "Customer " << name << " making payment for order " << order->getOrderID() << std::endl;
}
