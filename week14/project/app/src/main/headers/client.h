#ifndef CLIENT_H
#define CLIENT_H

#include "customer.h"
#include "order_processor.h"

class Client : public Customer, public OrderProcessor {
private:
    std::string clientID;

public:
    Client(const std::string& name, const std::string& userID, const std::string& clientID);

    void processOrder(std::shared_ptr<Order> order) override;
    void cancelOrder(std::shared_ptr<Order> order) override;

    std::string getClientID() const;
};

#endif // CLIENT_H
