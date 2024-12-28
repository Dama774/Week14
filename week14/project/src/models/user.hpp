#pragma once
#include <string>
#include <memory>
#include "order.hpp"

class User {
protected:
    std::string name;
    std::string userID;

public:
    User(const std::string& name, const std::string& userID) 
        : name(name), userID(userID) {}

    virtual ~User() = default;

    virtual void placeOrder(std::shared_ptr<Order> order) = 0;
    virtual void processOrder(std::shared_ptr<Order> order) = 0;

    std::string getName() const { return name; }
    std::string getUserID() const { return userID; }
};
