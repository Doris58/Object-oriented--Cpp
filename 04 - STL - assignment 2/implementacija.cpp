#include "deklaracija.h"

// Ubaciti potrebne include datoteke
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

// Zadan je raspon iteratora unutar stringa. Pročitati i vratiti prvu riječ iz stringa.
// Postaviti iterator it na prvu interpunkciju/bjelinu iza pročitane riječi ili na itend
// (end-iterator) ako takve nema.
// Riječi su cjeline međusobno odvojene bjelinama i/ili interpunkcijama: ,.!?:;()
// Bjeline su  \n\t\v.
std::string procitaj_rijec(std::string::const_iterator & it, std::string::const_iterator itend)
{
  // implementacija   
    while(it != itend && (*it == ',' || *it == '.' || *it == '!' || *it == '?' || *it == ':' || *it == ';' 
          || *it == '(' || *it == ')' || *it == '\"' || *it == '\'' || *it =='\n' || *it == '\t' || *it == '\v' || *it == ' ')) 
    {
      it++;
    }

    std::string::const_iterator i = it;

    while(it != itend && *it != ',' && *it != '.' && *it != '!' && *it != '?' && *it != ':' && *it != ';'
          && *it != '(' && *it != ')' && *it != '\"' && *it != '\'' && *it != '\n' && *it != '\t' && *it != '\v' && *it !=' ')
    {
      it++;
    }

    return std::string(i, it);  // [i, it)
}

// Otvoriti datoteku file_name za čitanje, učitati tekst (npr. liniju po liniju)
// i smjestiti riječi u mapu. Riječ je ključ, a vrijednost je broj ponavljanja riječi.
// Riječ se učitava pomoću rutine ucitaj_rijec.
void procitaj_datoteku(std::string file_name, std::map<std::string ,int> & word_list)
{ 
  // implementacija
    std::ifstream in;
    in.open(file_name);
    if(!in) 
      throw std::runtime_error("Ne mogu otvoriti datoteku.");

    std::string r, rijec;
    std::string::const_iterator begin, end;

    while(std::getline(in, r))
    {
      begin = r.begin();
      end = r.end();
        
      while(1)
      {
        rijec = procitaj_rijec(begin, end);

        if(rijec.size() != 0)  // alternativno: if(!rijec.empty())
        {
          auto it = word_list.insert(std::pair<std::string, int>(rijec, 1));

          if(it.second == 0) 
            it.first->second++;
        }
        else 
          break;
      }
    }
}

// Vrati listu riječi koje se najčešće pojavljuju u mapi (std::list) i broj ponavljanja (int).
std::pair<std::list<std::string>, int> naj(std::map<std::string,int> const & word_list)
{
  // implementacija   
    std::list<std::string> l;

    std::map<std::string, int>::const_iterator it = word_list.begin();

    int maxx = it->second;

    for(it = std::next(it); it != word_list.end(); it++)
    {
      if(it->second > maxx) 
        maxx = it->second;
    }
      
    for(it = word_list.begin(); it != word_list.end(); it++)
    {
      if(it->second == maxx) 
        l.push_back(it->first);
    }
       
    return std::pair<std::list<std::string>, int>(l, maxx);
}

// Argument grupe sadrži grupe riječi (ključ je ime grupe, a vrijednosti
// su riječi koje pripadaju grupi).
// Funkcija treba za svaku grupu riječi sumirati broj pojavljivanja svih riječi
// iz grupe u tekstu te vratiti vrijednosti u vektoru. Na i-tom mjestu u povratnom vektoru
// je broj pojavljivanja riječi iz i-te grupe (prema uređaju u multimap varijabli).
// Argument word_list je std::map svih riječi s brojem njihovih pojavljivanja.
std::vector<int>
broj_iz_grupe(std::map<std::string, int> const & word_list,
              std::multimap<std::string, std::string> const & grupe)
{
  // implementacija
    std::vector<int> vec;

    std::multimap<std::string, std::string>::const_iterator mi, mi2;

    std::map<std::string, int>::const_iterator it;

    int br_rijeci = 0;

    for(mi = grupe.begin(); mi != grupe.end(); mi = grupe.upper_bound(mi->first)) 
    {
      br_rijeci = 0;

      for(mi2 = grupe.equal_range(mi->first).first; mi2 != grupe.equal_range(mi->first).second; mi2++) 
      {
        it = word_list.find(mi2->second);

        if(it != word_list.end()) 
              br_rijeci += it->second;
      }
      
      vec.push_back(br_rijeci);
    }

    return vec;
}
