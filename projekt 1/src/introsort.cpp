#include "introsort.hpp"
#include<cmath>
#include "quicksort.hpp"
#include "heapsort.hpp"

void introSort(int tab[], int left, int right) // właściwa funkcja sortująca
{
    int maxdepth=2*log2(right-left+1);

    introSorting(tab,left,right,maxdepth);
}

void introSorting(int tab[], int left, int right,int maxdepth)  //  proces sortowania (jeśli rekurencja za głęboko to heapSort, jak nie to quick)
{
    if(right>left)
    {
        if(maxdepth==0)
        {
           int * kopia=new int[right-left+1];
           int l=0;
           for(int i=left;i<=right;i++)
            {
                kopia[l]=tab[i];
                l++;
            }

            l--;

            heapSort(kopia,0,l);

            for(int i=right;i>=left;i--)
            {
                tab[i]=kopia[l];
                l--;
            }
         
            delete [] kopia;
        }
        else
        {
                int i=divide(tab,left,right);
                introSorting(tab,left,i-1,maxdepth-1);
                introSorting(tab,i+1,right,maxdepth-1);
        }
        
    }
    else return;
}