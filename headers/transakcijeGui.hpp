#ifndef TRANSAKCIJE_KLASA
#define TRANSAKCIJE_KLASA
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <string>
#include <iostream>
#include <vector>
#include "transakcije.hpp"
#define ROWS 20
class TransakcijeGui : public Fl_Scroll {
private:
    std::vector<TransStruktura> vt;
    Fl_Tile* tile;
    void* w[100][5];
    std::vector<Fl_Box**> niz;
public:
    TransakcijeGui(std::vector<TransStruktura> a, int X, int Y, int W, int H, const char* L = 0);
    ~TransakcijeGui();
};
#endif