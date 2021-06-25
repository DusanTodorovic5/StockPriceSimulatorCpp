#include "tabela.hpp"

Tabela::Tabela(mapaTabele a, int X, int Y, int W, int H, const char* L) : Fl_Scroll(X, Y, W, H, L) {
    ts = a;
    static const char* header[7] = {
        "IdKupovine", "Simbol", "Kolicina", "Cena",
        "Trenutna Cena", "Razlika", "Razlika u %"
    };
    int cellw = 100;
    int cellh = 25;
    int xx = X, yy = Y;
    tile = new Fl_Tile(X, Y, cellw * 7, cellh * ts.size() + 30);
    Fl_Box** k = new Fl_Box * [7];
    for (int i = 0; i < 7; i++) {
        Fl_Box* box = new Fl_Box(xx, yy, cellw, cellh, header[i]);
        box->box(FL_BORDER_BOX);
        k[i] = box;
        xx += cellw;
    }
    niz.push_back(k);
    xx = X;
    yy += cellh;
    int i = 1;
    Fl_Box* box = nullptr;

    std::cout << ts.size() << std::endl;
    for (auto const& x : ts)
    {
        Fl_Box** rezptr = new Fl_Box * [7];
        Fl_Color(49);
        box = new Fl_Box(xx, yy, cellw, cellh, x.first.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[0] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.second.akcija.simbol.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[1] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.second.akcija.kolicina.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[2] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.second.akcija.cena.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[3] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.second.trenutna.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[4] = box;
        xx += cellw;

        box = new Fl_Box(xx, yy, cellw, cellh, x.second.razlika.c_str());
        box->box(FL_BORDER_BOX);
        if (x.second.razlika.length() > 0 && x.second.razlika[0] == '-')
            box->color(130);
        else
            box->color(71);
        rezptr[5] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.second.procentualna.c_str());
        box->box(FL_BORDER_BOX);
        if (x.second.razlika.length() > 0 && x.second.razlika[0] == '-')
            box->color(130);
        else
            box->color(71);
        rezptr[6] = box;
        xx = X;
        yy += cellh;
        niz.push_back(rezptr);
    }
    tile->end();
    end();
}
Tabela::~Tabela() {
    for (int i = 0; i < niz.size(); i++) {
        delete niz[i][0];
        delete niz[i][1];
        delete niz[i][2];
        delete niz[i][3];
        delete niz[i][4];
        delete niz[i][5];
        delete niz[i][6];
        delete niz[i];
    }
    delete tile;
}