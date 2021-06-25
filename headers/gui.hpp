#ifndef GUI_KLASA
#define GUI_KLASA


#include "engine.hpp"
#include "grafik.hpp"
#include "akcijeGui.hpp"
#include "transakcijeGui.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Int_Input.H>

#include<string>
class Gui : public Engine {

    private:
        //loginEkran
        Fl_Input* inpLog;
        Fl_Secret_Input* scrInpLog;
        Fl_Window* winLog;
        static void loginCallbackLog(Fl_Widget*, void*);
        static void RegcallbackLog(Fl_Widget*, void*);
        //registracijaEkran
        Fl_Input* usrInpReg;
        Fl_Secret_Input* passInpReg;
        Fl_Secret_Input* passInp2Reg;
        Fl_Int_Input* sumaReg;
        Fl_Window* winReg;
        static void callbackReg(Fl_Widget*, void*);
        //GlavniEkran
        Fl_Double_Window* win;
        Fl_Scroll* skrol;
        Grafik* chart;
        Fl_Int_Input* n;
        Fl_Double_Window* winAkcije;
        Fl_Int_Input* idAkc;
        Fl_Int_Input* kolAkc;
        Fl_Input* oznAkc;
        std::vector<Fl_Box*> box_labele;
        std::vector<std::string> labele;
        std::pair<bool, bool> indikatori;
        std::vector<Fl_Int_Input*> period[2];
        Fl_Input* simbolLabela;
        void init_labele();
        void azuriraj_podatke(std::string, tm, tm);
        void azuriraj_podatke(std::string, std::string, std::string);
        void azuriraj_labele();
        void praviKupiProdajCallback(bool);
        static void akcijeCallback(Fl_Widget*, void*);
        static void prikaziCallback(Fl_Widget*, void*);
        static void trenPrikaziCallback(Fl_Widget*, void*);
        static void windowCallback(Fl_Widget*, void*);
        static void maCallback(Fl_Widget*, void*);
        static void emaCallback(Fl_Widget*, void*);
        static void kupiCallback(Fl_Widget*, void*);
        static void prodajCallback(Fl_Widget*, void*);
        static void transakcijeCallback(Fl_Widget*, void*);
        std::vector<int> datumkonv(std::vector<Fl_Int_Input*>);



    void login();
    void registracija();
    void glavni_prozor();
    void transakcije();
    void akcije();
    void prikaziAkcije();
};
#endif