#include <iostream>

using namespace std;

int HoarePartition(int *A, int l, int r) {
    int p = A[l];
    int i = l;
    int j = r + 1;
    int temp;
    
    do {
        do {
            i++;
        } while (A[i] < p && i < r);
        
        do {
            j--;
        } while (A[j] > p);
        
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        
    } while (i < j);
    
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    
    temp = A[l];
    A[l] = A[j];
    A[j] = temp;
    
    return j;
}

void quickSort(int *A, int l, int r) {
    if (l < r) {
        int s = HoarePartition(A, l, r);
        quickSort(A, l, s-1);
        quickSort(A, s + 1, r);
    }
}

// algoritmo quicksort baseado no pseudocodigo dos slides

int main() {
    int testCases, n, num, score, size;
    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        cin >> n;
        size = n * 2;
        int* array = new int[size]; 
        score = 0;
        for (int j = 0; j < size; j++) {
            cin >> num;
            array[j] = num;
            //cout << "botou " << num << " na posicao " << j << endl;
        }
       
       quickSort(array, 0, (size) - 1);

       for (int k = 0; k < size; k += 2) {
        score += array[k];
        //cout << "adicionado " << array[k] << " ao score" << endl;
       }
       cout << score << endl;

       delete[] array;

    }
    return 0;
}