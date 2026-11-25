#include "../include/Order.h"

Order::Order() : orderId(0) {}

Order::Order(const Customer& customer, const Pizza& requestedPizza, int id)
{
    this->customer = customer;
    this->requestedPizza = requestedPizza;
    this->orderId = id;
}

Order::Order(const Order& other) 
    : customer(other.customer), requestedPizza(other.requestedPizza), orderId(other.orderId) {}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        customer = other.customer;
        requestedPizza = other.requestedPizza;
        orderId = other.orderId;
    }
    return *this;
}

Order::~Order() {}

const Pizza& Order::getPizza() const {
    return requestedPizza;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "ORDER #" << order.orderId;
    return os;
}