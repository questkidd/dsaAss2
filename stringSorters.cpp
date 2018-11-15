#include <iostream>
#include <ctime>

class sorter{
private:
	static bool ascending;

	static inline void arraySwap(int* a, int* b){
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	static int partition(int numbers[], int first, int last){
		int counter;
		int pivot = last;
		int firstDisordered = first;						//disordered implies it is more than the pivot if sorting by ascending

		for(counter = first; counter < last; counter++){
			if((numbers[counter] < numbers[pivot] && ascending) || (numbers[counter] > numbers[pivot] && !ascending)){
				arraySwap(&numbers[counter], &numbers[firstDisordered]);
				firstDisordered++;
			}
		}
		arraySwap(&numbers[pivot], &numbers[firstDisordered]);
		return firstDisordered;
	}

	static void merge(int numbers[], int low, int middle, int high){
        int* temp = new int[high - low + 1];
        int arrayOneCounter = low;
        int arrayTwoCounter = middle+1;
        int tempCounter = 0;

        while(arrayOneCounter <= middle && arrayTwoCounter <= high){
            if((numbers[arrayOneCounter] < numbers[arrayTwoCounter] && ascending) || (numbers[arrayOneCounter] > numbers[arrayTwoCounter] && !ascending)){temp[tempCounter++] = numbers[arrayOneCounter++];}
            else{temp[tempCounter++] = numbers[arrayTwoCounter++];}
        }

        while(arrayOneCounter <= middle){temp[tempCounter++] = numbers[arrayOneCounter++];}
        while(arrayTwoCounter <= high){temp[tempCounter++] = numbers[arrayTwoCounter++];}

        for(arrayOneCounter = low; arrayOneCounter <= high; arrayOneCounter++){
                numbers[arrayOneCounter] = temp[arrayOneCounter - low];
        }
        delete temp;
    }

public:
	static void quickSort(int numbers[], int first, int last){
		int partitionIndex;
		if((last-first)>0){
			partitionIndex = partition(numbers, first, last);
			quickSort(numbers, first, partitionIndex-1);
			quickSort(numbers, partitionIndex+1, last);
		}
	}

	static void mergeSort(int numbers[], int low, int high){
		int middle;
		if (low < high){
			middle = (low + high) / 2;
			mergeSort(numbers, low, middle);
			mergeSort(numbers, middle+1, high);
			merge(numbers, low, middle, high);
		}
	}

	static void selectionSort(int numbers[], int size) {
		int extreme;
		for (int i = 0; i < size - 1; i++) {
			extreme = i;
			for (int j = i + 1; j < size; j++) {
				if ((numbers[j] < numbers[extreme] && ascending) ||(numbers[j] > numbers[extreme] && !ascending)) {
					extreme = j;
				}
			}
			arraySwap(&numbers[i], &numbers[extreme]);
		}
	}

	static void displayArray(int arr[]) {
		for (int i = 0; i< ARRAYSIZE; i++) { cout << arr[i] << "\t"; }
			cout << endl << endl;
	}

    static void arrayCopy(int array1[], int array2[], int size) {
        while (size--) {
            array1[size] = array2[size];
        }
    }

	
}