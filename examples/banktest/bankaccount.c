#include "bankaccount.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


BankAccount * newBankAccount(char *accountNumber) {
	return newBankAccountWithAmount(accountNumber, 0);
}

BankAccount * newBankAccountWithAmount(char *accountNumber, int startAmount) {
	BankAccount *account = malloc(sizeof(BankAccount));
	
	//Setup account number
	account->accountNumber = malloc(strlen(accountNumber) + 1);
	strcpy(account->accountNumber, accountNumber);
	 
	//Setup balance
	account->balance = startAmount;
	
	return account;
}
void freeBankAccount(BankAccount *account) {
}

void addMoneyToBankAccount(BankAccount *account, int amount) {
	if (amount <= 0)
		return;
	account->balance += amount;
}
int retrieveMoneyFromBankAccount(BankAccount *account, int amount) {
	if (amount <= 0)
 		return 0;
	account->balance -= amount;
	return amount;
}