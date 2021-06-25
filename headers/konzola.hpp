#ifndef KONZOLA_ENGINE
#define KONZOLA_ENGINE
#include "engine.hpp"
class Konzola : public Engine {
    protected:
        void login();
        void registracija();
        void glavni_prozor();
        void transakcije();
        void akcije();
        void prikaziAkcije();
};

#endif