#pragma once

typedef void (*funcja)(int*,  int , int  );

void SortTest(funcja Sortuj,int ltablic,int rozmiar, double  procentPosortowany,bool rosnaco);