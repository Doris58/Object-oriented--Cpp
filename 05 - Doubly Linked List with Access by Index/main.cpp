#include "list.h"

#include <iostream>

template <typename T>
void printer(List<T> const & L)
{
    for(std::size_t i = 0; i < L.size(); i++)
    {
        L.setPosition(i);
        std::cout << L.current() << " " ;
    }
    std::cout << std::endl;
}

template <typename T>
void get_size_info(List<T> const & L)
{
   std::cout << "List size: " << L.size() << " Empty: " << L.empty() << std::endl; 
}

int main()
{
// My tests
    List<int> L;

    L.insert(0, 5);
    L.clear();
    get_size_info(L);

    L.insert(0, 5);
    L.insert(0, 7);
    L.clear();
    get_size_info(L);

    L.insert(0, 5);
    L.insert(0, 7);
    L.insert(1, 6);
    L.insert(3, 1);
    printer(L);
    get_size_info(L);

    L.push_back(3);
    L.sort();
    printer(L);

    L.remove(2);
    L.insert(2,1);
    printer(L);

    L.sort();
    printer(L);

    L.remove(0);
    L.remove(2);
    printer(L);

    L.remove(2);
    get_size_info(L);
    L.remove(0);
    L.remove(0);
    get_size_info(L);

    return 0;
}
