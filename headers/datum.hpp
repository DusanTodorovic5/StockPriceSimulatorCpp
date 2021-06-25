#ifndef DATUM_KLASA
#define DATUM_KLASA
#include<vector>
#include<iostream>
#include<string>
#include<ctime>
class Datum{
    private:
        std::vector<int> _od;
        std::vector<int> _do;
        tm t1; 
        tm t2;
        std::string proveraGodine(int,int,int);
        std::string proveri(std::vector<int>);
    public:
        Datum(std::vector<int>,std::vector<int>);
        std::pair<std::string,std::string> ispravan();
        tm vrati_od();
        tm vrati_do();
        static long vrati_trenutno();
};
#endif