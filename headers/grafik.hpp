#ifndef GRAFIK_KLASA
#define GRAFIK_KLASA
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include "podaci.hpp"
#include <algorithm>
#include <iterator>
class Grafik : public Fl_Group {
private:
    std::vector<Sveca> pod;
    std::vector<Sveca> original;
    double minimum;
    double maximum;
    int visina;
    int sirina;
    double skala;
    bool ma;
    bool ema;
    int n;
    inline double konvert(double);
    inline double dekonvert(double);
    void srediNiz();
public:
    Grafik(std::vector<Sveca>, int, int, int, int, const char*);
    void value(std::vector<Sveca> podaci, std::pair<bool, bool> indikatori, int n = 0);
    void emaDraw();
    void maDraw();
    void draw();
};
#endif
