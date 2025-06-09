#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string description;
    float amount;
    std::string category;
    std::string date;

public:
    Transaction();
    Transaction(const std::string& desc, float amt, const std::string& cat, const std::string& dt);

    std::string getDescription() const;
    float getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;

    void display() const;
};

#endif
