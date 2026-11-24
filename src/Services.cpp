#include "../include/Customer.h"
#include "../include/Pizza.h"
#include "../include/Ingredient.h"
#include "../include/Order.h"
#include "../include/Services.h"
#include "../include/Oven.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

namespace Services {

    Customer getRandomCustomer()
    {
        std::string names[] = {"Stefan", "Maria", "Atasiei", "Ioana", "Alex", "Elena", 
            "Mihai", "Ana", "Vlad", "Gabriela", "Cristian", "Monica", "Florin", "Alina", "Darius", "Simona",
            "Bogdan", "Camelia", "Radu", "Adriana", "George", "Xenia", "Patricia", "Lucian"};

        double tolerance[] = {0.5, 0.75, 1.0, 1.0, 1.0, 1.25, 1.5}; 
        // maresc sansele de a avea toleranta 1.0, pentru ca e cea mai comuna

        int indexNames = std::rand() % 24;
        int indexTolerance = std::rand() % 7;

        return Customer(names[indexNames], tolerance[indexTolerance]);
    }

    Order getRandomOrder(const Customer& customer, const std::vector<Pizza>& dailyMenu, int orderId)
    {
        int indexPizza = std::rand() % dailyMenu.size();
        return Order(customer, dailyMenu[indexPizza], orderId);
    }

    bool hasIngredient(const std::vector<Ingredient>& ingredients, const std::string& ingredientName) {
        for (const auto& ingredient : ingredients) {
            if (ingredient.getName() == ingredientName) 
                return true; 
        }
        
        return false;
    }

    std::vector<Pizza> getDailyMenu(const std::vector<Ingredient>& unlockedIngredients, 
        const std::vector<Pizza>& allPizzas)
    {
        std::vector<Pizza> availableRecipes;

        for (const auto& pizza : allPizzas) 
        {
            bool canMake = true;
            for (const auto& ingredient : pizza.getIngredients()) 
            {
                if (!hasIngredient(unlockedIngredients, ingredient.getName())) 
                {
                    canMake = false;
                    break;
                }
            }

            if (canMake) {
                availableRecipes.push_back(pizza);
            }
        }
        return availableRecipes;
    }

    double getIngredientSpeedAccuracy(double expectedPlacingTime, double actualPlacingTime)
    {
        if (expectedPlacingTime <= 0.0) {
            return 1.0;
        }

        if (actualPlacingTime <= expectedPlacingTime) {
            return 1.0;
        }

        const double delay = actualPlacingTime - expectedPlacingTime;
        const double accuracy = 1.0 - (delay / expectedPlacingTime);

        return std::max(0.0, accuracy);
    }

    double getIngredientAccuracy(const Pizza& requestedPizza, const Pizza& actualPizza)
    {
        const auto& requested = requestedPizza.getIngredients();
        const auto& actual = actualPizza.getIngredients();

        size_t maxIngredients = std::max(requested.size(), actual.size());
        if (maxIngredients == 0) {
            return 1.0;
        }

        int correctCount = 0;
        std::vector<bool> used(actual.size(), false);

        for (const auto& reqIng : requested) {
            for (size_t i = 0; i < actual.size(); ++i) {
                if (!used[i] && reqIng.getName() == actual[i].getName()) {
                    correctCount++;
                    used[i] = true; 
                    break; // de implementat pizze double de exemplu double cheese sau extra peperoni etc
                }
            }
        }

        return static_cast<double>(correctCount) / maxIngredients;
    }

    double getOvenAccuracy(const Pizza& requestedPizza, const Oven& oven)
    {
        double idealBakeTime = requestedPizza.getIdealBakeTime();
        double actualBakeTime = oven.getOvenTime();

        double timeDifference = std::abs(idealBakeTime - actualBakeTime);
        double accuracy = 1.0 - (timeDifference / idealBakeTime);

        if (accuracy < 0.0) accuracy = 0.0;

        return accuracy;
    }

    double getBakeDiscount(double actualTime, double ovenAccuracy, double toleranceLevel, double ingredientAccuracy, 
        const Pizza& requestedPizza)
    {
        double idealTime = requestedPizza.getIdealBakeTime() + requestedPizza.getIngredientPlacingTime();

        // presupunem ca toti clientii cu toleranta 1.0 pot accepta o intarziere de 10% din timpul ideal total
        double acceptableOverallDelay = (0.1 * idealTime) * toleranceLevel;

        double discount = 0;

        if (ovenAccuracy >= 0.90) {
            discount = 0.0;  // perfecta
        } else if (ovenAccuracy >= 0.75) {
            discount = 0.05; // 5%, usor necoapta / well-done
        } else if (ovenAccuracy >= 0.50) {
            discount = 0.15; // 15%, destul de arsa / cruda
        } else {
            discount = 0.30; // 30%, arsa / foarte cruda
        }
        

        discount += (1.0 - ingredientAccuracy) * 0.5; // penalizare pentru ingredientele gresite

        if (idealTime + acceptableOverallDelay < actualTime) {
            discount += 0.05; // se penalizeaza suplimentar pentru intarziere
        }

        // vad daca e cam mare penalizarea si daca e scort if ul asta si las doar discount pentru ingrediente + cuptor

        if (discount > 1.0) 
            discount = 1.0;
        
        return discount;
    }

    double getFinalPayment(double expectedPayment, double discount)
    {
        double finalPayment = expectedPayment - (expectedPayment * discount);
        return finalPayment;
    }
}