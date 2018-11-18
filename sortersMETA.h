#pragma once
class sortersMETA {
public:
	sortersMETA();
	static char dataType;
	static bool ascending;
	static int currentStringIndex;
	static bool sorts[5];
	static int radixSortIndex;
	static const int ARRAYSIZE = 7;
	static const int STRINGMAX = 6;
}; // need a class for sorter META data