class Account
{
public:
    Account(int);
    void credit(int);
    void debit(int);
    int getBalance();
private:
    int balance;
};
