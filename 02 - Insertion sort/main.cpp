#include "isort.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

/* alternativno:

template <typename Iter>
void print_container(Iter first, Iter last)
{
  for(Iter i = first; i != prev(i); i++)
    cout << *i << ", ";

  cout << *i << endl;
}
*/

template <typename T>
void print_vec(vector<T> const & vec)
{
  for(int i = 0; i < vec.size() - 1; i++)   // alternativno: for range !
    cout << vec[i] << ", ";

  cout << vec[vec.size() - 1] << endl;
}

template <typename T>
void print_list(list<T> const & list)
{
    list<T>::iterator li;    // alternativno: using Iter = list<T>::iterator;

    for(li = list.begin(); li != prev(list.end()); li++)
      cout << *li << ", ";

    cout << *li << endl;
}

int main()
{
  // Testirajte vaše algoritme na vektoru i listi. 
  vector<int> vec1 = {7, 4, 2, 8, 3, 5, 1};
  vector<int> vec2 = vec1, vec3 = vec1;
  
  vector<int>& ref = vec1;
  insertion_sort_index(ref);
  print_vec(vec1);

  insertion_sort(vec2.begin(), vec2.end());
  print_vec(vec2);

  insertion_sort1(vec3.begin(), vec3.end());
  print_vec(vec3);
  

  list<string> lista1 = {"abc", "desk", "deff", "bok", "tuv", "react"};
  list<string> lista2 = lista1;

  // insertion_sort_index nije definiran za std::list !

  insertion_sort(lista1.begin(), lista1.end());
  print_list(lista1);

  insertion_sort1(lista2.begin(), lista2.end());
  print_list(lista2);

  return 0;
}
