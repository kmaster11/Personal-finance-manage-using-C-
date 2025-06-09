#include <iostream>
#include <limits>
#include "transaction_manager.h"

void showMenu() {
    std::cout << "\n--- Personal Finance Manager ---\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. Display All Transactions\n";
    std::cout << "3. Save Transactions to File\n";
    std::cout << "4. Load Transactions from File\n";
    std::cout << "5. Search Transactions by Category\n";
    std::cout << "6. Search Transactions by Amount Range\n";
    std::cout << "7. Sort Transactions by Amount\n";
    std::cout << "8. Sort Transactions by Date\n";
    std::cout << "9. Monthly Summary\n";
    std::cout << "10. Delete Transaction\n";
    std::cout << "11. Exit\n";
    std::cout << "Choose an option: ";
    
}

Transaction inputTransaction() {
    std::string desc, cat, date;
    float amt;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter description: ";
    std::getline(std::cin, desc);

    std::cout << "Enter amount: ";
    while (!(std::cin >> amt) || amt < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid amount. Please enter a positive number: ";
    }

    std::cin.ignore();
    std::cout << "Enter category: ";
    std::getline(std::cin, cat);

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    return Transaction(desc, amt, cat, date);
}

int main() {
    TransactionManager manager;
    manager.loadFromCSV("transactions.csv");

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Transaction t = inputTransaction();
                manager.addTransaction(t);
                break;
            }
            case 2:
                manager.displayAll();
                break;
            case 3:
                manager.saveToCSV("transactions.csv");
                break;
            case 4:
                manager.loadFromCSV("transactions.csv");
                break;
            case 5: {
                std::string category;
                std::cin.ignore();
                std::cout << "Enter category to search: ";
                std::getline(std::cin, category);
                manager.searchByCategory(category);
                break;
            }
            case 6: {
                float minAmt, maxAmt;
                std::cout << "Enter minimum amount: ";
                std::cin >> minAmt;
                std::cout << "Enter maximum amount: ";
                std::cin >> maxAmt;
                manager.searchByAmountRange(minAmt, maxAmt);
                break;
            }
            case 7: {
                manager.sortByAmount(true);
                std::cout << "Sorted by amount (ascending).\n";
                break;
            }
            case 8: {
                manager.sortByDate(true);
                std::cout << "Sorted by date (ascending).\n";
                break;
            }
            case 9:{
                manager.generateMonthlySummary();
                break;
            }
            case 10: {
                int index;
                std::cout << "Enter the index of the transaction to delete: ";
                std::cin >> index;
                manager.deleteTransaction(index);
                break;
            }
            case 11:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
