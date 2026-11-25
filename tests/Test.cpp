#undef NDEBUG
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include "../include/Customer.h"
#include "../include/Ingredient.h"
#include "../include/Order.h"
#include "../include/Oven.h"
#include "../include/Pizza.h"
#include "../include/Services.h"

namespace {
    bool nearlyEqual(double a, double b, double eps = 1e-6) {
        return std::abs(a - b) <= eps;
    }
} // namespace

int main() {
    // potrivire ingrediente Game::initIngredients()
    Ingredient dough("Dough", 10, 3.0);
    Ingredient tomatoSauce("Tomato Sauce", 1, 2.0);
    Ingredient mozzarella("Mozzarella", 2, 4.0);
    Ingredient pepperoni("Pepperoni", 2, 5.0);
    Ingredient mushrooms("Mushrooms", 1, 3.5);
    Ingredient olives("Olives", 1, 2.5);
    Ingredient ham("Ham", 2, 4.5);

    std::vector<Ingredient> unlockedIngredients = {dough, tomatoSauce, mozzarella};
    assert(Services::hasIngredient(unlockedIngredients, "Dough"));
    assert(Services::hasIngredient(unlockedIngredients, "Tomato Sauce"));
    assert(Services::hasIngredient(unlockedIngredients, "Mozzarella"));
    assert(!Services::hasIngredient(unlockedIngredients, "Pepperoni"));
    assert(!Services::hasIngredient(unlockedIngredients, "Mushrooms"));
    assert(!Services::hasIngredient(unlockedIngredients, "Olives"));
    assert(!Services::hasIngredient(unlockedIngredients, "Ham"));

    // potrivire retete Game::initRecipes()
    Pizza margherita("Margherita", 0, 0.0);
    margherita.addIngredient(dough);
    margherita.addIngredient(tomatoSauce);
    margherita.addIngredient(mozzarella);

    Pizza pepperoniPizza("Pepperoni", 0, 0.0);
    pepperoniPizza.addIngredient(dough);
    pepperoniPizza.addIngredient(tomatoSauce);
    pepperoniPizza.addIngredient(mozzarella);
    pepperoniPizza.addIngredient(pepperoni);

    Pizza funghi("Funghi", 0, 0.0);
    funghi.addIngredient(dough);
    funghi.addIngredient(tomatoSauce);
    funghi.addIngredient(mozzarella);
    funghi.addIngredient(mushrooms);

    Pizza capricciosa("Capricciosa", 0, 0.0);
    capricciosa.addIngredient(dough);
    capricciosa.addIngredient(tomatoSauce);
    capricciosa.addIngredient(mozzarella);
    capricciosa.addIngredient(mushrooms);
    capricciosa.addIngredient(olives);

    Pizza prosciutto("Prosciutto", 0, 0.0);
    prosciutto.addIngredient(dough);
    prosciutto.addIngredient(tomatoSauce);
    prosciutto.addIngredient(mozzarella);
    prosciutto.addIngredient(olives);
    prosciutto.addIngredient(ham);

    std::vector<Pizza> allRecipes = {margherita, pepperoniPizza, funghi, capricciosa, prosciutto};

    // meniu ziua 1, doar Margherita disponibila
    std::vector<Pizza> dayOneMenu = Services::getDailyMenu(unlockedIngredients, allRecipes);
    assert(dayOneMenu.size() == 1);
    assert(dayOneMenu[0].getRecipeName() == "Margherita");

    // deblochez Pepperoni (z2) and Mushrooms (z3) -> Margherita, Pepperoni, Funghi disponibile
    unlockedIngredients.push_back(pepperoni);
    unlockedIngredients.push_back(mushrooms);
    std::vector<Pizza> dayThreeMenu = Services::getDailyMenu(unlockedIngredients, allRecipes);
    assert(dayThreeMenu.size() == 3);
    assert(dayThreeMenu[0].getRecipeName() == "Margherita");
    assert(dayThreeMenu[1].getRecipeName() == "Pepperoni");
    assert(dayThreeMenu[2].getRecipeName() == "Funghi");

    //getIngredientSpeedAccuracy
    assert(nearlyEqual(Services::getIngredientSpeedAccuracy(10.0, 8.0), 1.0));
    assert(nearlyEqual(Services::getIngredientSpeedAccuracy(10.0, 10.0), 1.0));
    assert(nearlyEqual(Services::getIngredientSpeedAccuracy(10.0, 12.5), 0.75));
    assert(nearlyEqual(Services::getIngredientSpeedAccuracy(10.0, 25.0), 0.0));
    assert(nearlyEqual(Services::getIngredientSpeedAccuracy(0.0, 5.0), 1.0));

    //getIngredientAccuracy -> Capricciosa (Dough, Tomato Sauce, Mozzarella, Mushrooms, Olives)
    Pizza partialCapricciosa("Capricciosa", 0, 0.0);
    partialCapricciosa.addIngredient(dough);
    partialCapricciosa.addIngredient(tomatoSauce);
    partialCapricciosa.addIngredient(mozzarella);
    partialCapricciosa.addIngredient(mushrooms);
    // lipsesc Olives -> 4 din 5 ingrediente corecte
    assert(nearlyEqual(Services::getIngredientAccuracy(capricciosa, partialCapricciosa), 0.8));
    assert(nearlyEqual(Services::getIngredientAccuracy(capricciosa, capricciosa), 1.0));

    //getBakeDiscount & getFinalPayment
    const double perfectDiscount = Services::getBakeDiscount(10.0, 1.0, 1.0, 1.0, margherita);
    assert(nearlyEqual(perfectDiscount, 0.0));
    assert(nearlyEqual(Services::getFinalPayment(9.0, perfectDiscount), 9.0));

    const double mixedDiscount = Services::getBakeDiscount(10.0, 0.4, 1.0, 0.5, margherita);
    assert(nearlyEqual(mixedDiscount, 0.55));
    assert(nearlyEqual(Services::getFinalPayment(10.0, mixedDiscount), 4.5));

    return 0;
}