#include "transakcijeGui.hpp"
TransakcijeGui::TransakcijeGui(std::vector<TransStruktura> a, int X, int Y, int W, int H, const char* L)
    : Fl_Scroll(X, Y, W, H, L) {
    vt = a;
    static const char* header[5] = { "ID", "Simbol", "Kolicina", "Cena", "Operacija" };
    int cellw = 100;
    int cellh = 25;
    int xx = X, yy = Y;
    tile = new Fl_Tile(X, Y, cellw * 5, cellh * vt.size() + 35);
    Fl_Box** k = new Fl_Box * [5];
    for (int i = 0; i < 5; i++) {
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
    std::cout << vt.size() << std::endl;
    for (auto const& x : vt)
    {
        Fl_Box** rezptr = new Fl_Box * [7];
        Fl_Color(49);
        box = new Fl_Box(xx, yy, cellw, cellh, x.id.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[0] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.simbol.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[1] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.kolicina.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[2] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.cena.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[3] = box;
        xx += cellw;
        box = new Fl_Box(xx, yy, cellw, cellh, x.operacija.c_str());
        box->box(FL_BORDER_BOX);
        rezptr[4] = box;
        xx += cellw;
        xx = X;
        yy += cellh;
        niz.push_back(rezptr);
    }
    tile->end();
    end();
}
TransakcijeGui::~TransakcijeGui() {
    for (int i = 0; i < niz.size(); i++) {
        delete niz[i][0];
        delete niz[i][1];
        delete niz[i][2];
        delete niz[i][3];
        delete niz[i][4];
        delete niz[i];
    }
    delete tile;
}