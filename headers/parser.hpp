#ifndef PARSER_KLASA
#define PARSER_KLASA
#include <curl/curl.h>
#include "podaci.hpp"
#include <regex>
class Parser{
    private:
        std::vector<std::string> podeli(std::string);
        Podaci parser(std::string readBuffer);
        std::string curlUpdate(std::string link);
    public:
        Podaci operator()(std::string,tm,tm);
        Podaci operator()(std::string,std::string, std::string);
};
#endif