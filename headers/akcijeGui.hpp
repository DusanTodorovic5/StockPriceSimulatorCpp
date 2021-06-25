#ifndef AKCIJE_GUI_KLASA
#define AKCIJE_GUI_KLASA
#include "sqlBaza.hpp"
#include "parser.hpp"
#include "tabela.hpp"
#include <ctime>
#include <cctype>
#include <algorithm>
class AkcijeGui {
private:
    double sumaNovca;
    int idKor;
    Akcija akcija;
    std::map<std::string, double> mapa;
    void azurirajTrenutne();
    std::string novacLabelaString;
public:
    AkcijeGui(int);
    mapaTabele init_tabela();
    const char* vrati_novac();
};

#endif