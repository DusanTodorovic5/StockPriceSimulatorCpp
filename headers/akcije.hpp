#ifndef AKCIJE_STRUKTURA
#define AKCIJE_STRUKTURA

#include<vector>
#include<string>
#include<iostream>
struct Vrednosti{
    int idAkc;
    std::string simbol;
    std::string kolicina;
    std::string cena;
    friend std::ostream& operator<<(std::ostream& os, Vrednosti vs){
        os << vs.idAkc << " ";
        os << vs.simbol << " ";
        os << vs.kolicina << " ";
        os << vs.cena;
        return os;
    }
};
typedef std::vector<Vrednosti> Akcija;

#endif