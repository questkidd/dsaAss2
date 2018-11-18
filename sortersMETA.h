#pragma once
//class for storing all META data related to the sorting that has to be carried out
class sortersMETA {
public:
	sortersMETA();
	static char dataType;
	static bool ascending;
	static int currentStringIndex;//current string index being sorted
	static bool sorts[5];
	static int radixSortIndex;
	static int ARRAYSIZE;
	static int STRINGMAX;
	static int maxFloatFraction;//maximum floating point fraction precision that will be sorted. used in radix sort
	static int maxFloatWhole;
};