#include "parser.hpp"
//uncomment to run on windows
//#define timegm _mkgmtime
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string Parser::curlUpdate(std::string link){
    std::cout<<"  " << link << std::endl;
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}
std::vector<std::string> Parser::podeli(std::string s) {
    std::string delimiter = ",";
    std::vector<std::string> vek;
    size_t pos = 0;
    std::string deo;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        deo = s.substr(0, pos);
        vek.push_back(deo);
        s.erase(0, pos + delimiter.length());
    }
    vek.push_back(s);
    return vek;
}
Podaci Parser::parser(std::string readBuffer){
    std::vector<Sveca> niz;
    std::string valuta = " ";
    std::string simbol = " ";
    std::string exchangeName = " ";
    std::string vremenskaZona = " ";
    
    std::regex regexp1("\"currency\":\"([A-z]+)\"");
    std::smatch m; 
    std::regex_search(readBuffer, m, regexp1);
    valuta = m.str(1);

    std::regex regexp2("\"symbol\":\"([A-z]+)\"");
    std::regex_search(readBuffer, m, regexp2);
    simbol = m.str(1);

    std::regex regexp3("\"exchangeName\":\"([A-z]+)\"");
    std::regex_search(readBuffer, m, regexp3);
    exchangeName = m.str(1);

    std::regex regexp4("\"timezone\":\"([A-z]+)\"");
    std::regex_search(readBuffer, m, regexp4);
    vremenskaZona = m.str(1);

    std::regex regexp5("\"timestamp\":\\[([0-9,]+)\\]");
    std::regex_search(readBuffer, m, regexp5);
    std::vector<std::string> tm = podeli(m.str(1));

    std::regex regexp6("\"close\":\\[([0-9,.nul]+)\\]");
    std::regex_search(readBuffer, m, regexp6);
    std::vector<std::string> cl = podeli(m.str(1)); 

    std::regex regexp7("\"open\":\\[([0-9,.nul]+)\\]");
    std::regex_search(readBuffer, m, regexp7);
    std::vector<std::string> op = podeli(m.str(1)); 

    std::regex regexp8("\"high\":\\[([0-9,.nul]+)\\]");
    std::regex_search(readBuffer, m, regexp8);
    std::vector<std::string> hi = podeli(m.str(1));

    std::regex regexp9("\"low\":\\[([0-9,.nul]+)\\]");
    std::regex_search(readBuffer, m, regexp9);
    std::vector<std::string> lo = podeli(m.str(1));
    if (tm[0] != "")
    for (int i = 0; i < tm.size(); i++) {
        if (cl[i] == "null" || op[i] == "null" || hi[i] == "null" || lo[i] == "null")
            continue;
        Sveca sv;
        sv.timestamp = std::stod(tm[i]);
        sv.open = std::stod(op[i]);
        sv.close = std::stod(cl[i]);
        sv.high = std::stod(hi[i]);
        sv.low = std::stod(lo[i]);
        niz.push_back(sv);
    }
    

    return Podaci(valuta,simbol,exchangeName,vremenskaZona,niz);
}
Podaci Parser::operator()(std::string simbol,std::string t1,std::string t2){
    std::string link;
    link = "https://query1.finance.yahoo.com/v8/finance/chart/" +
    simbol + "?period1=" + t2 + "&period2=" + t1 + "&interval=1h";
    return parser(curlUpdate(link));
}
Podaci Parser::operator()(std::string simbol, tm t1, tm t2){
    time_t t1U = timegm(&t1);
    time_t t2U = timegm(&t2);
    std::string link;
    link = "https://query1.finance.yahoo.com/v8/finance/chart/" +
    simbol + "?period1=" + std::to_string(t2U) + "&period2=" + std::to_string(t1U) + "&interval=1h";
    return parser(curlUpdate(link));
}