#include <iostream>
#include <algorithm>

#include "sortTest.hpp"
#include "heapsort.hpp"
#include "quicksort.hpp"
#include "merge.hpp"
#include "introsort.hpp"
#include "zadanie.hpp"
int main()
{
  std::cout<<"\nmerge:";
  zadanie(mergeSort);
  std::cout<<"\nintro:";
  zadanie(introSort);
  std::cout<<"\nquick:";
  zadanie(quickSort);
  
     // SortTest(mergeSort,100,10000,0,1);
}