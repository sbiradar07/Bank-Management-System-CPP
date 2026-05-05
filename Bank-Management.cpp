#include <string>
#include <iostream>
#include <fstream>
using namespace std;
// BankAccount class definition
class BankAccount
{
private:
    string accountnumber;
    string holdername;
    double balance;
public:
    double amount;
    // Default constructor
    BankAccount()
        : accountnumber(""), holdername(""), balance(0.0), amount(0.0)
    {
    }
    // Parameterized constructor
    BankAccount(const string& num, const string& name, double bal)
        : accountnumber(num), holdername(name), balance(bal), amount(0.0)
    {
    }
    // function to check if account details are valid
    bool isvalid() const
    {
        return !accountnumber.empty();
    }
    void setAccountDetails(const string& num, const string& name, double bal)
    {
        accountnumber = num;
        holdername = name;
        balance = bal;
    }
    void Deposit()
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "New Balance is :" << balance << endl;
        }
        else
        {
            cout << "Deposit amount must be positive" << endl;
        }
    }
    void withdraw()
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "New Balance is :" << balance << endl;
        }
        else
        {
            cout << "Insufficient funds" << endl;
        }
    }
    void checkbalance()
    {
        cout << "Account Balance is :" << balance << endl;
    }
    void saveToFile()
    {
        ofstream file(accountnumber + ".txt");
        if (file.is_open())
        {
            file << accountnumber << endl;
            file << holdername << endl;
            file << balance << endl;
            file.close();
            cout << "Account details saved to file successfully " << accountnumber << ".txt" << endl;
        }
        else
        {
            cout << "Unable to open file" << endl;
        }
    }
    static BankAccount loadFromFile(const string& accnum)
    {
        BankAccount account;
        ifstream file(accnum + ".txt");
        if (file.is_open())
        {
            getline(file, account.accountnumber);
            getline(file, account.holdername);
            file >> account.balance;
            file.close();
            cout << "Account details loaded from file successfully " << accnum << ".txt" << endl;
            return account;
        }
        else
        {
            cout << "No existing account. You have to create a new account." << endl;
            return BankAccount();
        }
    }
};
int main()
{
    int choice;
    cout << "Welcome to Bank Management System" << endl;
    cout << "1.Create new account :" << endl;
    cout<<"2. Login with existing account :" << endl;
    int option;
    BankAccount obj;
    string accountNumber;
    cin >> option;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Invalid input";
        return 0;
    }
    cin.ignore();
    if (option == 1)
    {
        cout << "Account not found. Creating new account..." << endl;
        cout << "Enter account number :" << endl;
        cin >> accountNumber;
        cout << "Enter holder name :" << endl;
        string holderName;
        cin >> holderName;
        cout << "Enter initial balance :" << endl;
        double initialbalance;
        cin >> initialbalance;
        obj.setAccountDetails(accountNumber, holderName, initialbalance);
        obj.saveToFile();
        cout << "Account created successfully" << endl;
    }
    else if (option == 2)
    {
        cout << "Enter account number :" << endl;
        cin >> accountNumber;
        obj = BankAccount::loadFromFile(accountNumber);
        if(!obj.isvalid()){
            return 0;
        }
    }
    else
    {
        cout << "Invalid option :" << endl;
        return 0;
    }
    do
    {
        cout << "Bank Management System Menu :" << endl;
        cout << "1. Deposit Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Save Account Details to File" << endl;
        cout << "5. Exit" << endl;
        cout << "choose an option :" << endl;
        cin >> choice;
        if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Invalid input";
        continue;
    }
        switch (choice)
        {
        case 1:
            cout << "Enter amount to deposit :" << endl;
            cin >> obj.amount;
            obj.Deposit();
            break;
        case 2:
            cout << "Enter amount to withdraw :" << endl;
            cin >> obj.amount;
            obj.withdraw();
            break;
        case 3:
            obj.checkbalance();
            break;
        case 4:
            obj.saveToFile();
            break;
        case 5:
            cout << "Exiting ...." << endl;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    } while (choice != 5);
    return 0;
}