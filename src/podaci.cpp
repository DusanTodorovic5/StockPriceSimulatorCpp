#include "podaci.hpp"
Podaci::Podaci(){
    
}
Podaci::Podaci(std::string valuta,std::string simbol,std::string exchangeName,std::string vremenskaZona,std::vector<Sveca> niz){
        this->valuta = valuta;
        this->simbol = simbol;
        this->exchangeName = exchangeName;
        this->vremenskaZona = vremenskaZona;
        this->niz = niz;
}
std::ostream& operator<<(std::ostream& os, const Podaci& pod){
    os << "Valuta : " << pod.valuta << std::endl; 
    os << "Simbol : " << pod.simbol << std::endl; 
    os << "Exchange Name : " << pod.exchangeName << std::endl; 
    os << "Vremenska Zona : " << pod.vremenskaZona << std::endl;
    for (int i=0;i<pod.niz.size();i++){
        os << pod.niz[i];
    }
    return os;
}
std::vector<Sveca> Podaci::vrati_svece(){
    return niz;
}
std::string Podaci::vrati_valutu() const{
    return this->valuta;
}
std::string Podaci::vrati_simbol() const{
    return this->simbol;
}
std::string Podaci::vrati_exchangeName() const{
    return this->exchangeName;
}
std::string Podaci::vrati_vremenskaZona() const{
    return this->vremenskaZona;
}
int Podaci::vrati_velicinu() const{
    return niz.size();
}
Sveca Podaci::operator[](int i){
    return niz[i];
}
std::vector<double> Podaci::vrati_Ema(int n){
    std::vector<double> emaV;
    emaV.push_back(niz[0].close);
    for (int i = 1; i < niz.size(); i++) {
        double s = niz[i].close * (2 / ((double)n + 1)) + emaV[i - 1] * (1 - 2 / ((double)n + 1));
        emaV.push_back(s);
    }
    return emaV;
}
std::vector<double> Podaci::vrati_Ma(int n){
    std::vector<double> maV;
    for (int i = 0; i < n; i++)
        maV.push_back(niz[i].close);
    for (int i = n; i < niz.size(); i++) {
        double s = 0;
        for (int j = 0; j < n; j++) {
            s += niz[i - j - 1].close;
        }
        maV.push_back(s/(double)n);
    }
    return maV;
}