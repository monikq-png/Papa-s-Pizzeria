#ifndef GAME_H
#define GAME_H

#include "Ingredient.h"
#include "Pizza.h"
#include "Oven.h"
#include <vector>

class Game {
private:
    int currentDay;
    int totalDays;
    int orderCounter;

    double totalEarnings;
    double totalExpenses;
    double averageAccuracyFinal;
    int totalOrdersCompleted;

    Oven oven;
    std::vector<Ingredient> allIngredients;
    std::vector<Ingredient> unlockedIngredients;
    std::vector<Pizza> allRecipes;

    void initIngredients();
    void initRecipes();
    void unlockIngredientForDay(int day);
    void playDay(int day);
    void processOrder(const std::vector<Pizza>& dailyMenu);

public:
    Game();
    void run();
};

#endif // GAME_H