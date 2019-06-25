/*  	Program:		MSVS 2012/2015
	Author:			Mai Pham	
	Class:			CSCI 140
	Date:			03/23/2017
	Description:		Project 1: Vending Machine + Extra Credit 1
	I certify that the code below is my own work.
	Exception(s): N/A
*/

#include <iostream>
#include <iomanip>
using namespace std;

void setUp(int dollars, int &quarters, int &dimes, int &nickels, double balance);
double getBalance(int dollars, int quarters, int dimes, int nickels);
void validate(int &purchasedAmount);
void insertCoins(int &insertMoney, int &insertQuarters, int &insertDimes, int &insertNickels);
void addCoins(int &quarters, int &dimes, int&nickels, int q, int d, int n);
void subtractCoins(int &quarters, int &dimes, int&nickels, int q, int d, int n);
void resetInsertMoney(int &insertMoney, int &insertQuarters, int &insertDimes, int &insertNickels);
void finalReport(int dollars, int quarters, int dimes, int nickels, double balance);

int main()
{
	int quarters, dimes, nickels, dollars = 0,
		quartersChange, dimesChange, nickelsChange,
		purchasedAmount, change1, change2, option,
		insertMoney = 0, insertQuarters = 0,
		insertDimes = 0, insertNickels = 0;
	double balance = 0;

	cout << fixed << showpoint << setprecision(2);

	cout << "Vending Machine Version 1A by Mai Pham" << endl << endl;
	
	cout << "Fill up the machine with changes. Please wait ..." << endl;
	setUp(dollars, quarters, dimes, nickels, balance);

	cout << "Enter a purchase amount [0 - 100] ==> ";
	cin >> purchasedAmount;

	while (purchasedAmount != 0)
	{
		cout << "You entered a purchased amount of " << purchasedAmount << " cents." << endl;
		validate(purchasedAmount);

		if (purchasedAmount == 0)
			break;

		cout << "Select an option (1 - dollar bill and 2 - coins) ==> ";
		cin >> option;
		if (option == 1)
		{
			cout << "Please insert one-dollar bill." << endl;
			dollars++;
			change1 = 100 - purchasedAmount;
		}
		else if (option == 2)
		{
			do
			{
				insertCoins(insertMoney, insertQuarters, insertDimes, insertNickels);
				cout << "You inserted an amount of " << insertMoney << " cents." << endl;

				if (insertMoney < purchasedAmount)
				{
					cout << "Insufficient amount! Returning all coins." << endl;
					resetInsertMoney(insertMoney, insertQuarters, insertDimes, insertNickels);
				}
				else
				{
					addCoins(quarters, dimes, nickels, insertQuarters, insertDimes, insertNickels);
				}
			} while (insertMoney < purchasedAmount);
			change1 = insertMoney - purchasedAmount;
		}

		cout << "Processing your purchase ..." << endl;
		change2 = change1;

		quartersChange = change1 / 25;
		if (quarters < quartersChange)
			quartersChange = quarters;
		change1 -= quartersChange * 25;

		dimesChange = change1 / 10;
		if (dimes < dimesChange)
			dimesChange = dimes;
		change1 -= dimesChange * 10;

		nickelsChange = change1 / 5;
		if (nickels < nickelsChange)
			nickelsChange = nickels;
		change1 -= nickelsChange * 5;

		if (change1 != 0)
		{
			cout << "Insufficient change!" << endl;
			cout << "Your transaction cannot be processed." << endl;
			
			if (option == 1)
			{
				cout << "Please take back your dollar bill." << endl << endl;
				dollars--;
			}
			else if (option == 2)
			{
				cout << "Please take back your coins." << endl << endl;
				subtractCoins(quarters, dimes, nickels, insertQuarters, insertDimes, insertNickels);
			}
		}
		else
		{
			subtractCoins(quarters, dimes, nickels, quartersChange, dimesChange, nickelsChange);
			cout << "Your change of " << change2 << " cents is given as:" << endl;
			cout << "	quarter(s): " << quartersChange << endl;
			cout << "	dime(s)   : " << dimesChange << endl;
			cout << "	nickel(s) : " << nickelsChange << endl << endl;
		}
		resetInsertMoney(insertMoney, insertQuarters, insertDimes, insertNickels);
		cout << "Enter a purchase amount [0 - 100] ==> ";
		cin >> purchasedAmount;
	}
	balance = getBalance(dollars, quarters, dimes, nickels);
	cout << "Final report is being generated ..." << endl;
	finalReport(dollars, quarters, dimes, nickels, balance);
	return 0;
}

void setUp(int dollars, int &quarters, int &dimes, int &nickels, double balance)
{
	cout << "Enter number of quarters, dimes, and nickels ==> ";
	cin >> quarters >> dimes >> nickels;

	cout << "There are " << quarters << " quarters, "
		 << dimes << " dimes, and " << nickels << " nickels." << endl;
	
	balance = getBalance(dollars, quarters, dimes, nickels);

	cout << "Initial machine balance is $" << balance << "." << endl
		 << "One-dollar bill or coins will be accepted." << endl
		 << "Only amount between 0 to 100 and multiple of 5 is accepted." << endl
		 << "Enter 0 to stop the program." << endl
		 << "Machine is now ready." << endl << endl;
}

double getBalance(int dollars, int quarters, int dimes, int nickels)
{
	double balance;
	balance = (dollars * 100) + (quarters * 25) + (dimes * 10) + (nickels * 5);
	balance = balance / 100;
	return balance;
}

void validate(int &purchasedAmount)
{
	while (purchasedAmount < 0 || purchasedAmount > 100 || purchasedAmount % 5 != 0)
	{
		if (purchasedAmount < 0 || purchasedAmount > 100)
			cout << "Invalid amount (outside valid range). Try again." << endl << endl;
		else
			cout << "Invalid amount (not a multiple of 5). Try again." << endl << endl;

		cout << "Enter a purchase amount [0 - 100] ==> ";
		cin >> purchasedAmount;
		cout << "You entered a purchased amount of " << purchasedAmount << " cents." << endl;
	}
}

void insertCoins(int &insertMoney,int &insertQuarters, int &insertDimes,int &insertNickels)
{
	int coins;

	cout << "Please insert your coins ==> ";
	cin >> coins;
	while (coins != 0)
	{
		if (coins == 25)
		{
			insertMoney += 25;
			insertQuarters++;
		}
		else if (coins == 10)
		{
			insertMoney += 10;
			insertDimes++;
		}
		else if (coins == 5)
		{
			insertMoney += 5;
			insertNickels++;
		}
		cin >> coins;
	}
}

void addCoins(int &quarters, int &dimes, int&nickels, int q, int d, int n)
{
	quarters += q;
	dimes += d;
	nickels += n;
}

void subtractCoins(int &quarters, int &dimes, int&nickels, int q, int d, int n)
{
	quarters -= q;
	dimes -= d;
	nickels -= n;
}

void resetInsertMoney(int &insertMoney, int &insertQuarters, int &insertDimes, int &insertNickels)
{
	insertMoney = 0;
	insertQuarters = 0;
	insertDimes = 0;
	insertNickels = 0;
}

void finalReport(int dollars, int quarters, int dimes, int nickels, double balance)
{
	cout << "Number of dollars  : " << dollars << endl;
	cout << "Number of quarters : " << quarters << endl;
	cout << "Number of dimes    : " << dimes << endl;
	cout << "Number of nickels  : " << nickels << endl;
	cout << "Machine balance    : $" << balance << endl;
	cout << "Machine is shutting down. Good bye." << endl << endl;
}
