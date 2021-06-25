#ifndef SVECA_STRUCT
#define SVECA_STRUCT
#include <iostream>
#include <iomanip>
struct Sveca{
    double timestamp;
    double open;
    double close;
    double high;
    double low;
    friend std::ostream& operator<<(std::ostream& os,const Sveca& sv){
        os<<std::fixed;
        os<<std::setprecision(5);
        std::string boja = "\033[0;32m";
        if (sv.close > sv.open) boja = "\033[0;31m";
        os << boja;
        os << "Timestamp : " << sv.timestamp << std::endl;
        os << "\tOpen : " << sv.open << std::endl;
        os << "\tClose : " << sv.close << std::endl;
        os << "\tHigh : " << sv.high << std::endl;
        os << "\tLow : " << sv.low << std::endl;
        os << "\033[0;37m";
        return os;
    }
};
#endif