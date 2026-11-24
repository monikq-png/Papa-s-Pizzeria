#include "../include/Customer.h"
#include "../include/Pizza.h"
#include "../include/Ingredient.h"
#include "../include/Oven.h"
#include "../include/Order.h"
#include "../include/Console.h"
#include "../include/Services.h"
#include "../include/Game.h"

Game::Game()
    : currentDay(1),
      totalDays(5),
      orderCounter(1),
      totalEarnings(0.0),
      totalExpenses(0.0),
      averageAccuracyFinal(0.0),
      totalOrdersCompleted(0)
{
    initIngredients();
    initRecipes();
}

void Game::initIngredients()
{
    unlockedIngredients.push_back(Ingredient("Dough", 10, 3.0)); // (bake time, pret)
    unlockedIngredients.push_back(Ingredient("Tomato Sauce", 1, 2.0));
    unlockedIngredients.push_back(Ingredient("Mozzarella", 2, 4.0));

    allIngredients.push_back(Ingredient("Pepperoni", 2, 5.0)); // ziua 2
    allIngredients.push_back(Ingredient("Mushrooms", 1, 3.5)); // ziua 3
    allIngredients.push_back(Ingredient("Olives", 1, 2.5));    // ziua 4
    allIngredients.push_back(Ingredient("Ham", 2, 4.5));       // ziua 5
}

void Game::initRecipes()
{
    // ziua 1
    Pizza margherita("Margherita", 0, 0.0); // (idealBakeTime, totalPrice)
    margherita.addIngredient(unlockedIngredients[0]); 
    margherita.addIngredient(unlockedIngredients[1]);
    margherita.addIngredient(unlockedIngredients[2]);
    allRecipes.push_back(margherita);

    // ziua 2
    Pizza pepperoni("Pepperoni", 0, 0.0);
    pepperoni.addIngredient(unlockedIngredients[0]);
    pepperoni.addIngredient(unlockedIngredients[1]);
    pepperoni.addIngredient(unlockedIngredients[2]);
    pepperoni.addIngredient(allIngredients[0]);
    allRecipes.push_back(pepperoni);

    // ziua 3
    Pizza funghi("Funghi", 0, 0.0);
    funghi.addIngredient(unlockedIngredients[0]);
    funghi.addIngredient(unlockedIngredients[1]);
    funghi.addIngredient(unlockedIngredients[2]);
    funghi.addIngredient(allIngredients[1]);
    allRecipes.push_back(funghi);

    // ziua 4
    Pizza capricciosa("Capricciosa", 0, 0.0);
    capricciosa.addIngredient(unlockedIngredients[0]);
    capricciosa.addIngredient(unlockedIngredients[1]);
    capricciosa.addIngredient(unlockedIngredients[2]);
    capricciosa.addIngredient(allIngredients[1]);
    capricciosa.addIngredient(allIngredients[2]); 
    allRecipes.push_back(capricciosa);

    // ziua 5
    Pizza prosciutto("Prosciutto", 0, 0.0);
    prosciutto.addIngredient(unlockedIngredients[0]);
    prosciutto.addIngredient(unlockedIngredients[1]);
    prosciutto.addIngredient(unlockedIngredients[2]);
    prosciutto.addIngredient(allIngredients[2]);
    prosciutto.addIngredient(allIngredients[3]);
    allRecipes.push_back(prosciutto);
}

void Game::unlockIngredientForDay(int day)
{
    int index = day - 2;
    if (index >= 0 && index < static_cast<int>(allIngredients.size())) {
        unlockedIngredients.push_back(allIngredients[index]);
    }
}

void Game::processOrder(const std::vector<Pizza>& dailyMenu)
{
    Customer customer = Services::getRandomCustomer();
    Order order = Services::getRandomOrder(customer, dailyMenu, orderCounter++);
    const Pizza& requestedPizza = order.getPizza();

    Console::displayCustomerDetails(customer);
    Console::displayOrderDetails(order);

    Console::continueToIngredients();

    Pizza playerPizza;
    double placingTime = Console::readPlayerPizza(playerPizza, unlockedIngredients);

    Console::displayIngredientTime(placingTime);

    Console::continueToOven();

    Console::displayOvenIN(requestedPizza);
    oven.bakePizza();
    Console::displayOvenOUT(oven);

    double effectiveBakeTime = std::max(oven.getOvenTime(), static_cast<double>(requestedPizza.getIdealBakeTime()));
    double actualTime = placingTime + effectiveBakeTime;
    
    double ingredientAccuracy = Services::getIngredientAccuracy(requestedPizza, playerPizza);
    double ovenAccuracy = Services::getOvenAccuracy(requestedPizza, oven);

    double discount = Services::getBakeDiscount(actualTime, ovenAccuracy, customer.getTolerance(), 
    ingredientAccuracy, requestedPizza);
    double finalPayment = Services::getFinalPayment(requestedPizza.getTotalPrice(), discount);

    Console::continueToServe(); 

    Console::displayCustomerFinalComment(customer, ingredientAccuracy, ovenAccuracy, actualTime, requestedPizza);
    Console::displayFinalPayment(finalPayment, discount);

    Console::continueToStatitics();  

    double ingredientSpeedAccuracy = Services::getIngredientSpeedAccuracy((order.getPizza()).getIngredientPlacingTime(), placingTime);

    Console::displayAccuracy(ingredientAccuracy, ovenAccuracy, ingredientSpeedAccuracy);

    totalEarnings += finalPayment;
    for (const auto& ing : playerPizza.getIngredients()) {
        totalExpenses += ing.getPrice();
    }
    averageAccuracyFinal += (ingredientAccuracy + ovenAccuracy) / 2.0;
    totalOrdersCompleted++;
}

void Game::playDay(int day)
{
    unlockIngredientForDay(day);

    std::vector<Pizza> dailyMenu = Services::getDailyMenu(unlockedIngredients, allRecipes);

    Console::displayDayStart(day, unlockedIngredients);
    Console::displayDailyMenu(dailyMenu);

    int ordersPerDay = 1;
    for (int i = 0; i < ordersPerDay; ++i) {
        processOrder(dailyMenu);
    }

    Console::continueToEndDay();
    Console::displayEndDay(day);
}

void Game::run()
{
    for (currentDay = 1; currentDay <= totalDays; currentDay++) {
        playDay(currentDay);
    }

    double profit = totalEarnings - totalExpenses;
    int overallAccuracy = (totalOrdersCompleted > 0) ? static_cast<int>((averageAccuracyFinal / totalOrdersCompleted) * 100) : 0;

    Console::displayGameOver(totalEarnings, profit, overallAccuracy);
}