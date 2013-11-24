#pragma warning(disable: 4786)

#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

namespace StringHelper
{
#define SPACES " \t\r\n"

string trim_right (const string & s, const string & t = SPACES);
string trim_left (const string & s, const string & t = SPACES); 
string trim (const string & s, const string & t = SPACES);
int axtoi(const string& s);
vector<string> split(const string& s, char c);
int parseInt(const string& s);
string toString(int n);
int parseRGB(const string& s);
void replaceAll(std::string* const cpstrSource, const std::string& refcstrSearch, const std::string& refcstrReplace);
string unescape(string& s);
string escape(string& s);
bool isNumeric(const string& s);
string itoa(int i, int radix);
}


#endif