#pragma warning(disable: 4786)

#include "StdAfx.h"
#include "Properties.h"
#include <iostream>
#include <fstream>
#include "StringHelper_luokka.h"
#include "defines.h"

using namespace std;

Properties::Properties(const string& filename)
{
	this->fileName = filename;
	ifstream bstream(filename.c_str());
	string key;
	string value;

	string line;
	while(true)
	{
		if(!getline(bstream, line, '\n'))
			break;
		if(line.length() == 0)
			continue;

		line=StringHelper::trim(line);

		if(line.length() == 0)
			continue;
		if(line[0] == '#')
			continue;

		int k = line.find('='); 

		if(k != -1)
		{
			key = StringHelper::trim(line.substr(0, k));
			value = StringHelper::trim(line.substr(k + 1));

			this->properties[key] = value;
		}
	}
	bstream.close();
}

string Properties::get(const string& key)
{
	//return this->properties[key];
	return StringHelper::unescape(this->properties[key]);
}

void Properties::set(const string& key, const string& value)
{
	string tempss = value;
	this->properties[key] = tempss;//StringHelper::escape(tempss);
	ofstream off(fileName.c_str());

	map<string, string>::iterator it = this->properties.begin();
	while(it != this->properties.end())
	{
		off << it->first;
		off << "=";
		off << it->second;
		off << endl;
		it++;
	}
	off.close();
}
