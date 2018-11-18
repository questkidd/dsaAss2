#include "sortersMETA.h"

sortersMETA::sortersMETA() {};
char sortersMETA::dataType;
bool sortersMETA::ascending;
int sortersMETA::currentStringIndex;
int sortersMETA::radixSortIndex;
bool sortersMETA::sorts[5] = { false, false, false, false, false };
 // need a class for sorter META data