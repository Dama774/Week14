#ifndef ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_H

#include <memory>
#include "order.h"

class OrderProcessor {
public:
    virtual ~OrderProcessor() = default;
    virtual void processOrder(std::shared_ptr<Order> order) = 0;
    virtual void cancelOrder(std::shared_ptr<Order> order) = 0;
};

#endif // ORDER_PROCESSOR_H
