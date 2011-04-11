#ifndef BANKTESTSUITE_H
#define BANKTESTSUITE_H

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "bankaccount.h"

//Setup in CUnit
int setupBankTestSuite(void);

//init + breakdown
int initBankTestSuite(void);
int cleanBankTestSuite(void);
 
//Tests
void testBankCreation(void);
void testBankCreationWithAmount(void);
void testAddingAmount(void);
void testAddingWrongAmount(void);
void testRetreivingAmount(void);
void testRetreivingWrongAmount(void);

#endif