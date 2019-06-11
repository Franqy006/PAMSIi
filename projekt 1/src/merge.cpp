#include"merge.hpp"
#include<iostream>
#include <cmath>

void merge(int tab[],  int left, int right,  int middle)    //funkcja scalająca
{
    int * kopia=new int[right-left+1];
    int l=0;
    for(int i=left;i<=right;i++)
    {
        kopia[l]=tab[i];
        l++;
    }

    int i=0;
    int j=middle-left+1;
    
    for(int l2=left;l2<=right;l2++)
    {
        if(i<=middle-left && j<=right-left)
        {
            if(kopia[i]<kopia[j])
            {
                tab[l2]=kopia[i++];
            }
            else
            {
                tab[l2]=kopia[j++]; 
            }
        }
        else if(i>middle-left)  //koniec pierwszej części
        {
        tab[l2]=kopia[j++];
        }
        else if(j>right-middle) //koniec drugieej części
        {
            tab[l2]=kopia[i++];
        }
    } 
    delete[] kopia;
}

void mergeSort(int tab[],int lewy, int prawy)   // właściwa funkcja sortująca
{
    if(lewy!=prawy) 
    {
        int middle=(lewy+prawy)/2;
        mergeSort(tab, lewy, middle);
        mergeSort(tab,middle+1,prawy);
        merge(tab,lewy,prawy,middle); 
    }
    else
    {
       return;
    }
} 