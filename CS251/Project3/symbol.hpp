#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"

class Symbol {
private:
	std::vector<Key> T;
	
public:
	Symbol(const std::string&);
	void decrypt(const std::string&);
	void getPerms(const char*,std::string,const int, const int);
	void doMiniBrute(const char*,std::string,const int, const int);
};

#endif