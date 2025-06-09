#include "transaction_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>

void TransactionManager::addTransaction(const Transaction& t) {
    transactions.push_back(t);
}

void TransactionManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    transactions.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string desc, amtStr, cat, date;
        std::getline(ss, desc, ',');
        std::getline(ss, amtStr, ',');
        std::getline(ss, cat, ',');
        std::getline(ss, date, ',');

        try {
            float amt = std::stof(amtStr);
            Transaction t(desc, amt, cat, date);
            transactions.push_back(t);
        } catch (...) {
            std::cerr << "Skipping malformed line.\n";
        }
    }
}

void TransactionManager::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    for (const auto& t : transactions) {
        file << t.getDescription() << ","
             << std::fixed << std::setprecision(2) << t.getAmount() << ","
             << t.getCategory() << ","
             << t.getDate() << "\n";
    }
}

void TransactionManager::displayAll() const {
    for (const auto& t : transactions) {
        t.display();
    }
}

void TransactionManager::searchByCategory(const std::string& category) const {
    for (const auto& t : transactions) {
        if (t.getCategory() == category)
            t.display();
    }
}

void TransactionManager::searchByAmountRange(float minAmount, float maxAmount) const {
    for (const auto& t : transactions) {
        if (t.getAmount() >= minAmount && t.getAmount() <= maxAmount)
            t.display();
    }
}

void TransactionManager::sortByAmount(bool ascending) {
    std::sort(transactions.begin(), transactions.end(), [=](const Transaction& a, const Transaction& b) {
        return ascending ? a.getAmount() < b.getAmount() : a.getAmount() > b.getAmount();
    });
}

void TransactionManager::sortByDate(bool ascending) {
    std::sort(transactions.begin(), transactions.end(), [=](const Transaction& a, const Transaction& b) {
        return ascending ? a.getDate() < b.getDate() : a.getDate() > b.getDate();
    });
}

void TransactionManager::generateMonthlySummary() const {
    std::map<std::string, float> monthlyTotal;
    for (const auto& t : transactions) {
        std::string month = t.getDate().substr(0, 7); // Extract YYYY-MM
        monthlyTotal[month] += t.getAmount();
    }

    std::cout << "\n--- Monthly Summary ---\n";
    for (const auto& pair : monthlyTotal) {
        std::cout << pair.first << ": " << std::fixed << std::setprecision(2) << pair.second << "\n";
    }
}

void TransactionManager::deleteTransaction(int index) {
    if (index < 0 || index >= transactions.size()) {
        std::cout << "Invalid index. Transaction not found.\n";
        return;
    }

    std::cout << "Deleting transaction:\n";
    transactions[index].display();

    char confirm;
    std::cout << "Are you sure you want to delete this transaction? (y/n): ";
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        transactions.erase(transactions.begin() + index);
        std::cout << "Transaction deleted successfully.\n";
    } else {
        std::cout << "Deletion cancelled.\n";
    }
}
