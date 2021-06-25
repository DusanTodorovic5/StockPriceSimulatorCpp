
#ifndef PODACI_KLASA
#define PODACI_KLASA
#include "sveca.hpp"
#include <vector>
#include <string>
class Podaci{
    private:
        std::string valuta;
        std::string simbol;
        std::string exchangeName;
        std::string vremenskaZona;
        std::vector<Sveca> niz;
        std::vector<double> ema;
        std::vector<double> ma;
    public:
        Podaci();
        Podaci(std::string,std::string,std::string,std::string,std::vector<Sveca>);
        Sveca operator[](int);
        int vrati_velicinu() const;
        std::vector<Sveca> vrati_svece();
        std::string vrati_valutu() const;
        std::string vrati_simbol() const;
        std::string vrati_exchangeName() const;
        std::string vrati_vremenskaZona() const;
        std::vector<double> vrati_Ema(int);
        std::vector<double> vrati_Ma(int);
        friend std::ostream& operator<<(std::ostream& os,const Podaci&);
};
#endif