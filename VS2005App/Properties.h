#pragma warning(disable: 4786)

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

class Properties
{
public:
	Properties(const string& filename);

	string get(const string& key);
	void set(const string& key,const string& value);
 
private:
	map<string,string> properties;
	string fileName;
};

#endif