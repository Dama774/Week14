#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    double price;
    int quantity;

public:
    Item(const std::string& name, double price, int quantity);

    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setQuantity(int newQuantity);
};

#endif // ITEM_H
