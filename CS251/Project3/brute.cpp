#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>


#include "key.hpp"
#include "brute.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();

}


void Brute::doBrute(const char str[],std::string prefix,const int n, const int length) {
	if (length == 1) {
		for (int j = 0; j < n - 1; j++) {
			Key enKey (encrypted);
			Key toKey (prefix + str[j]);
			Key keyception = toKey.subset_sum(this->T, false);
			//std::cout << keyception.getBinaryValue() << std::endl;


			if (keyception == enKey) {
				std::cout << prefix + str[j] << std::endl;
			}


		}
	} else {
		for (int i = 0; i < n - 1; i++)
			doBrute(str, prefix + str[i], n, length - 1);
	}

}

std::vector<Key> Brute::getT() {

	return this->T;

}


void Brute::decrypt(const std::string& encrypted){

	Key enKey (encrypted);

	//std::cout << enKey.getBinaryValue() << std::endl;

	// Generate all possible keys and match to binary value of enKey
    int length = encrypted.length();

    int n = sizeof ALPHABET;

    doBrute(ALPHABET, "", n, length); 

}


void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
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

	Brute brute (table_filename);

	brute.decrypt(encrypted);

	return 0;
}