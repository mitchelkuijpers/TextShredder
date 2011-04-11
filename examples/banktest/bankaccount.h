#ifndef MAIN_H
#define MAIN_H

typedef struct {
	char *accountNumber;
	int balance;
} BankAccount;

BankAccount * newBankAccount(char *accountNumber);
BankAccount * newBankAccountWithAmount(char *accountNumber, int startAmount);
void freeBankAccount(BankAccount *account);

void addMoneyToBankAccount(BankAccount *account, int amount);
int retrieveMoneyFromBankAccount(BankAccount *account, int amount);
	
#endif