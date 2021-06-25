#include "datum.hpp"
std::string Datum::proveraGodine(int dan,int mes,int god){

    if (god < 1970) return "NEISPRAVNA GODINA";
    if (mes < 1 || mes > 12) return "NEISPRAVNI MESEC";
    if (god%4 == 0 && god%100 && mes == 2){
        if (dan > 29 || dan < 1) return "NEISPRAVNI DAN";
    }
    else if (mes == 2){
        if (dan > 28 || dan < 1) return "NEISPRAVNI DAN";
    }
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
        if (dan < 1 || dan > 31) return "NEISPRAVNI DAN";
    }
    else{
        if (dan < 1 || dan > 30) return "NEISPRAVNI DAN";
    }
    return "0";
}
std::string Datum::proveri(std::vector<int> niz){
    int sek = niz[0];
    int min = niz[1];
    int sat = niz[2]; 
    int dan = niz[3];
    int mes = niz[4];
    int god = niz[5];
    if (sek > 59 || sek < 0) return "NEISPRAVNE SEKUNDE";
    if (min > 59 || min < 0) return "NEISPRAVNI MINUTI";
    if (sat > 23 || sat < 0) return "NEISPRAVNI SATI";
    return proveraGodine(dan,mes,god);
}
Datum::Datum(std::vector<int> _od,std::vector<int> _do){
    for (auto const &x : _od){
        std::cout<<x<<" ";
    }
    std::cout<<std::endl;
    for (auto const &x : _do){
        std::cout<<x<<" ";
    }
    std::cout<<std::endl;
    this->_od = _od;
    this->_do = _do;
}
std::pair<std::string,std::string> Datum::ispravan(){
    std::pair<std::string,std::string> par;
    par.first = proveri(_od);
    par.second = proveri(_do);
    if (par.first == "0" && par.second == "0"){
        
        t1.tm_sec = _od[0]; t1.tm_min = _od[1]; 
        t1.tm_hour = _od[2];
        t1.tm_mday = _od[3]; t1.tm_mon = _od[4]-1;
        t1.tm_year = _od[5] - 1900;
        t2.tm_sec = _do[0]; t2.tm_min = _do[1]; 
        t2.tm_hour = _do[2];
        t2.tm_mday = _do[3]; t2.tm_mon = _do[4]-1;
        t2.tm_year = _do[5] - 1900;
    }
    return par;
}
tm Datum::vrati_od(){
    return t1;
}
tm Datum::vrati_do(){
    return t2;
}
long Datum::vrati_trenutno(){
    return std::time(0);
}