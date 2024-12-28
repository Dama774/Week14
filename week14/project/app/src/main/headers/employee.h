#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "user.h"
#include "order.h"

class Employee : public User {
public:
    Employee(const std::string& name, const std::string& userID);

    void placeOrder(std::shared_ptr<Order> order) override;
    void processOrder(std::shared_ptr<Order> order) override;

    void processPayment(std::shared_ptr<Order> order);
    void shipOrder(std::shared_ptr<Order> order);
};

#endif // EMPLOYEE_H
