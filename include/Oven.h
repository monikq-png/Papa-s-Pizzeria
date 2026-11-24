#ifndef OVEN_H
#define OVEN_H

#include <iostream>

class Oven {
private:
    double ovenTime;

public:
    Oven();

    void bakePizza();

    double getOvenTime() const;

    friend std::ostream& operator<<(std::ostream& os, const Oven& oven);
};

#endif // OVEN_H