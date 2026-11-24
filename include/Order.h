#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "Customer.h"
#include "Pizza.h"

class Order {
private:
    Customer customer;
    Pizza requestedPizza;
    int orderId;

public:
    Order();
    Order(const Customer& customer, const Pizza& requestedPizza, int orderId);

    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order(); // !!!!!!!!!!!!!!!!!!

    const Pizza& getPizza() const;
    
    const Customer& getCustomer() const;

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

#endif // ORDER_H