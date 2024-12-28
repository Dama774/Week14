#pragma once
#include <memory>
#include "order.hpp"

class OrderProcessor {
public:
    virtual ~OrderProcessor() = default;
    virtual void processOrder(std::shared_ptr<Order> order) = 0;
    virtual void cancelOrder(std::shared_ptr<Order> order) = 0;
};
