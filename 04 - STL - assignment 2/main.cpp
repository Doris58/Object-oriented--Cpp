#include "deklaracija.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

#include <map>
#include <iterator>
#include <utility>
#include <list>
#include <vector>

using namespace std;

int main()
{
    // Ovdje napisati svoje vlastite testove!

    string a ="fejghrg:vhrjkhb hfvejk?kdwe";

    string::const_iterator it = a.begin();

    cout << procitaj_rijec(it, a.end()) << endl;
    cout << procitaj_rijec(it, a.end()) << endl;
    cout << procitaj_rijec(it, a.end()) << endl;


    map<string, int> m;
    m.insert(pair<string, int>("ana", 4));
    m.insert(pair<string, int>("marko", 7));
    m.insert(pair<string, int>("ivan", 2));
    m.insert(pair<string, int>("ivana", 7));
    m.insert(pair<string, int>("anaa", 3));

    pair<list<string>, int> par = naj(m);

    cout << "Lista: ";
    for(auto i = par.first.begin(); i != par.first.end(); i++)
        cout << *i <<" ";
    cout << endl;

    cout << "Maks. broj: " << par.second << endl;


    multimap<string, string> grupe;
    grupe.insert(pair<string, string>("imena", "ana"));
    grupe.insert(pair<string, string>("imena", "pero"));
    grupe.insert(pair<string, string>("dani", "ponedjeljak"));
    grupe.insert(pair<string, string>("dani", "utorak"));
    grupe.insert(pair<string, string>("dani", "srijeda"));
    grupe.insert(pair<string, string>("brojevi", "dvanaest"));

    map<string, int> tekst;
    tekst.insert(pair<string, int>("ana", 3));
    tekst.insert(pair<string, int>("pero", 7));
    tekst.insert(pair<string, int>("srijeda", 1));
    tekst.insert(pair<string, int>("ponedjeljak", 3));
    tekst.insert(pair<string, int>("anaa", 3));
    tekst.insert(pair<string, int>("dvanaest", 9));

    vector<int> v = broj_iz_grupe(tekst, grupe);

    for(int k = 0; k < v.size(); k++)
        cout << v[k] << endl;


    map<string, int> tekstt;

    procitaj_datoteku("../../test/2.txt", tekstt);

    for(auto t = tekstt.begin(); t != tekstt.end(); t++)
    {
        cout << t->first << " " << t->second << endl;
    }

    return 0;
}
