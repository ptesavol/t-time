// Tokenizer.h: interface for the Tokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENIZER_H__17709721_B095_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_TOKENIZER_H__17709721_B095_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

using namespace std;

class Tokenizer  
{

private:
	vector<string> ret;
	int begin;
	string buffer;
	string separator;
	string endline;

public:
	Tokenizer(const char* buf, int blen);
	Tokenizer(const char* buf, int blen, const string& separator, const string& endline);
	vector<string>* getNext();
	virtual ~Tokenizer();

};

#endif // !defined(AFX_TOKENIZER_H__17709721_B095_11D8_80E8_0010A4DF8E4B__INCLUDED_)
