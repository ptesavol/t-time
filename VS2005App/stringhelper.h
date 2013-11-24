#ifndef STRINGHELPER
#define STRINGHELPER

#include <string>
#include <strstream>

template<typename T>
string st(T figure)
	{
	ostrstream ostr;
  
    ostr << figure;
	string ret(ostr.str(),0,ostr.pcount());
    ostr.freeze(false);        
    return ret;    
	}

template<typename T>
string hex(T figure)
	{
	ostrstream ostr;
  
    ostr <<hex<< figure;
	string ret(ostr.str(),0,ostr.pcount());
    ostr.freeze(false);        
    return ret;    
	}

	/*
string st(double figure)
	{
	ostrstream ostr;
    
    ostr << figure;
	string ret(ostr.str(),0,ostr.pcount());
	
    ostr.freeze(0);        
    return ret;    
	}
*/
#endif

