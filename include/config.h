#ifndef CONFIG_H
#define CONFIG_H



float widthSort = 900;
float heightSort = 600;

float widthSpecs = 900;
float heightSpecs = 20;


float widthWindow = 900;
float heightWindow = heightSort+heightSpecs;

float height_rect=0;
//100000
//radix sort goes in bus error over 100000
float nElements = 10;

float sizeX=widthSort/nElements;
float sizeY=heightSort/nElements;

bool isSorting = false;
bool isSorted = true;




#endif // CONFIG_H