#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "order.h"

class Customer : public User {
public:
    Customer(const std::string& name, const std::string& userID);

    void placeOrder(std::shared_ptr<Order> order) override;
    void processOrder(std::shared_ptr<Order> order) override;

    void makePayment(std::shared_ptr<Order> order);
};

#endif // CUSTOMER_H
