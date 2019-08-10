//
// Created by mdavies4 on 08/07/2019.
//
#include "common_tools.hpp"
#include <string>
#include <sstream>

std::string reduce(const std::string& str,
                   const std::string& fill,
                   const std::string& whitespace);
std::string trim(const std::string& str,
                 const std::string& whitespace);



const char* string_to_const_char_pointer(std::string String){
    const char* n_char = String.c_str();
    return n_char;
}


bool is_string_number(std::string string_orig){
    std::string string = reduce(string_orig,"","\t");
    for(int i = 0; i < string.length(); i++)//for each char in string,
        if(! (string[i] >= '0' && string[i] <= '9') ) return false;
    //if string[i] is between '0' and '9' of if it'string a whitespace (there may be some before and after
    // the number) it'string ok. otherwise it isn't a number.

    return true;
}

const char* int_to_const_char_pointer(int number){
    std::string s = std::to_string(number);
    char const* pchar = s.c_str();
    return pchar;
}


int string_to_int(std::string String){

    if (!is_string_number(String))
        throw std::invalid_argument( "Value received was not an integer ." );
    int n_int;
    std::istringstream iss (String);
    iss >> n_int;
    if (iss.fail())
        throw std::invalid_argument( "Value received was not an integer ." );
    return n_int;
}


std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill = "",
                   const std::string& whitespace = " \t"){
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}