#pragma warning(disable: 4786)

#include "StdAfx.h"
#include "Props.h"
#include "StringHelper_luokka.h"

using namespace std;

Props* Props::_instance = 0;

Props::Props()
{
	string path = ((CTaikaApp*)AfxGetApp())->m_app_path;
	this->properties = new Properties(path + "\\t-aika.options");
	this->language = new Properties(path + "\\t-aika_fi.language");
}

Props::~Props()
{
	delete this->properties;
}

Props& Props::i()
{
	if(_instance == 0)
		_instance = new Props();
	return *_instance;
}

CTaikaApp& Props::e()
{
    extern CTaikaApp theApp;
	return theApp;
}

string Props::get(const string& key)
{
	return StringHelper::trim(this->properties->get(key));
}

void Props::set(const string& key, const string& value)
{
	this->properties->set(key, value);
}

CString Props::lang(const string& key)
{
	return format(StringHelper::trim(this->language->get(key)).c_str());
}

int Props::langl(const string& key)
{
	CString str = format(StringHelper::trim(this->language->get(key)).c_str());
	return str.GetLength();
}

char *Props::langs(const string& key, char *pbuf, int buflen)
{
	int v, s, p, i;
	vector<string> vect = StringHelper::split(StringHelper::trim(this->language->get(key)), '@');
	for(v=0, p=0; v<vect.size(); v++)
	{
		for(i=0; i<vect[v].size(); i++)
		{
			if(p >= buflen) break;
			pbuf[p++] = vect[v].at(i);
		}

		if(p >= buflen) break;
		pbuf[p++] = 0;
	}

	return pbuf;
}

CString Props::format(CString str)
{
	str.Replace("\\n", "\n");
    str.Replace("\\r", "\r");
    str.Replace("\\t", "\t");

	return str;
}