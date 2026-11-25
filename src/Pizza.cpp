#include "../include/Pizza.h"
#include <iostream>

Pizza::Pizza() : recipeName(""), idealBakeTime(0), totalPrice(0.0) {}

Pizza::Pizza(const std::string& recipeName, int idealBakeTime, double totalPrice)
{
    this->recipeName = recipeName;
    this->idealBakeTime = idealBakeTime;
    this->totalPrice = totalPrice;
}

void Pizza::addIngredient(const Ingredient& ingredient) 
{
    ingredients.push_back(ingredient);
}

int Pizza::getIdealBakeTime() const 
{
    int totalTime = 0; // timpul de baza pentru coacerea
    for (const Ingredient& ingredient : ingredients) {
        totalTime += ingredient.getBakeTime();
    }
    return totalTime;
} 

double Pizza::getIngredientPlacingTime() const {
    double totalPlacingTime = 0.0;
    for (std::size_t i = 0; i < ingredients.size(); i++) {
        totalPlacingTime += 2; // presupunem ca fiecare ingredent dureaza vreo 2 s sa fie tastat
    }
    return totalPlacingTime;
}

double Pizza::getTotalPrice() const {
    double total = 10; // pretul de baza dupa care facem si profit
    for (const Ingredient& ingredient : ingredients) {
        total += ingredient.getPrice();
    }
    return total;
} 

const std::string& Pizza::getRecipeName() const {
    return recipeName;
}

const std::vector<Ingredient>& Pizza::getIngredients() const {
    return ingredients;
}

bool Pizza::operator==(const Pizza& other) const 
{
    if (ingredients.size() != other.ingredients.size()) {
        return false;
    }

    for (const auto& ing : ingredients) {
        bool found = false;
        for (const auto& otherIng : other.ingredients) {
            if (ing.getName() == otherIng.getName()) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

std::string Pizza::printWithoutIngredients() const {
    return "Pizza " + recipeName;
}


std::ostream& operator<<(std::ostream& os, const Pizza& pizza) {
    os << "Pizza " << pizza.recipeName << std::endl << "(" << pizza.getTotalPrice() << " RON)" <<" - ";
    for (size_t i = 0; i < pizza.ingredients.size(); i++) {
        os << pizza.ingredients[i];
        if (i < pizza.ingredients.size() - 1) os << ", ";
    }
    return os;
}