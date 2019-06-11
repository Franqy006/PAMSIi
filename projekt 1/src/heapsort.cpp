#include "heapsort.hpp"
#include <iostream>
#include <algorithm>

void stosuj(int tab[], int left,int right)  //funkcja poprawnie uklada drzewo od zadanego miejsca w dol
{
    int maxindex=left;
    int l=2*left+1;
    int r=2*left+2;
    
    if(l<=right && tab[l]>tab[left])
    {
        maxindex=l;
    }

    if(r<=right && tab[r]>tab[left]&&tab[r]>tab[l])
    {
        maxindex=r;
    }
   
    if(maxindex!=left)
    {
        std::swap(tab[left],tab[maxindex]);
        stosuj(tab, maxindex,right);
    }

}

void buduj(int tab[], int left, int right)  // funkcja buduje drzewo z zadanej tabeli
{
    int n =right-left+1;
    for (int i =n / 2 - 1; i >= 0; i--) 
    {
        stosuj(tab, left+i, right); 
    }
}

void sortHeap(int tab[], int left, int right)   //  funkcja z ułożonego drzewa odczytuje wynik sortowania
{ 
    for (int i=right; i>left; i--) 
    { 
        std::swap(tab[left], tab[i]); // zamiana korzenia z ostatnim liściem
        
        stosuj(tab, left ,i-1); // ułożenie drzewa po zmianie, pomniejszonego o 1 posortowany element
            
    } 
}

void heapSort(int tab[], int left, int right) // właściwe sortowanie, buduje stos z elementów tablicy i je odczytuje
{
    buduj(tab,left,right);

    sortHeap(tab,left,right);
}