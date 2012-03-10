#include <iostream>
using std::cout;
using std::endl;

#include "Account.h"

Account::Account(int initialBalance)
{
    balance=0;
    if (initialBalance > 0)
        balance = initialBalance;

    if (initialBalance < 0)
        cout << "Error: Initial balance cannot be negative.\n" << endl;
}
void Account::credit(int amount)
{
    balance=balance+amount;
}

void Account::debit(int amount)
{
    if (amount <= balance )
        balance = balance - amount;
    else
        cout << "Debit amount exceeded account balance.\n" << endl;
}
int Account::getBalance()
{
    return balance;
}
