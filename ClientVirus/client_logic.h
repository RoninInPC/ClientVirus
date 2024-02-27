#pragma once


#include"el_gamal.h"
#include"finder_extension.h"
class ClientLogic final{
private:
	static inline AbstractAsymmetricalEncryption* el_gamal_ = new ElGamal(31,32,29);
	static inline FinderExtension finder;

private:
	static bool ValidateExtensions(const std::string& string) {
		return string.find(';') != -1;
	}
	static std::set<std::string> ToSet(std::string str) {
		std::set<std::string> set_str;
		std::string word;

		std::istringstream iss(str);
		while (std::getline(iss, word, ';')) {
			set_str.insert(word);
		}
		return set_str;
	}
public:
	static std::vector<std::string> Logic(const std::string& command, const std::string& message) {
		if (command == "get" and message == "files") {
			finder.FindPaths();
			return finder.GetPaths();
		}
		if (command == "set" and ValidateExtensions(message)) {
			finder.SetExtensions(ToSet(message));
			
		}
		return {};	
	}
};