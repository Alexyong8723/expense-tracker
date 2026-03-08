//Build a simple expense tracker application to manage your finances. The application should allow users to add, delete, and view their expenses. The application should also provide a summary of the expenses.

// Requirements
// Application should run from the command line and should have the following features:

// Users can add an expense with a description and amount.

// Users can update an expense.

// Users can delete an expense.

// Users can view all expenses.

// Users can view a summary of all expenses.

// Users can view a summary of expenses for a specific month (of current year).

// Here are some additional features that you can add to the application:

// Add expense categories and allow users to filter expenses by category.

// Allow users to set a budget for each month and show a warning when the user exceeds the budget.

// Allow users to export expenses to a CSV file.
#include <iostream>
#include <vector>   
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>

struct Expense {
    std::string description;
    double amount;
    std::string category;
    std::tm date;
};

class ExpenseTracker {
private:
    std::vector<Expense> expenses;
    std::map<std::string, double> monthlyBudgets;
public:
    void addExpense(const std::string& description, double amount, const std::string& category, const std::tm& date) {
        expenses.push_back({ description, amount, category, date });
    }
    void updateExpense(size_t index, const std::string& description, double amount,const std::string& category, const std::tm& date) {
        if (index < expenses.size()) {
            expenses[index] = { description, amount, category, date };
        } else {
            std::cout << "Invalid expense index." << std::endl;
        }
    }
    void deleteExpense(size_t index) {
        if (index < expenses.size()) {
            expenses.erase(expenses.begin() + index);
        } else {
            std::cout << "Invalid expense index." << std::endl;
        }
    }
    void viewExpenses() const {
        std::cout << "Expenses:" << std::endl;
        for (size_t i = 0; i < expenses.size(); ++i) {
            const auto& expense = expenses[i];
            std::cout << i << ": " << expense.description << " - $" << std::fixed
                << std::setprecision(2) << expense.amount << " - " << expense.category
                << " - " << (expense.date.tm_mon + 1) << "/" << (expense.date.tm_mday)
                << "/" << (expense.date.tm_year + 1900) << std::endl;
        }
    }
    void viewSummary() const {
        double total = 0;
        for (const auto& expense : expenses) {
            total += expense.amount;
        }
        std::cout << "Total Expenses: $" << std::fixed << std::setprecision(2) << total
            << std::endl;
    }
    void viewMonthlySummary(int month) const {
        double total = 0;
        for (const auto& expense : expenses) {
            if (expense.date.tm_mon == month - 1) {
                total += expense.amount;
            }
        }
        std::cout << "Total Expenses for " << month << ": $" << std::fixed
            << std::setprecision(2) << total << std::endl;
    }
    void setMonthlyBudget(const std::string& month, double budget) {
        monthlyBudgets[month] = budget;
    }
    void checkBudget(const std::string& month) const {
        auto it = monthlyBudgets.find(month);
        if (it != monthlyBudgets.end()) {
            double total = 0;
            for (const auto& expense : expenses) {
                if (expense.date.tm_mon == std::stoi(month) - 1) {
                    total += expense.amount;
                }
            }
            if (total > it->second) {
                std::cout << "Warning: You have exceeded your budget for " << month
                    << "!" << std::endl;
            } else {
                std::cout << "You are within your budget for " << month << "." << std::endl;
            }
        } else {
            std::cout << "No budget set for " << month << "." << std::endl;
        }
    }
    void exportToCSV(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {   
            file << "Description,Amount,Category,Date\n";
            for (const auto& expense : expenses) {
                file << expense.description << "," << expense.amount << ","
                    << expense.category << "," << (expense.date.tm_mon + 1) << "/"
                    << (expense.date.tm_mday) << "/" << (expense.date.tm_year + 1900)
                    << "\n";
            }
            file.close();
            std::cout << "Expenses exported to " << filename << std::endl;
        } else {
            std::cout << "Unable to open file." << std::endl;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.addExpense("Groceries", 150.75, "Food", { 0, 0, 0, 15, 5, 122 });
    tracker.addExpense("Rent", 1200.00, "Housing", { 0, 0, 0, 1, 5, 122 });
    tracker.addExpense("Utilities", 200.50, "Housing", { 0, 0, 0, 10, 5, 122 });
    tracker.viewExpenses();
    tracker.viewSummary();
    tracker.viewMonthlySummary(6);
    tracker.setMonthlyBudget("6", 1000.00);
    tracker.checkBudget("6");
    tracker.exportToCSV("expenses.csv");
    return 0;
}
