#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "item.h"

class Delivery; // Предварительное объявление

class Order {
private:
    std::string orderID;
    std::vector<std::shared_ptr<Item>> items;
    std::shared_ptr<Delivery> delivery;

public:
    Order(const std::string& orderID);

    std::string getOrderID() const;
    void addItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Item>> getItems() const;
    double getTotalCost() const;
    void setDelivery(std::shared_ptr<Delivery> newDelivery);
};

#endif // ORDER_H
