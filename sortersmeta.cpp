#include "sortersMETA.h"

sortersMETA::sortersMETA() {};
char sortersMETA::dataType;
bool sortersMETA::ascending;
int sortersMETA::currentStringIndex;
int sortersMETA::radixSortIndex;
int sortersMETA::maxFloatFraction;
int sortersMETA::maxFloatWhole;
int sortersMETA::ARRAYSIZE;
int sortersMETA::STRINGMAX;
bool sortersMETA::sorts[5] = { false, false, false, false, false };
 // need a class for sorter META data