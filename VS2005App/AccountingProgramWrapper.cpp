#include "stdafx.h"
#include "taika.h"
#include "AccountingProgramWrapper.h"
#include "Props.h"
#include "defines.h"
#include "NeuvosProgram.h"
#include "PasseliProgram.h"
#include "AccountingException.h"

AccountingProgram* AccountingProgramWrapper::ap = NULL;

AccountingProgramWrapper::AccountingProgramWrapper(void) {}
AccountingProgramWrapper::~AccountingProgramWrapper(void) {}

void AccountingProgramWrapper::open()
{
	close();

	CString laskutusohjelma = Props::i().get(OPTIONS_LASKUTUSOHJELMA).c_str();
	if(laskutusohjelma == LAS_MAATALOUSNEUVOS)       // :: hae/aseta tilinumerot
		ap = new NeuvosProgram();
	else if(laskutusohjelma == LAS_PASSELI)
		ap = new PasseliProgram();

	ap->open(Props::i().get(OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU).c_str());
}

void AccountingProgramWrapper::close()
{
	if(ap != NULL)
	{
		ap->close();
		delete ap;
		ap = NULL;
	}
}
