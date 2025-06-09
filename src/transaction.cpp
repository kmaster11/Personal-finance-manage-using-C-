#include "transaction.h"
#include <iostream>
#include <iomanip>

Transaction::Transaction() : amount(0.0f) {}

Transaction::Transaction(const std::string& desc, float amt, const std::string& cat, const std::string& dt)
    : description(desc), amount(amt), category(cat), date(dt) {}

std::string Transaction::getDescription() const { return description; }
float Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }

void Transaction::display() const {
    std::cout << std::left << std::setw(20) << description
              << std::setw(10) << std::fixed << std::setprecision(2) << amount
              << std::setw(15) << category
              << std::setw(12) << date << std::endl;
}
