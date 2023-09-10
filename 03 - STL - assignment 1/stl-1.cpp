#include "stl-1.h"

// Ubaciti potrebne include datoteke
#include<iostream>
#include<fstream>   // ofstream, ifstream, fstream classes
#include<stdexcept> // runtime_error
#include<string>
#include<iterator>  // back_inserter - return type: back_insert_iterator
#include<vector>
#include<list>
#include<algorithm>  // replace, find
#include<ios>        // showpos, scientific
#include<cmath>
#include<cassert>

std::vector<int> zadatak1(std::string const & file_name)
{
  // Implementacija zadatka 1
    std::ifstream in(file_name);

    if(!in) 
      throw std::runtime_error("Ne mogu otvoriti datoteku.");

    std::istream_iterator<int> isi(in);
    std::istream_iterator<int> isi_end;  // default-constructed --> end-of-stream iterator

    std::vector<int> vec(isi, isi_end);

    std::replace(vec.begin(), vec.end(), 0, 9);

    return vec;
}

void zadatak2(std::string const & file_name)
{
  // Implementacija zadatka 2
    std::ifstream in(file_name);

    if(!in)
      throw std::runtime_error("Ne mogu otvoriti datoteku.");

    std::istream_iterator<float> isi(in);
    std::istream_iterator<float> isi_end;

    std::vector<float> vec;

    copy(isi, isi_end, back_inserter(vec));  // Navodi na copy jer imamo isi, isi_end i back_insert iterator.

    std::ofstream out("3cols.txt");

    if(!out) 
      throw std::runtime_error("Ne mogu otvoriti datoteku.");

    for(int k = 0; k < vec.size(); k++)  
      out << std::showpos << std::scientific << vec[k] << " " << sin(vec[k]) << " " << exp(vec[k]) << std::endl;
}

std::list<int> zadatak3()
{
  // Implementacija zadatka 3
    std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> l2 = l1;

    while(*l1.begin() != 5)
      if(!(std::next_permutation(l1.begin(), l1.end())))
        break;

    while(*l2.begin() != 9)
      if(!(std::next_permutation(l2.begin(), l2.end()))) 
        break;

    auto it3 = std::find(l1.begin(), l1.end(), 3);  // find returns iterator
    auto it4 = std::find(l2.begin(), l2.end(), 4);
    auto it7 = std::find(l2.begin(), l2.end(), 7);

    assert(it3 != l1.end());
    assert(it4 != l2.end());
    assert(it7 != l2.end());

    auto i = l2.begin();
    while(i != it4 && i != it7 && i != l2.end())
      i++;

    if(i == it4)
    {
      // it4++; bez pocetnog 4
      l1.splice(it3, l2, it4, it7); // splice transfers elements from one list to another, before specified position
    }
  
    if(i == it7)
    {
      // it7++; bez pocetnog 7
      l1.splice(it3, l2, it7, it4);
    }

    return l1;
}

