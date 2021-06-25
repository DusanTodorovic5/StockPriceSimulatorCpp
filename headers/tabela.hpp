#ifndef TABELA_KLASA
#define TABELA_KLASA

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include "akcije.hpp"
#include <iostream>
#include <vector>
#include <map>
#define ROWS 20
struct tabelaStruktura {
    Vrednosti akcija;
    std::string trenutna;
    std::string razlika;
    std::string procentualna;
    inline double proc(double t1, double t2) {
        return abs(t1 - t2) / ((t1 + t2) / 2) * 100;
    }
    void dodaj() {
        double tren = std::stod(trenutna);
        double kup = std::stod(akcija.cena);
        razlika = std::to_string(tren - kup);
        procentualna = std::to_string(proc(tren, kup));
    }
};
typedef std::map<std::string, tabelaStruktura> mapaTabele;
class Tabela : public Fl_Scroll {
private:
    Fl_Tile* tile;
    mapaTabele ts;
    std::vector<Fl_Box**> niz;
public:
    Tabela(mapaTabele a, int X, int Y, int W, int H, const char* L = 0);
    ~Tabela();
};

#endif