#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    int bakeTime;
    double price;
    std::string name;
public:
    Ingredient();
    Ingredient(const std::string& name, int bakeTime, double price);

    std::string getName() const;

    int getBakeTime() const;

    double getPrice() const;

    bool operator==(const Ingredient& other) const;

    friend std::ostream& operator<<(std::ostream &os, const Ingredient& ingredient);
};

#endif 