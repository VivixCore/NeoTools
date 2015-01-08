#pragma once
#ifndef nt_UTIL_H_INCLUDED
#define nt_UTIL_H_INCLUDED
#include <string>
#include <vector>

namespace nt_util
{
	int openTextFile(std::string,std::vector<std::string>&,int);//vcList<std::string>&,int);
	std::string num2string(int);
	std::string num2string2(int);
	std::string num2string(double);
	std::vector<std::string> pipe2StringVector(std::string);
}

#endif