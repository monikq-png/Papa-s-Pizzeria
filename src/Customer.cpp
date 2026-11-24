#include "../include/Customer.h"
#include <cmath>

Customer::Customer() : name("Unknown"), tolerance(1.0) {}

Customer::Customer(const std::string& name, double tolerance)
{
    this->name = name;
    this->tolerance = tolerance;   
}

std::string Customer::getName() const {
    return name;
}

double Customer::getTolerance() const {
    return tolerance;
}

std::ostream& operator<<(std::ostream& os, const Customer& customer) {
    os << "Customer " << customer.name;
    return os;
}