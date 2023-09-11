#ifndef LIST_H
#define LIST_H

#include <cstddef>  // std::size_t
#include <stdexcept>

#include <cassert>
#include <iostream>

template <typename> class ListTest;

// Parametrizirana struktura koja predstavlja èvor u listi.
// Sadrži vrijednost (value) i pokazivaèe na prethodni i sljedeæi
// element u listi.
template <typename T>
struct Node
{
    T value{};

    Node * previous = nullptr;
    Node * next = nullptr;
};

/**
 * Dvostruko povezana lista s elementima indeksiranim cjelobrojnim indeksima.
 * Indeksi elemenata poèinju s nulom. Sve metode koje uzimaju indeks provjeravaju
 * da li je unutar granica i u suprotnom izbacuju std::runtime_error.
**/
template <typename T>
class List
{
    friend class ListTest<T>;

    public:
        // Konstruktor
        List() :  mSize(0), mPositionIdx(0), mStart(nullptr), mPosition(nullptr) {}
        
        // Destruktor
        ~List() { clear(); }
        
        // Obriši (dealociraj) sve elemente liste.
        void clear();
        
        // Da li je lista prazna?
        bool empty() const;
        
        // Broj elemenata u listi.
        std::size_t size() const;
        
        // Ubaci element "t" na poziciju "i" u listi. Pozicija "i" mora biti važeæa
        // i tada se element ubacuje na to mjesto, a prijašnji "i"-ti element postaje
        // "i"+1-vi element. Pozicija "i" može biti jednaka size()  i tada se element ubacuje na kraj liste.
        // Metoda mora ispravno ubacivati i u praznu listu. Metoda pozicionira listu na novom
        // i-tom elementu (pozivom metode setPosition()).
        // Novi element se alocira dinamièki pomoæu new operatora.
        void insert(std::size_t i, T const & t);
        
        // Izbaciti element iz liste i dealocirati ga pomoæu delete. Trenutna pozicija
        // nakon izbacivanja pokazuje na prethodni element ako postoji; kada se izbacuje prvi element
        // onda pokazuje na novi prvi element ili lista ostaje prazna.
        void remove(std::size_t i);
        
        // Postaviti trenutnu poziciju na i-to mjesto. Dozvoljeni "i" ide od 0 do 
        // size()-1. Inaèe izbaci izuzetak std::runtime_error. 
        void setPosition(std::size_t i) const;
        
        // Vrati selektirani element. Konstantna verzija.
        T const & current() const; 
        
        // Vrati selektirani element. Nekonstantna verzija. 
        T & current(); 
        
        // Dodaje element na kraj liste. Listu pozicionira na novom elementu. 
        void push_back(T const & t); 
        
        // Sortira listu pomoæu operatora <. Implementirati "insertion sort". 
        void sort(); 

    private:
        std::size_t mSize;

        mutable std::size_t mPositionIdx;

        Node<T> * mStart;

        mutable Node<T> * mPosition;

        // Vrati pokazivaè na selektirani node. 
        Node<T> * currentNode() { return mPosition; }
};

template <typename T>
bool List<T>::empty() const
{ 
  // Implementacija
    if(mSize) return 0;  // alternatively: if(size()) return 0;  /  if(mStart != nullptr)
    
    return 1;
}

template <typename T>
std::size_t List<T>::size() const 
{ 
    return mSize; 
}

template <typename T>
T const & List<T>::current() const 
{
 // Implementacija
    if(!empty())   // empty --> there are no nodes with values, mPosition = nullptr
    {
        return currentNode()->value;  // return mPosition->value;
    }
}

template <typename T>
T & List<T>::current() 
{
 // Implementacija
    if(!empty())   // empty --> there are no nodes with values, mPosition = nullptr
    {
        return currentNode()->value;  // return mPosition->value;
    }
}

template <typename T>
void List<T>::setPosition(std::size_t i) const
{
 // Implementacija  
    if(!(i >= 0 && i <= mSize - 1))   // alternatively: assert()
        throw std::runtime_error("Trazeni indeks nije u dozvoljenom rasponu.");  // also throws an error when the list is empty

    Node<T>* temp = mStart;

    for(std::size_t j = 0; j < i; j++)
        temp = temp->next;

    mPosition = temp;
    mPositionIdx = i;
}

template <typename T>
void List<T>::insert(std::size_t i, T const & t)
{
 // Implementacija
    if(!(i >= 0 && i <= mSize)) 
        throw std::runtime_error("Trazeni indeks nije u dozvoljenom rasponu.");

    Node<T>* novi = new Node<T>;
    novi->value = t;

    if(i == mSize)  novi->next = nullptr;
    else   // else there is an element in the list on the position after
    {
        setPosition(i);
        mPosition->previous = novi;
        novi->next = mPosition;
    }

    if(i == 0)
    {
        mStart = novi;
        novi->previous = nullptr;
    }
    else  // else there is an element in the list on the position before
    {
        setPosition(i - 1);
        mPosition->next = novi;
        novi->previous = mPosition;
    }

    mSize++;                // insertion affects, so modifies the size
    setPosition(i);
}

template <typename T>
void List<T>::remove(std::size_t i)
{
 // Implementacija  
 if(!empty())    // empty --> mSize - 1 = 0 - 1 = -1  (!) - not necessary
 {
    if(!(i >= 0 && i <= mSize - 1)) 
        throw std::runtime_error("Trazeni indeks nije u dozvoljenom rasponu.");  // also throws an error when the list is empty (!)

    setPosition(i);
    Node<T>* temp = mPosition;

    if(i != mSize - 1)   // there is an element in the list after the observed one
        mPosition->next->previous = mPosition->previous;

    if(i != 0)    // there is an element in the list before the observed one
    {
        mPosition->previous->next = mPosition->next;
        setPosition(i - 1);
    }
    else if(mSize != 1)   // the observed element is the first one, but not the only one
    {
        mStart = mStart->next;
        setPosition(0);
    }
    else  { mStart = nullptr; mPosition = nullptr; mPositionIdx = 0; }  // the element was the only one

    delete temp;
    mSize--;         // removing affects, so modifies the size
 }
}

template <typename T>
void List<T>::clear()
{
 // Implementacija
    if(mSize > 0)    // alt. !empty()
    {
        Node<T>* temp = mStart;
        if(mSize > 1)  // mStart is the previous element for an element in the list, or mStart->mext != nullptr
        {
            for(temp = mStart->next; temp->next != nullptr; temp = temp->next)
               delete temp->previous;

            delete temp->previous;
        }
        delete temp;

        mSize = 0;           // affecting the mSize
        mStart = nullptr;
        mPosition = nullptr;    // list is empty --> mPosition = nullptr
        mPositionIdx = 0;
    }
}

template <typename T>
void List<T>::push_back(T const & t) 
{
 // Implementacija
    insert(mSize, t);
}

template <typename T>
void List<T>::sort() 
{
 // Implementacija
    Node<T>* pomm;
    for(Node<T>* pom = mStart; pom != nullptr; pom = pom->next)    // doesn't sort the empty list
    {
        T d = pom->value;
        for(pomm = pom; pomm != mStart && pomm->previous->value > d; pomm = pomm->previous)
            pomm->value = pomm->previous->value;

        pomm->value = d;
    }
}

#endif /* LIST_H */
