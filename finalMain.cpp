#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include "sortersMETA.h"
using namespace std;

//generic functions to convert any type to strings
template <class generic> string convertToString(generic input) { return to_string(input); }
template <> string convertToString<string>(string input) { return input; }

//generic template functions to get the values of the digit at a particular position in a number. Only the ones for float and long are used
template <class generic> int getDigitAt(generic input, int digit) { return to_string(input); }
template <> int getDigitAt<float>(float input, int digit) {
	int ivalue = input * pow(10, sortersMETA::maxFloatFraction);
	int factor = pow(10, sortersMETA::maxFloatFraction + sortersMETA::maxFloatWhole - digit - 1);
	ivalue /= factor;
	factor *= 10;
	ivalue %= factor;
	return ivalue;
}
template <> int getDigitAt<long>(long input, int digit) {
	int ivalue = input;
	int factor = pow(10, 10-digit-1);
	ivalue /= factor;
	factor *= 10;
	ivalue %= factor;
	return ivalue;
}

//for the numerics(float and long), executes a counting sort, with a specified digit in the number
template <class generic> void countingSort(generic data[], int length, int digit) {
	int i;
	int largest = 9;//max value of numeric being 9
	generic* sorted = new generic[sortersMETA::ARRAYSIZE];
	int* counter = new int[largest + 1];
	for (i = 0; i <= largest; i++) { counter[i] = 0; }
	for (i = 0; i < length; i++) { counter[getDigitAt(data[i], digit)]++; }
	for (i = 1; i <= largest; i++) { counter[i] += counter[i - 1]; }
	for (i = length - 1; i >= 0; i--) { sorted[--counter[getDigitAt(data[i], digit)]] = data[i]; }
	if (digit == 0 && !sortersMETA::ascending) {
		for (i = 0; i < length; i++) { data[i] = sorted[length - 1 - i]; }
	} else {
		for (i = 0; i < length; i++) { data[i] = sorted[i]; }
	}
	delete[] sorted;//delete to avoid memory leaks
}
//for strings, executes a counting sort, with a specific digit in the string
template <> void countingSort<string>(string data[], int length, int digit) {
	int i;
	int largest = 256;//max value of char being 255
	string* sorted = new string[sortersMETA::ARRAYSIZE];
	int* counter = new int[largest + 1];
	for (i = 0; i <= largest; i++) { counter[i] = 0; }
	for (i = 0; i < length; i++) { counter[(digit < (int)data[i].length()) ? data[i][digit] : 256]++; }
	for (i = 1; i <= largest; i++) { counter[i] += counter[i - 1]; }
	for (i = length - 1; i >= 0; i--) { sorted[--counter[(digit < (int)data[i].length()) ? data[i][digit] : 256]] = data[i]; }
	if (digit == 0 && !sortersMETA::ascending) {
		for (i = 0; i < length; i++) { data[i] = sorted[length - 1 - i]; }
	}
	else {
		for (i = 0; i < length; i++) { data[i] = sorted[i]; }
	}
	delete[] sorted;//delete to avoid memory leaks
	delete[] counter;
}

//overall class, with most required functions for sorting an array, and other miscellaneous functions such as swap or array display
template <class generic>
class sorters{
private:
	//swaps the value of two generic array members
	static inline void arraySwap(generic* a, generic* b) {
		generic temp = *a;
		*a = *b;
		*b = temp;
	}

	//returns the maximum number of digits that a particular data type may have. required for the radix sort algorithm
	static int getMaxDigits() {
		if (sortersMETA::dataType == 's') { return sortersMETA::STRINGMAX; }
		else if (sortersMETA::dataType == 'l') { return 10; }
		else if (sortersMETA::dataType == 'f') { return sortersMETA::maxFloatFraction + sortersMETA::maxFloatWhole; }
	}

	static int partition(generic data[], int first, int last) {
		int counter;
		int pivot = last;
		int firstDisordered = first;				//disordered implies it is more than the pivot if sorting by ascending, vice versa for descending
		if(sortersMETA::dataType == 's'){ //specific section for dealing with strings in the quicksort, as they do not have same properties as numeric data
			for (counter = first; counter < last; counter++){
				string element = convertToString(data[counter]);
				char counterc = element[sortersMETA::currentStringIndex];
				string pivotstr = convertToString(data[pivot]);
				char pivotc = pivotstr[sortersMETA::currentStringIndex];
				if (counterc < pivotc && sortersMETA::ascending || counterc > pivotc && !sortersMETA::ascending) {
					arraySwap(&data[counter], &data[firstDisordered]);
					firstDisordered++;
				}
			}
		}
		else {
			for (counter = first; counter < last; counter++) {
				if ((data[counter] < data[pivot] && sortersMETA::ascending) || (data[counter] > data[pivot] && !sortersMETA::ascending)) {
					arraySwap(&data[counter], &data[firstDisordered]);
					firstDisordered++;
				}
			}
		}
		arraySwap(&data[pivot], &data[firstDisordered]);
		return firstDisordered;
	}

	static void merge(generic data[], int low, int middle, int high) {
		generic* temp = new generic[high - low + 1];
		int arrayOneCounter = low;
		int arrayTwoCounter = middle + 1;
		int tempCounter = 0;

		if (sortersMETA::dataType == 's') {//specific section for dealing with strings in the merge sort, as they do not have same properties as numeric data
			while (arrayOneCounter <= middle && arrayTwoCounter <= high) {
				if ((convertToString(data[arrayOneCounter])[sortersMETA::currentStringIndex] < convertToString(data[arrayTwoCounter])[sortersMETA::currentStringIndex] && sortersMETA::ascending) || (convertToString(data[arrayOneCounter])[sortersMETA::currentStringIndex] > convertToString(data[arrayTwoCounter])[sortersMETA::currentStringIndex] && !sortersMETA::ascending)) { temp[tempCounter++] = data[arrayOneCounter++]; }
				else { temp[tempCounter++] = data[arrayTwoCounter++]; }
			}

		} else {
			while (arrayOneCounter <= middle && arrayTwoCounter <= high) {
				if ((data[arrayOneCounter] < data[arrayTwoCounter] && sortersMETA::ascending) || (data[arrayOneCounter] > data[arrayTwoCounter] && !sortersMETA::ascending)) { temp[tempCounter++] = data[arrayOneCounter++]; }
				else { temp[tempCounter++] = data[arrayTwoCounter++]; }
			}
		}
		while (arrayOneCounter <= middle) { temp[tempCounter++] = data[arrayOneCounter++]; }
		while (arrayTwoCounter <= high) { temp[tempCounter++] = data[arrayTwoCounter++]; }

		for (arrayOneCounter = low; arrayOneCounter <= high; arrayOneCounter++) {
			data[arrayOneCounter] = temp[arrayOneCounter - low];
		}
		delete[] temp;//delete to avoid memory leaks
	}

public:
	//main function for processing of arrays, and displaying the results and time complexities
	static void processSorts(generic data[]) {
		generic* duplicate = new generic[sortersMETA::ARRAYSIZE];
		sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;
		clock_t startTime;
		bool printed = false;//used to ensure the arrays (sorted and unsorted) are printed only once
		double time[5] = { 0 };//initalize array for holding the time for various sorts
		if (sortersMETA::sorts[1]) { 
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			if (sortersMETA::dataType == 's') {
				startTime = clock();
				while (sortersMETA::currentStringIndex--) {//starting from the highest digit (rightmost character), we sort the array
					quickSort(duplicate, 0, sortersMETA::ARRAYSIZE - 1);
				}
				time[1] = double(clock() - startTime) / CLOCKS_PER_SEC;
				sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;//set the value for the current back to the max, as it is used elsewhere again
			}
			else {
				startTime = clock();
				quickSort(duplicate, 0, sortersMETA::ARRAYSIZE - 1);
				time[1] = double(clock() - startTime) / CLOCKS_PER_SEC;
			}
			cout << "Unsorted array" << endl;
			displayArray(data);
			cout << "Sorted array" << endl;
			displayArray(duplicate);
			cout << "Time taken by quick sort to sort the array: " << time[1] << endl;
			printed = true;//the arrays will not be printed again
		}
		if (sortersMETA::sorts[2]) { 
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			if (sortersMETA::dataType == 's') {
				startTime = clock();
				while (sortersMETA::currentStringIndex--) {//starting from the highest digit (rightmost character), we sort the array
					mergeSort(duplicate, 0, sortersMETA::ARRAYSIZE - 1);
				}
				time[2] = double(clock() - startTime) / CLOCKS_PER_SEC;
				sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;
			}
			else {
				startTime = clock();
				mergeSort(duplicate, 0, sortersMETA::ARRAYSIZE - 1);
				time[2] = double(clock() - startTime) / CLOCKS_PER_SEC;
			}
			if (!printed) {//only runs if it has not already been printed
				cout << "Unsorted array" << endl;
				displayArray(data);
				cout << "Sorted array" << endl;
				displayArray(duplicate);
				printed = true;
			}
			cout << "Time taken by merge sort to sort the array: " << time[2] << endl;
		}
		if (sortersMETA::sorts[3]) {
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			startTime = clock();
			radixSort(duplicate, sortersMETA::ARRAYSIZE);
			time[3] = double(clock() - startTime) / CLOCKS_PER_SEC;
			if (sortersMETA::dataType == 's') {
				sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;
			}
			if (!printed) {//only runs if it has not already been printed
				cout << "Unsorted array" << endl;
				displayArray(data);
				cout << "Sorted array" << endl;
				displayArray(duplicate);
				printed = true;
			}
			cout << "Time taken by radix sort to sort the array: " << time[3] << endl;
		}
		if (sortersMETA::sorts[4]) { 
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			if (sortersMETA::dataType == 's') {
				startTime = clock();
				while (sortersMETA::currentStringIndex--) {
					selectionSort(duplicate, sortersMETA::ARRAYSIZE);
				}
				time[4] = double(clock() - startTime) / CLOCKS_PER_SEC;
				sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;
			}
			else {
				startTime = clock();
				selectionSort(duplicate, sortersMETA::ARRAYSIZE);
				time[4] = double(clock() - startTime) / CLOCKS_PER_SEC;
			}
			if (!printed) {//only runs if it has not already been printed
				cout << "Unsorted array" << endl;
				displayArray(data);
				cout << "Sorted array" << endl;
				displayArray(duplicate);
				printed = true;
			}
			cout << "Time taken by selection sort to sort the array: " << time[4] << endl;
		}
		delete[] duplicate;//delete to avoid memory leaks
	}

	static void quickSort(generic data[], int first, int last) {//generic quick sort algorithm
		int partitionIndex;
		if ((last - first)>0) {
			partitionIndex = partition(data, first, last);
			quickSort(data, first, partitionIndex - 1);
			quickSort(data, partitionIndex + 1, last);
		}
	}

	static void mergeSort(generic data[], int low, int high) {//generic merge sort algorithm
		int middle;
		if (low < high) {
			middle = (low + high) / 2;
			mergeSort(data, low, middle);
			mergeSort(data, middle + 1, high);
			merge(data, low, middle, high);
		}
	}

	static void radixSort(generic data[], int size) {//generic merge sort algorithm
		int maxDigits = getMaxDigits();
		for (int digit = maxDigits; digit > 0; digit--) { 
			countingSort(data, size, digit - 1);
		}

	}

	static void selectionSort(generic data[], int size) {//generic selection sort algorithm
		int extreme;
		if (sortersMETA::dataType == 's') {
			for (int i = 0; i < size - 1; i++) {
				extreme = i;
				for (int j = i + 1; j < size; j++) {
					if ((convertToString(data[j])[sortersMETA::currentStringIndex] < convertToString(data[extreme])[sortersMETA::currentStringIndex] && sortersMETA::ascending) || (convertToString(data[j])[sortersMETA::currentStringIndex] > convertToString(data[extreme])[sortersMETA::currentStringIndex] && !sortersMETA::ascending)) {
						extreme = j;
					}
				}
				arraySwap(&data[i], &data[extreme]);
			}
		}
		else {
			for (int i = 0; i < size - 1; i++) {
				extreme = i;
				for (int j = i + 1; j < size; j++) {
					if ((data[j] < data[extreme] && sortersMETA::ascending) || (data[j] > data[extreme] && !sortersMETA::ascending)) {
						extreme = j;
					}
				}
				arraySwap(&data[i], &data[extreme]);
			}
		}
	}

	static void displayArray(generic arr[]) {//function to print out an array
		for (int i = 0; i< sortersMETA::ARRAYSIZE; i++) { cout << arr[i] << "\t"; }
		cout << endl << endl;
	}

	static void arrayCopy(generic original[], generic duplicate[], int size) {//function to copy the contents of one array to another
		while (size--) {
			duplicate[size] = original[size];
		}
	}


};

char readCharacter(char a, char b) {//function to read a character, only accepting the parameter inputs
	char input;
	do {
		cin >> input;
		if (input != a && input != b) { cout << "Invalid input. Please try again." << endl; }
	} while (input != a && input != b);
	return input;
}

char readCharacter(char a, char b, char c) {//function to read a character, only accepting the parameter inputs
	char input;
	do {
		cin >> input;
		if (input != a && input != b && input != c) { cout << "Invalid input. Please try again." << endl; }
	} while (input != a && input != b && input != c);
	return input;
}

int readPositiveInteger() {//function to read only a positive integer
	int input;
	do {
		cin >> input;
		if (input < 0) { cout << "Invalid input. Please try again." << endl; }
	} while (input < 0);
	return input;
}

int readInteger(int lowerBound, int upperBound) {//function to read an integer within given bounds
	int input;
	do {
		cin >> input;
		if (input < lowerBound || input > upperBound) { cout << "Invalid input. Please try again." << endl; }
	} while (input < lowerBound || input > upperBound);
	return input;
}

void getChoices() {//function to get the user's choices, and initialize all values for the sorting
	cout << "Please select data type(l/f/s)" << endl;
	sortersMETA::dataType = readCharacter('l', 'f', 's');
	cout << "Choose ascending or descending(a/d)" << endl;
	sortersMETA::ascending = (readCharacter('a', 'd') == 'a');
	while (!sortersMETA::sorts[0]) {
		cout << "Choose algorithms to run(If you want to run multiple algorithms, enter values seperated by spaces):" << endl;
		cout << "1. Quick sort" << endl;
		cout << "2. Merge sort" << endl;
		cout << "3. Radix sort" << endl;
		cout << "4. Selection sort" << endl;
		cout << "5. Start sorting process" << endl;
		sortersMETA::sorts[readInteger(0, 5) % 5] = true;
	}
	if (sortersMETA::dataType == 'f' && sortersMETA::sorts[3]) {
		cout << "Enter accuracy of floating point values:" << endl;
		cout << "Enter magnitude of whole number portion (range 0 to 5):" << endl;
		sortersMETA::maxFloatWhole = readInteger(0, 5);
		cout << "Enter magnitude of fraction number portion (range 0 to 5):" << endl;
		sortersMETA::maxFloatFraction = readInteger(0, 5);
	}
	if (sortersMETA::dataType == 's') {
		cout << "Enter max length of strings:(range 1 to 7)" << endl;
		sortersMETA::STRINGMAX = readInteger(1, 7);
	}
	cout << "Enter array size(range 1 to 100):" << endl;
	sortersMETA::ARRAYSIZE = readInteger(1, 100);

}

//function to obtain arrays for long or floating point values
template <class numeric>
void getNumericInput(numeric data[], int size, bool negativeAllowed) {
	cout << "Enter array values:" << endl;
	numeric input;
	if (!negativeAllowed) {
		for (int i = 0; i < size; i++) {
			cout << i << ":\t";
			do {
				cin >> input;
				if (input < 0) { cout << "Invalid input. No negative values allowed. Please try again." << endl; }
			} while (input < 0);
			data[i] = input;
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			cout << i << ":\t";
			cin >> input;
			data[i] = input;
		}
	}
}

//function to obtain values for string array
void getStringInput(string data[], int size) {
	cout << "Enter array values:" << endl;
	string input;
	for (int i = 0; i < size; i++) {
		cout << i << ":\t";
		cin >> input;
		data[i] = input;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


void main(void) {
	getChoices();
	switch (sortersMETA::dataType) {//create arrays based on users choice
	case 'l':
		long* ldata;
		ldata = new long[sortersMETA::ARRAYSIZE];
		getNumericInput(ldata, sortersMETA::ARRAYSIZE, !sortersMETA::sorts[3]);
		sorters<long>::processSorts(ldata);
		delete[] ldata;
		break;
	case 'f':
		float* fdata;
		fdata = new float[sortersMETA::ARRAYSIZE];
		getNumericInput(fdata, sortersMETA::ARRAYSIZE, !sortersMETA::sorts[3]);
		sorters<float>::processSorts(fdata);
		delete[] fdata;
		break;
	case 's':
		string* sdata;
		sdata = new string[sortersMETA::ARRAYSIZE];
		getStringInput(sdata, sortersMETA::ARRAYSIZE);
		sorters<string>::processSorts(sdata);
		delete[] sdata;
		break;
	}
}
