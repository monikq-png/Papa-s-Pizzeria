#ifndef SERVICES_H
#define SERVICES_H

#include "Customer.h"
#include "Pizza.h"
#include "Ingredient.h"
#include "Order.h"
#include "Oven.h"

#include <vector>
#include <cstdlib>
#include <string>

namespace Services 
{
    Customer getRandomCustomer();

    Order getRandomOrder(const Customer& customer, const std::vector<Pizza>& dailyMenu, int orderId);

    std::vector<Pizza> getDailyMenu(const std::vector<Ingredient>& unlockedIngredients, 
        const std::vector<Pizza>& allRecipes);

    double getIngredientAccuracy(const Pizza& requestedPizza, const Pizza& actualPizza);
    
    bool hasIngredient(const std::vector<Ingredient>& ingredients, const std::string& ingredientName);

    double getOvenAccuracy(const Pizza& requestedPizza, const Oven& oven);

    double getIngredientSpeedAccuracy(double expectedPlacingTime, double actualPlacingTime);
    
    double getBakeDiscount(double idealTime, double ovenAccuracy, double toleranceLevel, double ingredientAccuracy, const Pizza& requestedPizza);

    double getFinalPayment(double expectedPayment, double discount);

    // functie care sa verifice daca un ingredient exista
}

#endif