#include "../headers/item.h"

Item::Item(const std::string& name, double price, int quantity)
    : name(name), price(price), quantity(quantity) {}

std::string Item::getName() const {
    return name;
}

double Item::getPrice() const {
    return price;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
