#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Pizza {
private:
    std::string recipeName;
    std::vector<Ingredient> ingredients;
    double totalPrice;
    int idealBakeTime; 

public:
    Pizza();
    Pizza(const std::string& recipeName, int idealBakeTime, double totalPrice);

    void addIngredient(const Ingredient& ing);

    int getIdealBakeTime() const; 

    double getTotalPrice() const;

    std::string getRecipeName() const;

    const std::vector<Ingredient>& getIngredients() const;

    double getIngredientPlacingTime() const; // returneaza timpul total de asezare a ingredientelor pe pizza

    std::string printWithoutIngredients() const;

    bool operator==(const Pizza& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Pizza& pizza);
};

#endif // PIZZA_H