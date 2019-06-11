#include "quicksort.hpp"
#include <algorithm>
#include <iostream>
int divide(int tab[],  int left, int right)
{
    int size=right-left+1;
    int mid=right;
    int wsk=left;

    for(int i =left; i<right;i++)
    {

        if(tab[i]<tab[mid])
        {
            std::swap(tab[i], tab[wsk++]);
        }
    }
    std::swap(tab[mid], tab[wsk]);
    return wsk;
}

void quickSort(int tab[], int left, int right)
{
    
    if(right>left)
    {
        int i=divide(tab,left,right);
        quickSort(tab,left,i-1);
        quickSort(tab,i+1,right);
    }
else return;
}