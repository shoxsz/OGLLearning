#include "string.hpp"

void split(const std::string& str, std::string delm, std::vector<std::string>& strs){
    unsigned int begin = 0, i;
    
	strs.clear();

    while((i = str.find_first_of(delm, begin)) != std::string::npos){
        strs.push_back(str.substr(begin, i - begin));
        begin = i+1;
    }
	strs.push_back(str.substr(begin, i - begin));
}