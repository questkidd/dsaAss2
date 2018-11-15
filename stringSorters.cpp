#include <iostream>
#include <ctime>

template <class generic>
class sorter {
private:
	static bool ascending;
	static char dataType = 's';
	static const int STRINGMAX = 5;

	static inline void arraySwap(generic* a, generic* b) {
		generic temp = *a;
		*a = *b;
		*b = temp;
	}

	static int getMaxDigits(){
		if(dataType == 's'){return STRINGMAX;}
		else if(dataType == 'l'){return 10;}
		else if (dataType == 'f'){return 7;}
	}

	static int partition(generic data[], int first, int last) {
		int counter;
		int pivot = last;
		int firstDisordered = first;						//disordered implies it is more than the pivot if sorting by ascending

		for (counter = first; counter < last; counter++) {
			if ((data[counter] < data[pivot] && ascending) || (data[counter] > data[pivot] && !ascending)) {
				arraySwap(&data[counter], &data[firstDisordered]);
				firstDisordered++;
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

		while (arrayOneCounter <= middle && arrayTwoCounter <= high) {
			if ((data[arrayOneCounter] < data[arrayTwoCounter] && ascending) || (data[arrayOneCounter] > data[arrayTwoCounter] && !ascending)) { temp[tempCounter++] = data[arrayOneCounter++]; }
			else { temp[tempCounter++] = data[arrayTwoCounter++]; }
		}

		while (arrayOneCounter <= middle) { temp[tempCounter++] = data[arrayOneCounter++]; }
		while (arrayTwoCounter <= high) { temp[tempCounter++] = data[arrayTwoCounter++]; }

		for (arrayOneCounter = low; arrayOneCounter <= high; arrayOneCounter++) {
			data[arrayOneCounter] = temp[arrayOneCounter - low];
		}
		delete temp;
	}

public:
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

	static void selectionSort(generic data[], int size) {
		int extreme;
		for (int i = 0; i < size - 1; i++) {
			extreme = i;
			for (int j = i + 1; j < size; j++) {
				if ((data[j] < data[extreme] && ascending) || (data[j] > data[extreme] && !ascending)) {
					extreme = j;
				}
			}
			arraySwap(&data[i], &data[extreme]);
		}
	}

	static void displayArray(generic arr[]) {
		for (int i = 0; i< ARRAYSIZE; i++) { cout << arr[i] << "\t"; }
			cout << endl << endl;
	}

	static generic* arrayCopy(generic original[], int size) {
		generic* duplicate = new generic[size];
		while (size--) {
			duplicate[size] = original[size];
		}
		return duplicate;
	}


};