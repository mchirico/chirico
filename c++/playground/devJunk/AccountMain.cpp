#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Account.h"

int main()
{

  Account account1(50);
  cout << "account1 balance: $" << account1.getBalance() << endl;

  int withdrawalAmount;
  cout << "\nEnter withdrawal amount for account1: ";
  cin >> withdrawalAmount;
  account1.debit(withdrawalAmount);

  cout << "account1 balance: $" << account1.getBalance() << endl;

}
