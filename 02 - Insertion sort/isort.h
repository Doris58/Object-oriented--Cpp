#ifndef _ISORT_H_ 
#define _ISORT_H_ 

#include<iostream>

#include<list>
#include<vector>
#include<string>

#include<algorithm> // rotate, upper_bound
#include<iterator>  // prev, next

// Verzija s indeksima (vector dozvoljava pristup s pomocu indeksa)
template <typename Record>
void insertion_sort_index(std::vector<Record> & vec)
{
   // implementacija 
    if(!vec.empty())
    {
        int i, j;

        for(i = 1; i < vec.size(); i++)
        {
            Record temp = vec[i];

            for(j = i; j > 0 && vec[j - 1] > temp; j--)
                vec[j] = vec[j - 1];

            vec[j] = temp;
        }
    }
}

// Verzija koja uzima iterator range -- koristiti samo std::next i std::prev
template <typename Iter>
void insertion_sort(Iter first, Iter last) 
{
   // implementacija 
    if(!(first == last))
    { 
        Iter it, itt;

        for(it = first; it != last; it = std::next(it))
        {
            auto temp = *it;

            for(itt = it; itt != first && *std::prev(itt) > temp; itt = std::prev(itt))
                *itt = *std::prev(itt);

            *itt = temp;
        }
    }
}

// Verzija s algoritmima std::rotate i std::upper_bound
template <typename Iter>
void insertion_sort1(Iter first, Iter last) 
{
   // implementacija 
    Iter i, i1;

    for(i = first; i != last; i = std::next(i))
    {
        i1 = std::upper_bound(first, i, *i);

        std::rotate(i1, i, std::next(i));
    }
}

#endif
