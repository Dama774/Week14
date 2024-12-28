#include "order.h"
#include <iostream>

Order::Order(const std::string& orderId, std::shared_ptr<User> customer, double price)
    : orderId(orderId), customer(customer), totalPrice(price), processed(false) {}

void Order::addItem(const std::string& item) {
    items.push_back(item);
}

void Order::process() {
    processed = true;
}

void Order::displayDetails() const {
    std::cout << "Order ID: " << orderId << "\n";
    if (auto cust = customer.lock()) {
        std::cout << "Customer: " << cust->getName() << "\n";
    }
    std::cout << "Total Price: $" << totalPrice << "\n";
    std::cout << "Status: " << (processed ? "Processed" : "Pending") << "\n";
    
    if (!items.empty()) {
        std::cout << "Items:\n";
        for (const auto& item : items) {
            std::cout << "- " << item << "\n";
        }
    }
}
