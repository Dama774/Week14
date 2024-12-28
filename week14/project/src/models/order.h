#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <memory>
#include "user.h"

class Order {
private:
    std::string orderId;
    std::weak_ptr<User> customer;
    double totalPrice;
    std::vector<std::string> items;
    bool processed;

public:
    Order(const std::string& orderId, std::shared_ptr<User> customer, double price);
    
    void addItem(const std::string& item);
    void process();
    void displayDetails() const;
    
    std::string getOrderId() const { return orderId; }
    double getTotalPrice() const { return totalPrice; }
    std::shared_ptr<User> getCustomer() const { return customer.lock(); }
    bool isProcessed() const { return processed; }
};

#endif // ORDER_H
