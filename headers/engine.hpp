#ifndef ENGINE_KLASA
#define ENGINE_KLASA
#include "datum.hpp"
#include "sqlBaza.hpp"
#include "parser.hpp"
#include <map>
enum class Stanje { LOGIN = 0, REGISTRACIJA, GLAVNI, TRANSAKCIJE, AKCIJE, IZLAZ };
typedef std::map<std::string, double> MapaAkcija;
class Engine{
    protected:    
        Stanje stanje;
        Podaci podaci;
        Parser parser;
        int id;
        std::string username;
        std::string novac;
        virtual void login() = 0;
        virtual void registracija() = 0;
        virtual void glavni_prozor() = 0;
        virtual void transakcije() = 0;
        virtual void akcije() = 0;
        MapaAkcija azurirajMapu(Akcija akcija) {
            MapaAkcija mapa;
            Parser p;
            Podaci pod;
            std::time_t tsad = std::time(0);
            long tpre = tsad - 345600;
            for (auto const& x : akcija) {
                if (mapa.find(x.simbol) == mapa.end()) {
                    pod = p(x.simbol, std::to_string(tsad), std::to_string(tpre));
                    std::pair<std::string, double> par;

                    par.first = pod.vrati_simbol();
                    std::transform(par.first.begin(), par.first.end(), par.first.begin(),
                        [](unsigned char c) { return std::tolower(c); });
                    par.second = pod[pod.vrati_velicinu() - 1].close;
                    mapa.insert(par);
                }
            }
            return mapa;
        }
        double inline razlika(double a, double b) {
            return a > b ? a - b : b - a;
        }
        double inline procRazlika(double a, double b) {
            return (a > b ? a - b : b - a) / ((a + b) / 2) * 100;
        }
    public:
        void start() {
            while (stanje != Stanje::IZLAZ) {
                switch (stanje) {
                    case Stanje::LOGIN: login(); break;
                    case Stanje::REGISTRACIJA: registracija(); break;
                    case Stanje::GLAVNI: glavni_prozor(); break;
                    case Stanje::TRANSAKCIJE: transakcije(); break;
                    case Stanje::AKCIJE: akcije(); break;
                }
            }
        }
        Engine() {
            stanje = Stanje::LOGIN;
            SQL::init();
            long tren = Datum::vrati_trenutno();
            podaci = parser("aapl", std::to_string(tren), std::to_string(tren - 345600));
        }
        ~Engine() {
            SQL::finish();
        }
};
#endif