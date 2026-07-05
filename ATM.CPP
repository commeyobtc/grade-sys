#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Holds all account information
struct Account
{
    string name;
    int pin;
    double balance;
};

// Reads a validated integer from the user (e.g. PIN, menu choice)
int readInt(const string &label)
{
    int value;
    cout << "Enter " << label << ": ";
    while (!(cin >> value))
    {
        cout << "Invalid input. Please enter a numeric value for " << label << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

// Reads a validated double from the user (e.g. deposit/withdraw amount)
double readAmount(const string &label)
{
    double value;
    cout << "Enter " << label << ": ";
    while (!(cin >> value) || value < 0)
    {
        cout << "Invalid input. Please enter a positive numeric value for " << label << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

// Sets up the account with a starting name, pin, and balance
Account createAccount()
{
    Account acc;
    cout << "Enter account holder name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, acc.name);

    acc.pin = readInt("4-digit PIN");
    acc.balance = readAmount("starting balance");
    return acc;
}

// Verifies the user knows the correct PIN before allowing access
bool login(const Account &acc)
{
    int attempts = 3;
    while (attempts > 0)
    {
        int enteredPin = readInt("PIN");
        if (enteredPin == acc.pin)
        {
            cout << "Login successful.\n";
            return true;
        }
        attempts--;
        cout << "Incorrect PIN. Attempts remaining: " << attempts << "\n";
    }
    cout << "Too many incorrect attempts. Access denied.\n";
    return false;
}

void checkBalance(const Account &acc)
{
    cout << "Current balance: $" << acc.balance << "\n";
}

void deposit(Account &acc)
{
    double amount = readAmount("deposit amount");
    acc.balance += amount;
    cout << "Deposit successful. New balance: $" << acc.balance << "\n";
}

void withdraw(Account &acc)
{
    double amount = readAmount("withdrawal amount");
    if (amount > acc.balance)
    {
        cout << "Insufficient funds. Your balance is $" << acc.balance << "\n";
    }
    else
    {
        acc.balance -= amount;
        cout << "Withdrawal successful. New balance: $" << acc.balance << "\n";
    }
}

// Displays the menu and returns the user's validated choice
int showMenu()
{
    cout << "\n----- ATM MENU -----\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Exit\n";
    return readInt("choice (1-4)");
}

int main()
{
    cout << "===== Welcome to Simple ATM =====\n";
    Account account = createAccount();

    if (!login(account))
    {
        return 0; // Exit program if login fails
    }

    bool running = true;
    while (running)
    {
        int choice = showMenu();
        switch (choice)
        {
        case 1:
            checkBalance(account);
            break;
        case 2:
            deposit(account);
            break;
        case 3:
            withdraw(account);
            break;
        case 4:
            cout << "Thank you for using Simple ATM. Goodbye!\n";
            running = false;
            break;
        default:
            cout << "Invalid choice. Please select 1-4.\n";
        }
    }

    return 0;
}
