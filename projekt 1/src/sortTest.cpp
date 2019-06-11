#include "sortTest.hpp"
#include "heapsort.hpp"
#include "quicksort.hpp"
#include "merge.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

void SortTest(funcja Sortuj,int ltablic,int rozmiar, double  procentPosortowany, bool rosnaco)  //  funkcja do testowania
{
    double procent=procentPosortowany/100;
    std::cout<<" w "<<procent*100<<"% posortowany"<<std::endl<<"dla rozmiaru tablicy: "<<rozmiar<<std::endl;
    bool nsorted=0;
    std::vector<double>wektorczasow;
    int * tab=new int[rozmiar];
    
    for(int a=0;a<ltablic;a++)
    { 
        std::random_device rd;
        std::uniform_int_distribution<int>distpre (0,100000); 
        std::uniform_int_distribution<int>dist (100000,10000000); 
        for(int i=0; i<=static_cast<int>((rozmiar-1)*procent);i++)
        {
            tab[i]=distpre(rd);
        }
        for(int i=static_cast<int>((rozmiar-1)*procent)+1; i<rozmiar;i++)
        {
            tab[i]=dist(rd);
        }
        if(rosnaco==1)
        {
            quickSort(tab,0,static_cast<int>((rozmiar-1)*procent));
        }
        else
        {
            std::sort(tab,tab+rozmiar,std::greater<int>());
        }

        auto start = std::chrono::high_resolution_clock::now();

        Sortuj(tab,0,rozmiar-1);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end-start;
        wektorczasow.emplace_back(elapsed.count());

        for(int i=0; i<rozmiar-1;i++)   //  sprawdzenie czy tablica jest posortowana
        {
            if (tab[i]>tab[i+1]) nsorted=1;
        } 
    }
    auto max_time =std::max_element(wektorczasow.begin(),wektorczasow.end());
    double suma=std::accumulate(wektorczasow.begin(),wektorczasow.end(),0.0);   //podsumowanie czasów
    std::cout<<"sredni czas: "<<suma/ltablic<<std::endl;    //  średnia
    std::cout<<"maksymalny czas: "<<*max_time<<std::endl;
    if(nsorted)
    {   
        std::cout<<std::endl<<"NIE POSORTOWANE\n";
        
        for(int i=0; i<rozmiar;i++)
        {
            std::cout<<tab[i]<< " ";
        }
    }
    delete[] tab;
}