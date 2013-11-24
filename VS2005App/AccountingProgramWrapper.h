#pragma once

#include "AccountingProgram.h"

class AccountingProgramWrapper
{
public:
	AccountingProgramWrapper(void);
	~AccountingProgramWrapper(void);

	static void open();
	static void close();
	static AccountingProgram* ap;
};
