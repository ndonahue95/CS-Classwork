#ifndef _BRUTE_HPP_
#define _BRUTE_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"

class Brute {
private:
	std::vector<Key> T;

public:
	virtual std::vector<Key> getT();
	Brute(const std::string&);
	void decrypt(const std::string&);
	void doBrute(const char*,std::string,const int, const int);
	std::vector<Key> possiblePasswords; 
};

#endif
