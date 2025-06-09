#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include "transaction.h"
#include <vector>
#include <string>

class TransactionManager {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& t);
    void loadFromCSV(const std::string& filename);
    void saveToCSV(const std::string& filename) const;
    void displayAll() const;

    void searchByCategory(const std::string& category) const;
    void searchByAmountRange(float minAmount, float maxAmount) const;

    void sortByAmount(bool ascending = true);
    void sortByDate(bool ascending = true);

    void generateMonthlySummary() const;
    void deleteTransaction(int index);

};

#endif
