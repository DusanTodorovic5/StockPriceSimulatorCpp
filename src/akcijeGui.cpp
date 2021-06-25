#include "akcijeGui.hpp"
AkcijeGui::AkcijeGui(int id) {
    idKor = id;
    sumaNovca = SQL::novac(id);
    akcija = SQL::akcije(id);
}
void AkcijeGui::azurirajTrenutne() {
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
}
mapaTabele AkcijeGui::init_tabela() {
    azurirajTrenutne();
    mapaTabele mt;
    for (auto const& x : akcija) {
        tabelaStruktura ts;
        ts.akcija = x;
        ts.trenutna = std::to_string(mapa[x.simbol]);
        ts.dodaj();
        std::pair<std::string, tabelaStruktura> par;
        par.first = std::to_string(x.idAkc);
        par.second = ts;
        mt.insert(par);
    }
    novacLabelaString = "Novac : " + std::to_string(sumaNovca);
    return mt;
}
const char* AkcijeGui::vrati_novac() {
    return novacLabelaString.c_str();
}