#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "key.hpp"
#include "symbol.hpp"




// TODO
// - generate brute on first half
// - loop through second half of T (from index you havnt used yet) 
//    - repetitively generate subset sums and create hash map 
// - for each first half subset sum do a map.get(key) and add to second half
//	  - if it equals encrupyed key its a password!


// map like dis: key = string stringPasswordValue   |    value = someLong binaryInIntegerValue






std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

std::unordered_map<long long,std::string> my_map;

Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();

}

void Symbol::doMiniBrute(const char str[],std::string prefix,const int n, const int length) {
	if (length == 1) {
		for (int j = 0; j < n - 1; j++) {

			// make string
			std::string newStr = prefix + str[j];

			// make 'a' string
			std::string aaa = "";
			for (int i = 0; i < (encrypted.length() - newStr.length()); i++)
					aaa = aaa + "a";

			Key newKey (prefix + str[j] + aaa);
			Key ssKey = newKey.subset_sum(this->T, false);
			Key enKey (encrypted);
			
			// do brute?
			long long enKeyInt = enKey.getIntValue();
			long long ssKeyInt = ssKey.getIntValue();

			long long toFind = (enKeyInt - ssKeyInt);
            
            enKey -= ssKey;
            toFind = enKey.getIntValue();

			std::unordered_map<long long,std::string>::const_iterator omgwat = my_map.find(toFind);

			if (omgwat != my_map.end()) {
				std::cout << prefix + str[j] << omgwat->second << std::endl;
			}


            if (newStr == "pass") {
			//	std::cout << "pass found   |sskey   " << ssKeyInt << "    |enkey    " << enKeyInt << std::endl;
            }

		}

	} else {
		for (int i = 0; i < n - 1; i++)
			doMiniBrute(str, prefix + str[i], n, length - 1);
	}

}

void Symbol::getPerms(const char str[],std::string prefix,const int n, const int length) {
	if (length == 1) {
		for (int j = 0; j < n - 1; j++) {

			// make string
			std::string newStr = prefix + str[j];

			// make 'a' string
			std::string aaa = "";
			for (int i = 0; i < (encrypted.length() - newStr.length()); i++)
					aaa = aaa + "a";

			Key newKey (aaa + newStr);
			Key ssKey = newKey.subset_sum(this->T, false);

			// add to map
			my_map.insert({ssKey.getIntValue(), newStr});
            
            if (newStr == "word") {
               // std::cout << "word found   |   " << ssKey.getIntValue() << std::endl;
            }

		}
	} else {
		for (int i = 0; i < n - 1; i++)
			getPerms(str, prefix + str[i], n, length - 1);
	}

}

void Symbol::decrypt(const std::string& encrypted){

	getPerms(ALPHABET, "", sizeof (ALPHABET), encrypted.length() / 2); 

	doMiniBrute(ALPHABET, "", sizeof (ALPHABET), encrypted.length() - (encrypted.length() / 2)); 


}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	
	initialize(argc, argv);

	Symbol sBrute (table_filename);

	sBrute.decrypt(encrypted);
	
	return 0;
}
