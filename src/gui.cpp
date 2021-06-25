#include "gui.hpp"
void Gui::login() {
    winLog = new Fl_Window(400, 400, "Ulogujte se");
    winLog->begin();
    inpLog = new Fl_Input(150, 50, 100, 40, "");
    scrInpLog = new Fl_Secret_Input(150, 130, 100, 40, "");
    Fl_Box ukuc_usr(0, 20, 400, 30, "Unesi korisnicko ime");
    Fl_Box ukuc_pass(0, 100, 400, 30, "Unesi sifru");
    Fl_Button* but = new Fl_Button(150, 180, 100, 40, "Ulogujte se");
    Fl_Box registrac(0, 250, 400, 30, "Ako nemate nalog, napravite novi");
    Fl_Button* butReg = new Fl_Button(150, 280, 100, 40, "Registruj se");
    winLog->end();
    but->callback((Fl_Callback*)loginCallbackLog, this);
    but->box(FL_GTK_UP_BOX);
    butReg->callback((Fl_Callback*)RegcallbackLog, this);
    butReg->box(FL_GTK_UP_BOX);
    winLog->show();
    Fl::run();
    delete inpLog;
    delete scrInpLog;
    delete but;
    delete butReg;
    Fl::delete_widget(winLog);

    if (stanje != Stanje::GLAVNI)
        stanje = Stanje::IZLAZ;
}
void Gui::registracija() {
    winReg = new Fl_Window(400, 400, "Registracija");
    winReg->begin();
    usrInpReg = new Fl_Input(150, 50, 100, 30, "");
    passInpReg = new Fl_Secret_Input(150, 110, 100, 30, "");
    passInp2Reg = new Fl_Secret_Input(150, 170, 100, 30, "");
    sumaReg = new Fl_Int_Input(150, 230, 100, 30, "");
    Fl_Box kor_ime(0, 30, 400, 20, "Unesi korisnicko ime");
    Fl_Box ukuc_pass(0, 90, 400, 20, "Unesi sifru");
    Fl_Box pon_pass(0, 140, 400, 20, "Ponovi sifru");
    Fl_Box ukuc_sumu(0, 210, 400, 20, "Unesi sumu novca");
    Fl_Button but(150, 280, 100, 40, "Registracija");
    but.box(FL_GTK_UP_BOX);
    but.callback((Fl_Callback*)callbackReg, this);
    winReg->end();
    winReg->show();
    Fl::run();
    delete usrInpReg;
    delete passInpReg;
    delete passInp2Reg;
    delete sumaReg;
    Fl::delete_widget(winReg);
}
void Gui::glavni_prozor() {
    init_labele();
    std::string naslov = "Poop Projekat Korisnik : " + this->username;
    win = new Fl_Double_Window(1200, 700, naslov.c_str());
    win->begin();
    win->callback((Fl_Callback*)windowCallback, this);
    skrol = new Fl_Scroll(20, 20, win->w() - 250, win->h() - 40);
        skrol->box(FL_NO_BOX);
        chart = new Grafik(podaci.vrati_svece(), 20, 20, win->w() - 250, win->h() - 70, "");
    skrol->end();
    //pravljenje labela
    for (int i = 0; i < 5; i++) {
        Fl_Box* boxLabela = new Fl_Box(win->w() - 210, 20 + i * 45, 200, 40, labele[i].c_str());
        boxLabela->box(FL_GTK_DOWN_BOX);
        box_labele.push_back(boxLabela);
    }
    //kraj pravljenja labela
    Fl_Button dugmeAkcije(win->w() - 210, 250, 200, 40, "Moje akcije");
    dugmeAkcije.box(FL_GTK_UP_BOX);
    dugmeAkcije.callback((Fl_Callback*)akcijeCallback, this);
    //grupa za upis
    Fl_Group grupa(win->w() - 210, 300, 200, 250);
    grupa.box(FL_DOWN_BOX);
    grupa.begin();
    Fl_Box periodLabela(win->w() - 200, 305, 170, 15, "Period od:");
    //prve input tabele
    Fl_Int_Input* inp = new Fl_Int_Input(win->w() - 200, 320, 25, 20);
    period[0].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 173, 320, 25, 20);
    period[0].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 145, 320, 25, 20);
    period[0].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 117, 320, 25, 20);
    period[0].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 89, 320, 25, 20);
    period[0].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 61, 320, 39, 20);
    period[0].push_back(inp);
    //druge input tabele
    Fl_Box peridoLabela(win->w() - 200, 345, 170, 15, "Period do:");
    inp = new Fl_Int_Input(win->w() - 200, 360, 25, 20);
    period[1].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 173, 360, 25, 20);
    period[1].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 145, 360, 25, 20);
    period[1].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 117, 360, 25, 20);
    period[1].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 89, 360, 25, 20);
    period[1].push_back(inp);
    inp = new Fl_Int_Input(win->w() - 61, 360, 39, 20);
    period[1].push_back(inp);
    Fl_Box labela(win->w() - 200, 400, 80, 15, "Simbol: ");
    simbolLabela = new Fl_Input(win->w() - 115, 398, 80, 20);
    Fl_Button dugmePrikaz(win->w() - 200, 450, 180, 40, "Prikazi");
    dugmePrikaz.callback((Fl_Callback*)prikaziCallback, this);
    Fl_Button dugmePrikazTren(win->w() - 200, 500, 180, 40, "Prikazi trenutne");
    dugmePrikazTren.callback((Fl_Callback*)trenPrikaziCallback, this);
    grupa.end();
    //kraj grupe za upis
    //Indikatori
    Fl_Box labelaN(win->w() - 200, 565, 90, 15, "N: ");
    n = new Fl_Int_Input(win->w() - 135, 563, 90, 20);
    Fl_Check_Button dugmeEMA(win->w() - 210, 590, 100, 40, "EMA");
    //dugmeEMA.box(FL_GTK_UP_BOX);
    dugmeEMA.callback((Fl_Callback*)emaCallback, this);
    Fl_Check_Button dugmeEM(win->w() - 105, 590, 100, 40, "MA");
    //dugmeEM.box(FL_GTK_UP_BOX);
    dugmeEM.callback((Fl_Callback*)maCallback, this);
    Fl_Button transDugme(win->w() - 210, 640, 200, 40, "Transakcije");
    transDugme.callback((Fl_Callback*)transakcijeCallback, this);
    transDugme.box(FL_GTK_UP_BOX);
    win->end();
    win->show();
    Fl::run();
    delete chart;
    delete skrol;
    for (Fl_Box* f : box_labele) {
        delete f;
    }
    box_labele.clear();
    for (Fl_Int_Input* f : period[0]) {
        delete f;
    }
    period[0].clear();
    for (Fl_Int_Input* f : period[1]) {
        delete f;
    }
    period[1].clear();
    delete simbolLabela;
    delete n;
    Fl::delete_widget(win);
}
void Gui::transakcije() {
    Fl_Double_Window winTrans(530, 400, "Moje Transakcije");
    TransakcijeGui tr(SQL::transakcije(this->id), 10, 10, 520, 390);
    winTrans.end();
    winTrans.show();
    while (winTrans.shown()) Fl::wait();
}
void Gui::akcije() {
    winAkcije = new Fl_Double_Window(900, 400, "Moje Akcije");
    AkcijeGui akcgui(id);
    Tabela tabela(akcgui.init_tabela(), 10, 10, 720, 390);
    Fl_Box novacLabela(740, 10, 155, 40, akcgui.vrati_novac());
    novacLabela.box(FL_GTK_DOWN_BOX);
    Fl_Box idAkcLab(740, 200, 60, 20, "Id akcije");
    idAkc = new Fl_Int_Input(805, 200, 90, 20);
    Fl_Button dugmeProdaj(740, 230, 155, 40, "Prodaj");
    dugmeProdaj.box(FL_GTK_UP_BOX);
    dugmeProdaj.callback((Fl_Callback*)prodajCallback,this);
    Fl_Box oznAkcLab(760, 280, 60, 20, "Oznaka akcije");
    oznAkc = new Fl_Input(840, 280, 50, 20);
    Fl_Button dugmeKupi(740, 310, 155, 40, "Kupi");
    dugmeKupi.box(FL_GTK_UP_BOX);
    dugmeKupi.callback((Fl_Callback*)kupiCallback, this);
    Fl_Box kolAkcLab(740, 360, 60, 20, "Kolicina");
    kolAkc = new Fl_Int_Input(805, 360, 90, 20);
    winAkcije->end();
    winAkcije->show();
    while (winAkcije->shown()) Fl::wait();
    delete idAkc; idAkc = nullptr;
    delete kolAkc; kolAkc = nullptr;
    delete oznAkc; oznAkc = nullptr;
    Fl::delete_widget(winAkcije);
    init_labele();
    azuriraj_labele();
}
void Gui::prikaziAkcije() {

}

//LOGIN
void Gui::loginCallbackLog(Fl_Widget* w, void* arg) {
    Gui* kl = ((Gui*)arg);
    std::pair<std::string, std::string> usrpass;
    usrpass.first = kl->inpLog->value();
    usrpass.second = kl->scrInpLog->value();
    if (usrpass.first.length() == 0) { fl_alert("UNESI KORISNICKO IME"); return; }
    std::pair<int, std::string> par = SQL::loginPass(usrpass);
    if (par.first == -1) {
        fl_alert(par.second.c_str());
        return;
    }
    kl->winLog->hide();
    kl->stanje = Stanje::GLAVNI;
    kl->id = par.first;
    kl->username = par.second;
    kl->novac = std::to_string(SQL::novac(kl->id));
}
void Gui::RegcallbackLog(Fl_Widget* w, void* arg) {
    ((Gui*)arg)->registracija();
}
//REGISTRACIJA
void Gui::callbackReg(Fl_Widget* w, void* arg) {
    Gui* kl = (Gui*)arg;
    std::string pass = kl->passInpReg->value();
    std::string pass2 = kl->passInp2Reg->value();
    if (pass != pass2) {
        fl_alert("Lozinke se ne poklapaju");
        return;
    }
    if (!kl->sumaReg->value()) {
        fl_alert("Unesite sumu novca!");
        return;
    }
    std::string s = SQL::registracija(kl->usrInpReg->value(), pass, atoi(kl->sumaReg->value()));
    if (s != "") {
        fl_alert(s.c_str());
        return;
    }
    fl_alert("Uspesno registrovan, mozete se ulogovati");
    kl->winReg->hide();
}
//GLAVNI PROZOR
void Gui::init_labele() {
    labele.clear();
    labele.push_back("Novac: " + novac);
    labele.push_back("Valuta: " + podaci.vrati_valutu());
    labele.push_back("Simbol: " + podaci.vrati_simbol());
    labele.push_back("Exchange name: " + podaci.vrati_exchangeName());
    labele.push_back("Vremenska Zona: " + podaci.vrati_vremenskaZona());
}
void Gui::azuriraj_podatke(std::string sim, tm t1, tm t2) {
    Parser parser;
    podaci = parser(sim, t1, t2);
    if (podaci.vrati_velicinu() == 0) {
        fl_alert("GRESKA: Neispravan period ili nepostojeci simbol");
    }
}
void Gui::azuriraj_podatke(std::string sim, std::string t1, std::string t2) {
    Parser parser;
    podaci = parser(sim, t1, t2);
    if (podaci.vrati_velicinu() == 0) {
        fl_alert("GRESKA: Neispravan period ili nepostojeci simbol");
    }
}
void Gui::azuriraj_labele() {
    for (int i = 0; i < 5; i++) {
        box_labele[i]->label(labele[i].c_str());
    }
}
void Gui::praviKupiProdajCallback(bool t) {
    std::string kolicina = (char*)kolAkc->value();
    std::string oznaka = (char*)oznAkc->value();
    std::string idAkcije = (char*)idAkc->value();
    if (kolicina == "") {
        fl_alert("Unesi kolicinu akcije");
        return;
    }
    if (!t && oznaka == "") {
        fl_alert("Unesite oznaku akcije");
        return;
    }
    if (t && idAkcije == "") {
        fl_alert("Unesite id akcije");
        return;
    }
    Parser parser;
    Podaci trenpod;
    std::time_t tsad = std::time(0);
    long tpre = tsad - 345600;
    if (!t) oznaka = (char*)oznAkc->value();
    else oznaka = SQL::simbol(atoi(idAkc->value()));
    std::transform(oznaka.begin(), oznaka.end(), oznaka.begin(), [](unsigned char c) { return std::tolower(c); });
    trenpod = parser(oznaka, std::to_string(tsad), std::to_string(tpre));
    if (trenpod.vrati_velicinu() < 1) {
        fl_alert("Simbol nepostojeci!");
        return;
    }
    double trenAkc = trenpod.vrati_svece()[trenpod.vrati_velicinu() - 1].close;
    if (!t) {
        if (std::stod(novac) < trenAkc * atoi(kolAkc->value())) {
            fl_alert("Nemate dovoljno novca");
            return;
        }
        int sqlp = SQL::kupi(this->id, oznaka, atof(kolAkc->value()), trenAkc);
        if (sqlp != 0) {
            fl_alert("Neuspesna kupovina akcija!");
            return;
        }
        novac = std::to_string(SQL::novac(this->id));
        fl_alert("Kupljeno!");
        winAkcije->hide();
    }
    else {
        int sqlp = SQL::prodaj(this->id, atoi(idAkc->value()), trenAkc, atoi(kolAkc->value()));
        if (sqlp != 0) {
            fl_alert("Neuspesna kupovina akcije");
            return;
        }
        novac = std::to_string(SQL::novac(this->id));
        fl_alert("Prodato!");
        winAkcije->hide();
    }
}
void Gui::akcijeCallback(Fl_Widget* w, void* arg) {
    ((Gui*)arg)->akcije();
}
void Gui::prikaziCallback(Fl_Widget* w, void* arg) {
    Gui* kl = ((Gui*)arg);
    Datum d(kl->datumkonv(kl->period[0]), kl->datumkonv(kl->period[1]));
    std::pair<std::string, std::string> par = d.ispravan();
    if (par.first != "0" || par.second != "0") {
        if (par.first != "0")
            fl_alert(par.first.c_str());
        if (par.second != "0")
            fl_alert(par.second.c_str());
        return;
    }
    tm t1 = d.vrati_od();
    tm t2 = d.vrati_do();
    std::string simbol = (char*)(kl->simbolLabela->value());
    kl->azuriraj_podatke(simbol, t2, t1);
    kl->init_labele();
    kl->azuriraj_labele();
    kl->chart->value(kl->podaci.vrati_svece(), kl->indikatori);
    kl->skrol->size(kl->win->w() - 250, kl->win->h() - 40);
}
void Gui::trenPrikaziCallback(Fl_Widget* w, void* arg) {
    Gui* kl = ((Gui*)arg);
    std::time_t t1 = std::time(0);
    long t2 = t1 - 445600;
    std::string simbol = (char*)(kl->simbolLabela->value());
    kl->azuriraj_podatke(simbol, std::to_string(t1), std::to_string(t2));
    kl->init_labele();
    kl->azuriraj_labele();
    kl->skrol->size(kl->win->w() - 250, kl->win->h() - 40);
    kl->skrol->redraw();
    kl->chart->value(kl->podaci.vrati_svece(), kl->indikatori);
}
void Gui::windowCallback(Fl_Widget* w, void* arg) {
    Gui* kl = ((Gui*)arg);
    int odgovor = fl_choice("Da li zelite da izadjete?", "Izloguj me", "Da", "Ne");
    if (odgovor == 0) {
        kl->stanje = Stanje::LOGIN;
        kl->win->hide();
    }
    else if (odgovor == 1) {
        kl->stanje = Stanje::IZLAZ;
        kl->win->hide();
    }
}
void Gui::maCallback(Fl_Widget* w, void* arg) {
    Gui* kl = ((Gui*)arg);
    kl->indikatori.first = !kl->indikatori.first;
    kl->skrol->size(kl->win->w() - 250, kl->win->h() - 40);
    kl->skrol->redraw();
    kl->chart->value(kl->podaci.vrati_svece(), kl->indikatori, atoi(kl->n->value()));
}
void Gui::emaCallback(Fl_Widget* w, void* arg) {
    Gui* kl = (Gui*)arg;
    kl->indikatori.second = !kl->indikatori.second;
    kl->skrol->size(kl->win->w() - 250, kl->win->h() - 40);
    kl->skrol->redraw();
    kl->chart->value(kl->podaci.vrati_svece(), kl->indikatori, atoi(kl->n->value()));
}
void Gui::kupiCallback(Fl_Widget* w, void* arg) {
    ((Gui*)arg)->praviKupiProdajCallback(false);
}
void Gui::prodajCallback(Fl_Widget* w, void* arg) {
    ((Gui*)arg)->praviKupiProdajCallback(true);
}
void Gui::transakcijeCallback(Fl_Widget* w, void* arg) {
    ((Gui*)arg)->transakcije();
}
std::vector<int> Gui::datumkonv(std::vector<Fl_Int_Input*> niz) {
    std::vector<int> n;
    n.push_back(std::atoi((char*)niz[0]->value()));
    n.push_back(std::atoi((char*)niz[1]->value()));
    n.push_back(std::atoi((char*)niz[2]->value()));
    n.push_back(std::atoi((char*)niz[3]->value()));
    n.push_back(std::atoi((char*)niz[4]->value()));
    n.push_back(std::atoi((char*)niz[5]->value()));
    return n;
}