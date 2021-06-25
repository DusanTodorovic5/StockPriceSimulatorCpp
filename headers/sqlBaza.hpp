#ifndef SQL_KLASA
#define SQL_KLASA
#include "sqlite3.h"
#include "akcije.hpp"
#include <vector>
#include <iostream>
#include "transakcije.hpp"
class SQL {
    private:
        static int id;
        static sqlite3* db;
        SQL();
    public:
        static void init();
        static void finish();
        static std::pair<int,std::string> loginPass(std::pair<std::string,std::string>);
        static std::string registracija(std::string,std::string,int);
        static double novac(int);
        static Akcija akcije(int);
        static int kupi(int,std::string,int,double);
        static int prodaj(int,int,double,int);
        static std::string simbol(int);
        static Transakcije transakcije(int);
};

#endif