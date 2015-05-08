#include <iostream>
#include <boost/regex.hpp>
#include <string>

/*

	Using boost library (libboost-regex-dev on ubuntu) to perform regular expression check

	Use linker -lboost_regex when compile with g++
	To compile: g++ -Wall email_regex_boost.cpp -o email_regex -lboost_regex

	It has been shown to be a mission impossible to "perfectly" match all email addresses with Regular Expression. But it is not hard to make it enough-to-use.

	Rules defined here: 
		There must be only one '@' and at least one '.' in the e-mail address.
		Characters allowed is '0~9' all letter in both cases '.' '_'  and '-'

*/


int main() {

	boost::regex email_verify("^([a-zA-Z0-9]+[a-zA-Z0-9._-]+[@]+[a-zA-Z0-9_-]++[.]+[a-zA-Z0-9._-]+)$");
	std::string instr;

	while(1) {

		std::cout << "input e-mail: ";
		std::cin >> instr;

		if ( instr == "exit" || instr == "quit" ) break;

		if ( regex_match(instr, email_verify) ) 
			std::cout << "valid\n";
		else
			std::cout << "invalid\n";

	}


	return 0;
}
