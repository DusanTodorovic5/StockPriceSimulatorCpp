#include "grafik.hpp"
Grafik::Grafik(std::vector<Sveca> pod, int X, int Y, int W, int H, const char* L = 0) : Fl_Group(X, Y, (pod.size() > 25 ? pod.size() : 25) * 36, H, L) {
    this->original = pod;
    this->pod = pod;
    visina = H;
    sirina = 35;
    auto maxEl = std::max_element(pod.begin(), pod.end(),
        [](const Sveca& a, const Sveca& b)
        {
            return a.high < b.high;
        });
    if (pod.size() > 0) {
        maximum = maxEl->high;
        srediNiz();
    }
}
void Grafik::srediNiz() {
    auto minEl = std::min_element(pod.begin(), pod.end(),
        [](const Sveca& a, const Sveca& b)
        {
            return a.low < b.low;
        });
    minimum = minEl->low;
    skala = ((double)visina - 80 + (double)y()) / (maximum - minimum);
    for (int i = 0; i < pod.size(); i++) {
        pod[i].low = konvert(pod[i].low);
        pod[i].high = konvert(pod[i].high);
        pod[i].open = konvert(pod[i].open);
        pod[i].close = konvert(pod[i].close);
    }
}
inline double Grafik::konvert(double t) {
    return (t - minimum) * skala + 20;
}
inline double Grafik::dekonvert(double t) {
    return (t - 20) / skala + minimum;
}
void Grafik::value(std::vector<Sveca> podaci, std::pair<bool, bool> indikatori, int n) {
    if (podaci.size() > 0) {
        original = podaci;
        this->pod = podaci;
        this->ma = indikatori.first;
        this->ema = indikatori.second;
        this->n = n;
        size((pod.size()>25?pod.size():25) * 36, visina);
        auto maxEl = std::max_element(pod.begin(), pod.end(),
            [](const Sveca& a, const Sveca& b)
            {
                return a.high < b.high;
            });
        maximum = maxEl->high;
        srediNiz();
        redraw();
    }
}
void Grafik::emaDraw() {
    std::vector<double> emaV;
    emaV.push_back(original[0].close);
    for (int i = 1; i < original.size(); i++) {
        double s = original[i].close * (2 / ((double)n + 1)) + emaV[i - 1] * (1 - 2 / ((double)n + 1));
        emaV.push_back(s);
    }
    fl_line_style(FL_SOLID);
    fl_color(0);
    for (int i = 0; i < emaV.size() - 1; i++) {
        fl_line(i * sirina + 12 + x(), visina - konvert(emaV[i]) + y(), (i + 1) * sirina + 12 + x(), visina - konvert(emaV[i + 1]) + y());
    }
}
void Grafik::maDraw() {
    std::vector<double> maV;
    for (int i = 0; i < n; i++)
        maV.push_back(konvert(original[i].close));
    for (int i = n; i < original.size(); i++) {
        double s = 0;
        for (int j = 0; j < n; j++) {
            s += original[i - j - 1].close;
        }
        maV.push_back(konvert(s / (double)n));
    }
    fl_line_style(FL_SOLID);
    fl_color(9);
    for (int i = 0; i < maV.size() - 1; i++) {
        fl_line(i * sirina + 12 + x(), visina - maV[i] + y(), (i + 1) * sirina + 12 + x(), visina - maV[i + 1] + y());
    }
}
void Grafik::draw() {
    Fl_Group::draw();
    fl_color(48);
    fl_rectf(x(), y(), 950, 630);
    fl_rectf(x(), y(), w(), h());
    fl_line_style(FL_DASH);
    //pravis grid
    //horizontalne linije

    fl_color(50);
    int korak = (visina - 5) / 20;
    int prva = visina - konvert(minimum) + y() - korak;

    for (int i = 0; i < 20; i++) {
        fl_line(0 + x(), prva + y(), w() + x() - 45, prva + y());
        prva = prva - korak;
    }
    //vertikalne linije
    prva = 35 * 7;
    for (int i = 0; i < pod.size() / 7; i++) {
        fl_line(prva * (i + 1) + x(), y(), prva * (i + 1) + x(), visina + y());
    }

    fl_line_style(FL_SOLID);
    for (int i = 0; i < pod.size(); i++) {
        if (pod[i].close > pod[i].open) fl_color(FL_GREEN);
        else fl_color(FL_RED);
        fl_line(i * sirina + 12 + x(), visina - pod[i].low + y(), i * sirina + 12 + x(), visina - pod[i].high + y());
        if (pod[i].open < pod[i].close)
            fl_rectf(i * sirina + x(), visina - pod[i].close + y(), 27, pod[i].close - pod[i].open + 2);
        else
            fl_rectf(i * sirina + x(), visina - pod[i].open + y(), 27, pod[i].open - pod[i].close + 2);
    }

    if (ma && n < original.size() && n > 0) {
        maDraw();
    }
    if (ema && n < original.size() && n > 0) {
        emaDraw();
    }

    //pravis vodilju zadnje
    fl_font(FL_TIMES, 20);
    std::string cena = "";
    fl_color(4);
    fl_line(x(), visina - pod[pod.size() - 1].close + y(), w() + x() - 30, visina - pod[pod.size() - 1].close + y());
    cena = std::to_string(dekonvert(pod[pod.size() - 1].close));
    fl_draw(cena.c_str(), w() + x() - 140, 30 + y());
    //vodilju minimalne
    fl_color(88);
    fl_line(x(), visina - (konvert(minimum)) + y(), w() + x() - 30, visina - (konvert(minimum)) + y());
    cena = std::to_string(minimum);
    fl_draw(cena.c_str(), w() + x() - 250, 30 + y());
    //vodilju najvece
    fl_color(63);
    fl_line(x(), visina - (konvert(maximum)) + y(), w() + x() - 30, visina - (konvert(maximum)) + y());
    cena = std::to_string(maximum);
    fl_draw(cena.c_str(), w() + x() - 360, 30 + y());


}