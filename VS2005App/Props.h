#pragma warning(disable: 4786)

#ifndef PROPS_H
#define PROPS_H

#include <string>
#include <map>
#include <fstream>
#include "Properties.h"
#include "taika.h"

using namespace std;

class Props 
{
public:
	static Props& i();
	static CTaikaApp& e();
	string get(const string& key);
	CString lang(const string& key);
	CString format(CString str);
	int langl(const string& key);
	char *langs(const string& key, char *pbuf, int buflen);
	void set(const string& key, const string& value);

private:
	Props();
	~Props();
	static Props* _instance;

	Properties* properties;
	Properties* language;
};

#endif