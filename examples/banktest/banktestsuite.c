#include "banktestsuite.h"

int setupBankTestSuite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Bank Test Suite", initBankTestSuite, cleanBankTestSuite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of testBankCreation()", testBankCreation)) ||
		(NULL == CU_add_test(pSuite, "test of testBankCreationWithAmount()", testBankCreationWithAmount)) ||
		(NULL == CU_add_test(pSuite, "test of testAddingAmount()", testAddingAmount)) ||
		(NULL == CU_add_test(pSuite, "test of testAddingWrongAmount()", testAddingWrongAmount)) ||
		(NULL == CU_add_test(pSuite, "test of testRetreivingAmount()", testRetreivingAmount)) ||
		(NULL == CU_add_test(pSuite, "test of testRetreivingWrongAmount()", testRetreivingWrongAmount)))
	{
		return -1;
	}
	return 0;
}

int initBankTestSuite(void)
{
	return 0;
}

int cleanBankTestSuite(void)
{
	return 0;
}

void testBankCreation(void)
{
	char *name = "1234567";
	BankAccount *b = newBankAccount(name);
	CU_ASSERT(0 == strcmp(b->accountNumber, name));
	CU_ASSERT(0 == b->balance);
}

void testBankCreationWithAmount(void)
{
	char *name = "1234567";
	int amount = 123;
	BankAccount *b = newBankAccountWithAmount(name, amount);
	CU_ASSERT(0 == strcmp(b->accountNumber, name));
	CU_ASSERT(amount == b->balance);
}

void testAddingAmount(void)
{
	int amount = 100;
	int secondAmount = 50;
	int thirdAmount = 0;
	
	BankAccount *b = newBankAccount("Some name");
	addMoneyToBankAccount(b, amount);
	CU_ASSERT(amount == b->balance);
	
	addMoneyToBankAccount(b, secondAmount);
	CU_ASSERT((amount+secondAmount) == b->balance);
	
	addMoneyToBankAccount(b, thirdAmount);
	CU_ASSERT((amount+secondAmount+thirdAmount) == b->balance);
}

void testAddingWrongAmount(void)
{
	int amount = -1;
	int secondAmount = 50;
	int thirdAmount = -40;
	
	BankAccount *b = newBankAccount("Some name");
	addMoneyToBankAccount(b, amount);
	CU_ASSERT(0 == b->balance);
	
	addMoneyToBankAccount(b, secondAmount);
	CU_ASSERT(secondAmount == b->balance);
	
	addMoneyToBankAccount(b, thirdAmount);
	CU_ASSERT(secondAmount == b->balance);
}

void testRetreivingAmount(void)
{
	int beginAmount = 1000;
	int firstAmount = 100;
	int secondAmount = 50;
	int thirdAmount = 0;
	int expected, retreiveResult;
	
	BankAccount *b = newBankAccountWithAmount("Some name", beginAmount);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, firstAmount);
	expected = beginAmount - firstAmount;
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == firstAmount);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, secondAmount);
	expected = beginAmount - (firstAmount + secondAmount);
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == secondAmount);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, thirdAmount);
	expected = beginAmount - (firstAmount + secondAmount + thirdAmount);
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == thirdAmount);
}

void testRetreivingWrongAmount(void) 
{
	int beginAmount = 1000;
	int firstAmount = -100;
	int secondAmount = 50;
	int thirdAmount = -1;
	int expected, retreiveResult;
	
	BankAccount *b = newBankAccountWithAmount("Some name", beginAmount);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, firstAmount);
	expected = beginAmount;
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == 0);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, secondAmount);
	expected = beginAmount - secondAmount;
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == secondAmount);
	
	retreiveResult = retrieveMoneyFromBankAccount(b, thirdAmount);
	expected = beginAmount - secondAmount;
	CU_ASSERT( expected == b->balance);
	CU_ASSERT( retreiveResult == 0);
}