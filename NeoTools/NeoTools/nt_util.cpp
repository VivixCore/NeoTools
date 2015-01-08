#include "nt_util.h"
#include <fstream>
#include <sstream>

int nt_util::openTextFile(std::string filename, /*vcList<std::string>*/std::vector<std::string> &d, int failurecode)
{
	std::ifstream ifs(filename);
	if(ifs.fail())
		return failurecode;

	std::string temp;
	while(std::getline(ifs,temp))
	{
		if((temp.substr(0,2)!="//") && (temp!=""))
		d.push_back(temp);
	}
	ifs.close();
	return 0;
}

std::string nt_util::num2string(int number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::string nt_util::num2string2(int number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	if(ss.str().size()<2)
	return "0"+ss.str();
	return ss.str();//return a string with the contents of the stream
}

std::string nt_util::num2string(double number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::vector<std::string>/*vcList*/ nt_util::pipe2StringVector(std::string csv)
{
	std::stringstream ss(csv);
	//vcList<std::string> out;
	std::vector<std::string> out;
	std::string s;

	while (std::getline(ss, s, '|')) 
		out.push_back(s);
	return out;
}