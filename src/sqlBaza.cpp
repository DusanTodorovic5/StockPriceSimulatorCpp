#include "sqlBaza.hpp"
sqlite3 *SQL::db = nullptr;

void SQL::init(){
    if (db != nullptr) return;
    if (sqlite3_open("baza.db", &db) == SQLITE_OK){
        std::cout << "Baza uspesno otvorena" << std::endl;
    }
    else{
        std::cout << "Baza neuspesno otvorena" << std::endl;
    }
}
void SQL::finish(){
    sqlite3_close(db);
}
std::pair<int,std::string> SQL::loginPass(std::pair<std::string,std::string> usr){
    std::pair<int,std::string> par;
    sqlite3_stmt *stmt;
    if (usr.first.length() == 0) {
        par.first = -1;
        par.second = "Unesite korisnicko ime";
        return par;
    }
    std::string str;
    std::string upit = "SELECT password, IdKor from korisnici where username = \'" + usr.first + "\'";
    sqlite3_prepare( db,upit.c_str(), -1, &stmt, NULL );
    sqlite3_step( stmt );
    if (!sqlite3_column_text(stmt,0)) { 
        sqlite3_finalize(stmt);
        par.first = -1;
        par.second = "Netacna lozinka ili korisnicko ime";
        return par;
    }
    str = (char*)sqlite3_column_text(stmt,0);
    par.first = sqlite3_column_int(stmt,1);
    sqlite3_finalize(stmt);
    if (str == usr.second){
        par.second = usr.first;
    }
    else{
        par.first = -1;
        par.second = "Netacna sifra";
    }
    return par;
}
std::string SQL::registracija(std::string usr,std::string pass,int suma){
    sqlite3_stmt *stmt;
    std::string str;
    std::string upit = "SELECT username from korisnici where username = \'" + usr + "\'";
    sqlite3_prepare( db,upit.c_str(), -1, &stmt, NULL );
    sqlite3_step( stmt );
    if (sqlite3_column_text(stmt,0)) { 
        sqlite3_finalize(stmt); 
        return "Korisnicko ime vec postoji";
    }
    sqlite3_finalize(stmt);
    if (suma < 1){
        return "Unesite sumu novca vecu od 0";
    }
    upit = "INSERT INTO korisnici (username, password, suma)"\
            "VALUES('" + usr + "', '" + pass + "', " + std::to_string(suma) + ")";
    int rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK){
        return "Greska pri upisivanju u bazi podataka";
    }
    return "";
}
double SQL::novac(int id){
    sqlite3_stmt *stmt;
    double novac;
    std::string upit = "SELECT suma from korisnici where idKor = " + std::to_string(id);
    sqlite3_prepare( db,upit.c_str(), -1, &stmt, NULL );
    sqlite3_step( stmt );
    novac = sqlite3_column_double(stmt,0);
    sqlite3_finalize(stmt);
    return novac;
}
std::string SQL::simbol(int id){
    sqlite3_stmt *stmt;
    std::string upit = "SELECT simbol from akcije where idAkc = " + std::to_string(id);
    sqlite3_prepare( db,upit.c_str(), -1, &stmt, NULL );
    sqlite3_step( stmt );
    std::string sym = (char*)sqlite3_column_text(stmt,0);
    sqlite3_finalize(stmt);
    return sym;
}
Akcija SQL::akcije(int id){
    sqlite3_stmt *stmt;
    Akcija akcija;
    std::string upit = "select * from akcije where idKor = " + std::to_string(id);
    sqlite3_prepare(db, upit.c_str(), 255, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW){
        int idAkc = sqlite3_column_int(stmt, 0);
        std::string simbolAkc = (char*)sqlite3_column_text(stmt, 2);
        int kolAkc = sqlite3_column_int(stmt, 3);
        double cenaAkc = sqlite3_column_double(stmt, 4);
        Vrednosti vr;
        vr.idAkc = idAkc;
        vr.cena = std::to_string(cenaAkc);
        vr.kolicina = std::to_string(kolAkc);
        vr.simbol = simbolAkc;
        akcija.push_back(vr);
    }
    sqlite3_finalize(stmt);
    return akcija;
}
int SQL::kupi(int id,std::string simbol,int kolicina,double cena){
    double pare = novac(id);
    if (pare < kolicina*cena) return -4;
    std::string upit = "INSERT INTO akcije (idKor, simbol, kolicina, cena)"\
            "VALUES(" + std::to_string(id) + ",\"" + simbol + "\"," + std::to_string(kolicina) + "," + std::to_string(cena) + ")";
    int rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -1; }
    upit = "INSERT INTO transakcije (simbol, kolicina, cena, oper, idKor)"\
            "VALUES(\"" + simbol + "\"," + std::to_string(kolicina) + "," + std::to_string(cena) + ",\"Kupio\"," + std::to_string(id) + ")";
    rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -2; }
    pare = pare-kolicina*cena; 
    upit = "UPDATE korisnici SET Suma = "+ std::to_string(pare)+ " where idKor = " + std::to_string(id);
    rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -3; }
    return 0;
}
int SQL::prodaj(int userid,int idAkc,double cena,int kol){
    sqlite3_stmt *stmt;
    std::string upit = "select idKor, kolicina, simbol from akcije where idAkc = " + std::to_string(idAkc);
    sqlite3_prepare( db,upit.c_str(), -1, &stmt, NULL );
    sqlite3_step( stmt );
    if (!sqlite3_column_int(stmt,0)){
        return -1;
    }
    int trenKol = sqlite3_column_int(stmt,1);
    int provId = sqlite3_column_int(stmt,0);
    std::string simbol = (char*)sqlite3_column_text(stmt,2);
    sqlite3_finalize(stmt);
    if (provId != userid){
        return -2;
    }
    if (trenKol < kol){
        return -3;
    }
    if (trenKol == kol){
        upit = "DELETE FROM akcije where idAkc = " + std::to_string(idAkc);
    }
    else{
        upit = "UPDATE akcije set kolicina = " + std::to_string(trenKol-kol) + " where idAkc = " + std::to_string(idAkc);
    }
    int rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -4; }
    upit = "INSERT INTO transakcije (simbol, kolicina, cena, oper, idKor)"\
            "VALUES(\"" + simbol + "\"," + std::to_string(kol) + "," + std::to_string(cena) + ",\"Prodao\"," + std::to_string(userid) + ")";
    rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -5; }
    double pare = novac(userid);
    pare = pare+kol*cena;
    upit = "UPDATE korisnici SET Suma = "+ std::to_string(pare)+ " where idKor = " + std::to_string(userid);
    rc = sqlite3_exec(db, upit.c_str(), nullptr, 0, nullptr);
    if (rc != SQLITE_OK) { return -6; }
    return 0;
}
std::vector<TransStruktura> SQL::transakcije(int id){
    sqlite3_stmt *stmt;
    Transakcije ts;
    std::string upit = "select idTrans, simbol, kolicina, cena, oper from transakcije where idKor = " + std::to_string(id);
    sqlite3_prepare(db, upit.c_str(), 255, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW){
        int idTr = sqlite3_column_int(stmt, 0);
        std::string simbol = (char*)sqlite3_column_text(stmt, 1);
        int kol = sqlite3_column_int(stmt, 2);
        double cena = sqlite3_column_double(stmt, 3);
        std::string oper = (char*)sqlite3_column_text(stmt, 4);
        TransStruktura t;
        t.id = std::to_string(idTr);
        t.cena = std::to_string(cena);
        t.kolicina = std::to_string(kol);
        t.simbol = simbol;
        t.operacija = oper;
        ts.push_back(t);
    }
    sqlite3_finalize(stmt);
    return ts;
}