#include "zadanie.hpp"
#include "sortTest.hpp"
#include <vector>
#include <iostream>

void zadanie(funcja Sortuj)
{
    std::vector<double> procenty{0,25,50,75,95,99,99.7};
    std::vector<int> rozmiary{10000,50000,100000,500000,1000000};

    for(double proc:procenty)
    {
        for(int rozmiar:rozmiary)
        {
             SortTest(Sortuj,100,rozmiar,proc,1);
        }
        std::cout<<std::endl;
    }
    std::cout<<"odwrocone: \n";

    for(int rozmiar:rozmiary)
    {
        SortTest(Sortuj,100,rozmiar,0,0);
    }

}