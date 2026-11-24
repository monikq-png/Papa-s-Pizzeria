#ifndef CONSOLE_H
#define CONSOLE_H

// afisarile cu ziua curenta, meniul zile etc.
#include "Customer.h"
#include "Pizza.h"
#include "Ingredient.h"
#include "Oven.h"
#include "Order.h"

#include <iostream>
#include <vector>
#include <iomanip>

namespace Console 
{
    void displayDayStart(int day, const std::vector<Ingredient>& unlockedIngredients);

    void displayDailyMenu(const std::vector<Pizza>& dailyMenu);

    void displayCustomerDetails(const Customer& customer);

    void displayOrderDetails(const Order& order);

    void displayIngredientTime(double time);

    double readPlayerPizza(Pizza& playerPizza, const std::vector<Ingredient>& unlockedIngredients);

    void displayOvenIN(const Pizza& pizza);

    void displayOvenOUT(const Oven& oven);

    void displayCustomerFinalComment(const Customer& customer, double ingredientAccuracy, double ovenAccuracy, double actualTime,
        const Pizza& requestedPizza);

    void displayFinalPayment(double finalPayment, double discount);

    void displayAccuracy(double ingredientAccuracy, double ovenAccuracy, double ingredientSpeedAccuracy);

    void displayEndDay(int day);

    void displayGameOver(double totalEarnings, double profit, int overallAccuracy);

    void continueToIngredients();

    void continueToOven();

    void continueToServe();

    void continueToStatitics();

    void continueToEndDay();

}

#endif