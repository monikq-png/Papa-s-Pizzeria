#include "../include/Oven.h"
#include <iostream>
#include <chrono>
#include <iomanip>
//#include <limits>

Oven::Oven() : ovenTime(0.0) {}

void Oven::bakePizza()
{
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto startTime = std::chrono::steady_clock::now();

    std::cin.get();

    auto endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = endTime - startTime;
    ovenTime = duration.count(); // pune timpul in secunde
}

double Oven::getOvenTime() const
{
    return ovenTime;
}