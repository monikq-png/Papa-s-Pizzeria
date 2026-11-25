#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    std::string name;
    int bakeTime;
    double price;
public:
    Ingredient();
    Ingredient(const std::string& name, int bakeTime, double price);

    const std::string& getName() const;

    int getBakeTime() const;

    double getPrice() const;

    bool operator==(const Ingredient& other) const;

    friend std::ostream& operator<<(std::ostream &os, const Ingredient& ingredient);
};

#endif 