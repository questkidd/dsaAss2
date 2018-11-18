#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include "sortersMETA.h"
using namespace std;


template <class generic> string convertToString(generic input) { return to_string(input); }
//template <> string convertToString<float>(float input) { return input; }
template <> string convertToString<string>(string input) { return input; }

template <class generic>
class sorters{
private:
	static inline void arraySwap(generic* a, generic* b) {
		generic temp = *a;
		*a = *b;
		*b = temp;
	}

	static int getMaxDigits() {
		if (sortersMETA::dataType == 's') { return sortersMETA::STRINGMAX; }
		else if (sortersMETA::dataType == 'l') { return 10; }
		else if (sortersMETA::dataType == 'f') { return 7; }
	}

	static int partition(generic data[], int first, int last) {
		int counter;
		int pivot = last;
		int firstDisordered = first;						//disordered implies it is more than the pivot if sorting by ascending
		if(sortersMETA::dataType == 's'){
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

		if (sortersMETA::dataType == 's') {
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
		delete[] temp;
	}

	static void countingSort(generic data[], int length, int digit) {
		int i;
		int largest = 256;//max value of char being 255
		generic* sorted = new generic[sortersMETA::ARRAYSIZE];
		int* counter = new int[largest + 1];
		for (i = 0; i <= largest; i++) { counter[i] = 0; }
		for (i = 0; i < length; i++) { counter[ (digit < (int)convertToString(data[i]).length()) ? convertToString(data[i])[digit] : 256]++; }
		for (i = 1; i <= largest; i++) { counter[i] += counter[i - 1]; }
		for (i = length - 1; i >= 0; i--) { sorted[--counter[(digit < (int)convertToString(data[i]).length()) ? convertToString(data[i])[digit] : 256]] = data[i]; }
		for (i = 0; i < length; i++) { data[i] = sorted[i]; }
		/*
		bool alphanumeric = sortersMETA::dataType == 's';
		int arrayCounter;
		generic largest = !alphanumeric ? data[0] : convertToString(data[0])[sortersMETA::currentStringIndex];
		generic* sorted = new generic[sortersMETA::ARRAYSIZE];
		for (arrayCounter = 1; arrayCounter < length; arrayCounter++) {
			if (!alphanumeric && largest < data[arrayCounter]) {
				largest = data[arrayCounter];
			}
			else if (alphanumeric && largest < convertToString(data[arrayCounter])[sortersMETA::currentStringIndex]) {
				largest = convertToString(data[arrayCounter])[sortersMETA::currentStringIndex];
			}
		}
		generic* counter = new generic[largest + 1];
		for (i = 0; i <= largest; i++) {
			counter[i] = 0;
		}
		if (!alphanumeric) {
			for (i = 0; i < length; i++) {
				counter[data[i]]++;
			}
		}
		else {
			for (i = 0; i < length; i++) {
				counter[convertToString(data[i])[sortersMETA::currentStringIndex]]++;
			}
		}
		for (i = 1; i <= largest; i++) {
			counter[i] += counter[i - 1];
		}
		for (i = length - 1; i >= 0; i--) {
			sorted[--counter[data[i]]] = data[i];
		}
		if (sortersMETA::ascending) {
			for (i = 0; i < length; i++) {
				data[i] = sorted[i];
			}
		}
		else {
			for (i = 0; i < length; i++) {
				data[sortersMETA::ARRAYSIZE - 1 - i] = sorted[i];
			}
		}
		delete sorted;
		delete counter;
		*/
	}

public:
	static void processSorts(generic data[]) {
		generic* duplicate = new generic[sortersMETA::ARRAYSIZE];
		sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;
		clock_t startTime;
		bool printed = false;
		double time[5] = { 0 };
		if (sortersMETA::sorts[1]) { 
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			if (sortersMETA::dataType == 's') {
				startTime = clock();
				while (sortersMETA::currentStringIndex--) {
					quickSort(duplicate, 0, sortersMETA::ARRAYSIZE - 1);
				}
				time[1] = double(clock() - startTime) / CLOCKS_PER_SEC;
				sortersMETA::currentStringIndex = sortersMETA::STRINGMAX;


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
			printed = true;
		}
		if (sortersMETA::sorts[2]) { 
			arrayCopy(data, duplicate, sortersMETA::ARRAYSIZE);
			if (sortersMETA::dataType == 's') {
				startTime = clock();
				while (sortersMETA::currentStringIndex--) {
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
			if (!printed) {
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
			if (!printed) {
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
			if (!printed) {
				cout << "Unsorted array" << endl;
				displayArray(data);
				cout << "Sorted array" << endl;
				displayArray(duplicate);
				printed = true;
			}
			cout << "Time taken by selection sort to sort the array: " << time[4] << endl;
		}
		delete[] duplicate; // causes error for some reason, but after changing delete to delete[], no errors!

	}
	static void quickSort(generic data[], int first, int last) {
		int partitionIndex;
		if ((last - first)>0) {
			partitionIndex = partition(data, first, last);
			quickSort(data, first, partitionIndex - 1);
			quickSort(data, partitionIndex + 1, last);
		}
	}

	static void mergeSort(generic data[], int low, int high) {
		int middle;
		if (low < high) {
			middle = (low + high) / 2;
			mergeSort(data, low, middle);
			mergeSort(data, middle + 1, high);
			merge(data, low, middle, high);
		}
	}

	//maybe convert floats to strings, and sort them that way?

	static void radixSort(generic data[], int size) {
		int maxDigits = getMaxDigits();
		for (int digit = maxDigits; digit > 0; digit--) { //
			countingSort(data, size, digit - 1);
		}

	}

	//static void radixSort(generic data[], int length) {
	//	register int digitCounter, counterOne, counterTwo, factor;
	//	//int radix = sorters::META == 's'?256:10;
	//	const int radix = 10;
	//	int maxdigits = getMaxDigits();
	//	//queue<generic> queues = new queue<generic>[radix];
	//	queue<generic> queues[radix];
	//	for (digitCounter = 0, factor = 1; digitCounter < maxdigits; factor *= radix, digitCounter++) {
	//		for (counterOne = 0; counterOne <length; counterOne++) {
	//			queues[(data[counterOne] / factor) % radix].push(data[counterOne]);
	//		}
	//		for (counterOne = counterTwo = 0; counterOne < radix; counterOne++) {
	//			while (!queues[counterOne].empty()) {
	//				data[counterTwo++] = queues[counterOne].front();
	//				queues[counterOne].pop();
	//			}
	//		}
	//	}
	//}

	static void selectionSort(generic data[], int size) {
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

	static void displayArray(generic arr[]) {
		for (int i = 0; i< sortersMETA::ARRAYSIZE; i++) { cout << arr[i] << "\t"; }
		cout << endl << endl;
	}

	static void arrayCopy(generic original[], generic duplicate[], int size) {
		while (size--) {
			duplicate[size] = original[size];
		}
	}


};

void main(void) {
	sortersMETA();//initializing the static members of the class
	cout << "Please select data type(l/f/s)" << endl;
	cin >> sortersMETA::dataType;
	cout << "Choose ascending or descending(a/d)" << endl;
	char order;
	cin >> order;
	sortersMETA::ascending = (order == 'a');
	while (!sortersMETA::sorts[0]) {
		cout << "Choose algorithms to run(If you want to run multiple algorithms, enter values seperated by spaces):" << endl;
		cout << "1. Quick sort" << endl;
		cout << "2. Merge sort" << endl;
		cout << "3. Radix sort" << endl;
		cout << "4. Selection sort" << endl;
		cout << "5. Start sorting process" << endl;
		int choice;
		cin >> choice;
		sortersMETA::sorts[choice % 5] = true;
	}

	
	switch (sortersMETA::dataType) {
	case 'l':
		//if radix sort selected, prevent input of negative numbers
		long ldata[sortersMETA::ARRAYSIZE];
		for (int i = 0; i < sortersMETA::ARRAYSIZE; i++) {
			ldata[i] = rand() % 100;
		}
		sorters<long>::processSorts(ldata);

		break;
	case 'f':
		float fdata[sortersMETA::ARRAYSIZE];
		for (int i = 0; i < sortersMETA::ARRAYSIZE; i++) {
			fdata[i] =(float) (rand() % 100);
		}
		sorters<float>::processSorts(fdata);
		break;
	case 's':
		string sdata[sortersMETA::ARRAYSIZE] = { "Faraz", "Lihaz", "Ilyas", "Udaas", "Khaas", "Daraz", "Nawaz" };
		//char carray[7][6] = { "Faraz", "Lihaz", "Ilyas", "Udaas", "Khaas", "Daaaz", "Nawaz" };
		sorters<string>::processSorts(sdata);
		break;
	}
}

/*
template <typename T> void foo() { /* generic implementation   }

template <> void foo<animal>() { /* specific for T = animal  }
*/