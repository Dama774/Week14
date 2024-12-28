#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "item.hpp"

class Delivery; // Предварительное объявление

class Order {
private:
    std::string orderID;
    std::vector<std::shared_ptr<Item>> items;
    std::shared_ptr<Delivery> delivery;

public:
    Order(const std::string& orderID) : orderID(orderID) {}

    std::string getOrderID() const { return orderID; }

    void addItem(std::shared_ptr<Item> item) {
        items.push_back(item);
    }

    std::vector<std::shared_ptr<Item>> getItems() const { return items; }

    double getTotalCost() const {
        return std::accumulate(items.begin(), items.end(), 0.0, 
            [](double sum, const std::shared_ptr<Item>& item) {
                return sum + item->getPrice() * item->getQuantity();
            });
    }

    void setDelivery(std::shared_ptr<Delivery> newDelivery) {
        delivery = newDelivery;
    }
};
