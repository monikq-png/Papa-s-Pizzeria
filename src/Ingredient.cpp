#include "../include/Ingredient.h"
#include <iostream>

Ingredient::Ingredient() : name(""), bakeTime(0), price(0.0) {}

Ingredient::Ingredient(const std::string& name, int bakeTime, double price)
{
    this->name = name;
    this->bakeTime = bakeTime;
    this->price = price;
}

std::string Ingredient::getName() const {
    return name;
}

int Ingredient::getBakeTime() const {
    return bakeTime;
}

double Ingredient::getPrice() const {
    return price;
}

bool Ingredient::operator==(const Ingredient& other) const
{
    return name == other.getName();
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
    os << ingredient.name << " (+" << ingredient.bakeTime << "s, " << ingredient.price << " RON)";
    return os;
}