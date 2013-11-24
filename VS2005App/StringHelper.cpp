#include "StdAfx.h"
#include "StringHelper_luokka.h"

namespace StringHelper
{
#define SPACES " \t\r\n"

string unescape(string& s)
{
	string search = "\\\\";
	string rep = "\\";
	replaceAll(&s, search, rep);

	/*search = "\\:";
	rep = ":";
	replaceAll(&s, search, rep);*/

	return s;
}

string escape(string& s)
{
	string search = "\\";
	string rep = "\\\\";
	replaceAll(&s, search, rep);

	/*search=":";
	rep ="\\";
	rep += ":";
	replaceAll(&s, search, rep);*/

	return s;
}

bool isNumeric(const string& s)
{
    BOOL dpnt = FALSE;

	if(s.length() == 0)
		return false;

	for (int i=0; i<s.length(); i++)
	{
		if(s[i] == '.' || s[i] == ',')
		{ // allow one decimal point
		  if(dpnt) return false;
		  dpnt = TRUE;
		  continue;
		}

		if (s[i] > '9' ||s[i] < '0')
			return false;
	}

	return true;
}

void replaceAll(std::string* const cpstrSource, const std::string& refcstrSearch, const std::string& refcstrReplace)
{
	std::string::size_type pos = 0;

	while((pos = cpstrSource->find(refcstrSearch, pos)) != std::string::npos)
	{
		cpstrSource->replace(pos, refcstrSearch.length(), refcstrReplace);
		pos += refcstrReplace.length();
	}
}

string trim_right (const string & s, const string & t)
{ 
	string d (s); 
	string::size_type i (d.find_last_not_of (t));
	if(i == string::npos)
		return "";
	else
		return d.erase (d.find_last_not_of (t) + 1) ; 
}  // end of trim_right

string trim_left (const string & s, const string & t ) 
{ 
	string d (s); 
	return d.erase (0, s.find_first_not_of (t)) ; 
}  // end of trim_left

string trim (const string & s, const string & t )
{ 
	string d (s); 
	return trim_left (trim_right (d, t), t) ; 
}  // end of trim

int axtoi(const string& owsi) 
{
	const char* hexStg = owsi.c_str();
	int n = 0;			// position in string
	int m = 0;			// position in digit[] to shift
	int count;			// loop index
	int intValue = 0;	// integer value of hex string
	int digit[5];		// hold values to convert
	while(n < 4)
	{
		if (hexStg[n]=='\0')
			break;
		if (hexStg[n] > 0x29 && hexStg[n] < 0x40 )		// if 0 to 9
			digit[n] = hexStg[n] & 0x0f;				// convert to int
		else if (hexStg[n] >='a' && hexStg[n] <= 'f')	// if a to f
			digit[n] = (hexStg[n] & 0x0f) + 9;			// convert to int
		else if (hexStg[n] >='A' && hexStg[n] <= 'F')	// if A to F
			digit[n] = (hexStg[n] & 0x0f) + 9;			// convert to int
		else
			break;

		n++;
	}
	count = n;
	m = n - 1;
	n = 0;
	while(n < count)
	{
		// digit[n] is value of hex digit at position n
		// (m << 2) is the number of positions to shift
		// OR the bits into return value
		intValue = intValue | (digit[n] << (m << 2));
		m--;	// adjust the position to set
		n++;	// next digit to process
	}

	return (intValue);
}

vector<string> split(const string& s, char c)
{
	vector<string> ret;

	istringstream bstream(s);
	string line;

	while(getline(bstream,line,c))
	{
		ret.push_back (line);
	}
	return ret;
}

int parseInt(const string& s)
{
	return atoi(s.c_str());
}

string toString(int n)
{
	ostringstream os;
	os<<n;
	return os.str();
}

int parseRGB(const string& s)
{
	vector<string> vec=split(s,',');
	return RGB(parseInt(vec[0]),parseInt(vec[1]),parseInt(vec[2]));
}

string itoa(int i, int radix)
{
	string str;
	char cnv[32];

	::itoa(i, cnv, radix);

	str = cnv;
	return str;
}

}