#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    std::string name;
    double tolerance;

public:
    Customer();
    Customer(const std::string& name, double tolerance);

    std::string getName() const;

    double getTolerance() const;

    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
};

#endif