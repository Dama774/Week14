#ifndef USER_H
#define USER_H

#include <string>
#include <memory>
#include "order.h"

class User {
protected:
    std::string name;
    std::string userID;

public:
    User(const std::string& name, const std::string& userID);
    virtual ~User() = default;

    virtual void placeOrder(std::shared_ptr<Order> order) = 0;
    virtual void processOrder(std::shared_ptr<Order> order) = 0;

    std::string getName() const;
    std::string getUserID() const;
};

#endif // USER_H
