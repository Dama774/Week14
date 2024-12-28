#include "user.h"

User::User(const std::string& name, const std::string& userID) 
    : name(name), userID(userID) {}

std::string User::getName() const { 
    return name; 
}

std::string User::getUserID() const { 
    return userID; 
}

Customer::Customer(const std::string& name, const std::string& userID, double discount)
    : User(name, userID), discountRate(discount) {}

void Customer::applyDiscount(double rate) {
    discountRate = rate;
}

void Customer::displayInfo() const {
    std::cout << "Customer: " << name << " (ID: " << userID 
              << ", Discount: " << discountRate << "%)\n";
}

Employee::Employee(const std::string& name, const std::string& userID)
    : User(name, userID) {}

void Employee::processOrder(std::shared_ptr<Order> order) {
    // Обработка заказа
}

void Employee::displayInfo() const {
    std::cout << "Employee: " << name << " (ID: " << userID << ")\n";
}
