#ifndef TRANSAKCIJE_STRUKTURA
#define TRANSAKCIJE_STRUKTURA
#include<iostream>
#include<vector>
struct TransStruktura{
    std::string id;
    std::string simbol;
    std::string kolicina;
    std::string cena;
    std::string operacija;
    friend std::ostream& operator<<(std::ostream& os, TransStruktura ts){
        os << " " << ts.id << " " << ts.simbol << " " << ts.simbol << " " << ts.kolicina << " " << ts.cena;
        os << " " << ts.operacija << std::endl;
        return os;
    }
};
typedef std::vector<TransStruktura> Transakcije;
#endif