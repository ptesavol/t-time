// Tokenizer.cpp: implementation of the Tokenizer class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Tokenizer.h"
#include <algorithm>
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Tokenizer::Tokenizer(const char* buf, int bufsize)
	{
	this->begin=0;
	this->buffer=string(buf,0,bufsize);
	this->endline="\n";
	this->separator="	";
	}

Tokenizer::Tokenizer(const char* buf, int bufsize, const string& separator, const string& endline)
	{
	this->begin=0;
	this->buffer=string(buf,0,bufsize);
	this->separator=separator;
	this->endline=endline;
	}

// Returns the next line terminated by endline of eof tokenized by the boundaries of separator
vector<string>* Tokenizer::getNext()
	{
	//find endline or EOF
	if (begin>=buffer.length())
		return 0;
	int end=this->buffer.find(endline, begin);
	string temp;
	if (end==-1)
		{
		temp=buffer.substr(begin);
		this->begin=buffer.length();
		}
	else
		{
		temp=buffer.substr(begin,end-begin);
		this->begin=end+separator.length();
		}
	this->ret.clear();
	int i=0;
	int j=0;
	
	while (true)
		{
		if(temp.length()==0)
			break;
		if (i>=temp.length())
			{
			if ( (i-separator.length())>=0 && temp.substr((i-separator.length()),separator.length())==separator )
				{
				ret.push_back(string(""));
				//cout<<"Pushed back empty string"<<endl;
				}
			break;
			}

		j=temp.find(separator,i);
		if (j==-1)	
			{
			ret.push_back(temp.substr(i));
			//cout<<"Pushed back i"<<endl;
			break;
			}
		else
			{ 
			ret.push_back(temp.substr(i,j-i));
			//cout<<"Pushed back j-i"<<endl;
			}
		i=j+separator.length();
		}
	return &ret;
	}

Tokenizer::~Tokenizer()
{

}

