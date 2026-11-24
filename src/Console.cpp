#include "../include/Customer.h"
#include "../include/Pizza.h"
#include "../include/Ingredient.h"
#include "../include/Oven.h"
#include "../include/Order.h"
#include "../include/Console.h"
#include "../include/Services.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <chrono>

namespace Console 
{
    static void printCentered(const std::string& text, int width = 90) 
    {
        std::cout << std::endl;
        int padding = (width - static_cast<int>(text.length())) / 2;
        if (padding < 0) padding = 0;
        
        std::cout << std::setw(padding + text.length()) << text << std::endl;
    }

    void displayDayStart(int day, const std::vector<Ingredient>& unlockedIngredients)
    {
        printCentered("-------------------------------------");
        printCentered("DAY " + std::to_string(day));
        printCentered("NEW INGREDIENT UNLOCKED: " + unlockedIngredients.back().getName());
    }

    void displayDailyMenu(const std::vector<Pizza>& dailyMenu)
    {
        printCentered("-------------------------------------");
        printCentered("TODAY'S MENU");
        std::cout << std::endl;
        for (const auto& pizza : dailyMenu) 
        {
            std::cout << pizza << std::endl;
        }
    }

    void displayCustomerDetails(const Customer& customer)
    {
        printCentered("-------------------------------------");
        // double tolerance[] = {0.5, 0.75, 1.0, 1.0, 1.0, 1.25, 1.5}; 
        printCentered("CUSTOMER DETAILS");
        std::cout << std::endl;

        static const std::string possibleComments[] = {
            // 0.5
            "I'm in a huge hurry, make it snappy!",
            "I know what I want, and I want it now!",

            // 0.75
            "I don't have all day, so please hurry a bit.",
            "I'm on a tight schedule, try to be quick.",

            // 1.0
            "I'm not in a rush, just don't take too long.",
            "Make it tasty and reasonably fast, please.",
            "I'm pretty hungry, so don't drag it out, but make sure it's good!",
            "No need to rush, just serve it while it's hot and fresh!",

            // 1.25
            "I don't mind waiting, just make it right!",
            "No rush at all, good pizza takes time.",

            // 1.5
            "Take all the time you need, I'm just relaxing.",
            "I don't care how long it takes, just make it perfect!"
        };

        int index = 0;
        std::cout << customer.getName() << ": ";
        if (customer.getTolerance() == 0.5) {
            
            index = rand() % 2;
        } else if (customer.getTolerance() == 0.75) {
            index = rand() % 2 + 2; 
        } else if (customer.getTolerance() == 1.0) {
            index = rand() % 4 + 4; 
        } else if (customer.getTolerance() == 1.25) {
            index = rand() % 2 + 8; 
        } else if (customer.getTolerance() == 1.5) {
            index = rand() % 2 + 10;
        }
        std::cout << possibleComments[index]; 
    }

    void displayOrderDetails(const Order& order)
    {
        std::cout << " I'd like a ";
        std::cout << (order.getPizza()).printWithoutIngredients();
        std::cout << "." << std::endl;
    }
    
    void displayIngredientTime(double time)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << time;
        std::string timeString = oss.str();

        printCentered("IT TOOK " + timeString + " SECONDS TO PLACE THE INGREDIENTS.");
    }

    double readPlayerPizza(Pizza& playerPizza, const std::vector<Ingredient>& unlockedIngredients)
    {   
        printCentered("-------------------------------------");
        printCentered("ENTER THE INGREDIENTS. TYPE -DONE- WHEN YOU WANT TO PUT THE PIZZA IN THE OVEN");

        std::chrono::steady_clock::time_point startTime;
        bool timerStarted = false;

        std::string ingredient;
        while (true)
        {
            std::getline(std::cin, ingredient);

            if (!timerStarted) {
                startTime = std::chrono::steady_clock::now();
                timerStarted = true;
            }

            if (ingredient == "DONE") {
                break;
            }

            bool isAvailable = false;
            for (const auto& i : unlockedIngredients)
            {
                if (ingredient == i.getName())
                {
                    playerPizza.addIngredient(i);
                    isAvailable = true;
                    break;
                }
            }

            if (!isAvailable) {
                std::cout << "WE DON'T HAVE ANY " << ingredient << " IN STOCK!" << std::endl;
            }
        }

        auto endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;

        return duration.count();
    }

    void displayOvenIN(const Pizza& pizza)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << pizza.getIdealBakeTime();
        std::string expectedOvenTime = oss.str();

        printCentered("-------------------------------------");
        printCentered("THE PIZZA IS IN THE OVEN! PRESS -ENTER- WHEN YOU WANT TO TAKE IT OUT...");
        printCentered("EXPECTED TIME: " + expectedOvenTime + " SECONDS");
    }

    void displayOvenOUT(const Oven& oven)
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << oven.getOvenTime();
        std::string ovenTimeString = oss.str();

        printCentered("YOU TOOK THE PIZZA OUT AFTER " + ovenTimeString + " SECONDS.");
    }

    void displayCustomerFinalComment(const Customer& customer, double ingredientAccuracy, double ovenAccuracy, double actualTime,
        const Pizza& requestedPizza)
    {
        printCentered("-------------------------------------");
        std::cout << std::endl;

        double idealTime = requestedPizza.getIdealBakeTime() + requestedPizza.getIngredientPlacingTime();
        double acceptableDelay = (0.1 * idealTime) * customer.getTolerance();
        bool isLate = actualTime > (idealTime + acceptableDelay);

        double averageAccuracy = (ingredientAccuracy + ovenAccuracy) / 2.0;

        // } else if (ovenAccuracy >= 0.50) {
        //discount = 0.15; // 15%, destul de arsă / crudă
        double satisfaction =  averageAccuracy - (isLate ? 0.15 : 0.0); // pe principiul discount ului
        
        std::string comment;
        if (ingredientAccuracy < 0.5) {
            comment = "This isn't even the pizza I ordered! Way too many wrong toppings.";
        } else if (ovenAccuracy < 0.5) {
            comment = "This pizza is completely ruined in the oven!";
        } else if (satisfaction >= 0.90) {
            comment = "Perfection! Best pizza in town!";
        } else if (satisfaction >= 0.75) {
            comment = "Pretty good pizza, I'll definitely come back.";
        } else if (satisfaction >= 0.50) {
            comment = "It's okay, I guess, but could be much better.";
        } else {
            comment = "Terrible! Definitely not worth full price.";
        }

        std::cout << customer.getName() << ": " << comment;
        std::cout << std::endl;
    }

    void displayFinalPayment(double finalPayment, double discount)
    {
        printCentered("-------------------------------------");

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << finalPayment;
        std::string finalPaymentString = oss.str();

        printCentered("DISCOUNT APPLIED: " + std::to_string(static_cast<int>(discount * 100)) + "%");
        printCentered("FINAL PAYMENT: " + finalPaymentString + " RON");
        std::cout << std::endl;
    }

    void displayAccuracy(double ingredientAccuracy, double ovenAccuracy, double ingredientSpeedAccuracy)
    {
        double overallAccuracy = (ingredientAccuracy + ovenAccuracy) / 2.0;

        printCentered("-------------------------------------");
        printCentered("INGREDIENT ACCURACY: " + std::to_string(static_cast<int>(ingredientAccuracy * 100)) + "%");
        printCentered("INGREDIENT SPEED ACCURACY: " + std::to_string(static_cast<int>(ingredientSpeedAccuracy * 100)) + "%");
        printCentered("OVEN TIME ACCURACY: " + std::to_string(static_cast<int>(ovenAccuracy * 100)) + "%");
        printCentered("OVERALL ACCURACY: " + std::to_string(static_cast<int>(overallAccuracy * 100)) + "%");
        printCentered("-------------------------------------");

        std::cout << std::endl;
    }

    void displayEndDay(int day)
    {
        printCentered("-------------------------------------");
        printCentered("END OF DAY " + std::to_string(day));
        std::cout << std::endl;
    }

    void displayGameOver(double totalEarnings, double profit, int overallAccuracy)
    {
        std::ostringstream ossEarnings, ossProfit;
        ossEarnings << std::fixed << std::setprecision(2) << totalEarnings;
        ossProfit << std::fixed << std::setprecision(2) << profit;

        printCentered("-------------------------------------");
        printCentered("GAME OVER");
        printCentered("-------------------------------------");
        printCentered("TOTAL EARNINGS: " + ossEarnings.str() + " RON");
        printCentered("TOTAL PROFIT: " + ossProfit.str() + " RON");
        printCentered("OVERALL ACCURACY: " + std::to_string(overallAccuracy) + "%");
        std::cout << std::endl;
        printCentered("-------------------------------------");
    }

    void continueToIngredients()
    {
        std::cout << std::endl;
        printCentered("PRESS -ENTER- TO START PREPARING THE ORDER...");
        std::string enter;
        std::getline(std::cin, enter);
    }

    void continueToOven()
    {
        std::cout << std::endl;
        printCentered("PRESS -ENTER- TO PLACE THE PIZZA IN THE OVEN...");
        std::string enter;
        std::getline(std::cin, enter);
    }

    void continueToServe()
    {
        std::cout << std::endl;
        printCentered("PRESS -ENTER- TO SERVE THE PIZZA...");
        std::string enter;
        std::getline(std::cin, enter);
    }

    void continueToStatitics()
    {
        std::cout << std::endl;
        printCentered("PRESS -ENTER- TO SEE THE STATISTICS...");
        std::string enter;
        std::getline(std::cin, enter);
    }

    void continueToEndDay()
    {
        std::cout << std::endl;
        printCentered("PRESS -ENTER- TO CLOSE UP FOR TODAY...");
        std::string enter;
        std::getline(std::cin, enter);
    }

}