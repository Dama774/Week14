#include "../headers/order.h"
#include <numeric>

Order::Order(const std::string& orderID) : orderID(orderID) {}

std::string Order::getOrderID() const {
    return orderID;
}

void Order::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

std::vector<std::shared_ptr<Item>> Order::getItems() const {
    return items;
}

double Order::getTotalCost() const {
    return std::accumulate(items.begin(), items.end(), 0.0, 
        [](double sum, const std::shared_ptr<Item>& item) {
            return sum + item->getPrice() * item->getQuantity();
        });
}

void Order::setDelivery(std::shared_ptr<Delivery> newDelivery) {
    delivery = newDelivery;
}
