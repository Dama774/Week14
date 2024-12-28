#pragma once
#include <string>

class Item {
private:
    std::string name;
    double price;
    int quantity;

public:
    Item(const std::string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }
};
