#include <iostream>

using namespace std;

int HoarePartition(int *A, int l, int r) {
    int p = A[l];
    int i = l;
    int j = r + 1;
    
    do {
        do {
            i++;
        } while (A[i] < p && i < r);
        
        do {
            j--;
        } while (A[j] > p);
        
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        
    } while (i < j);
    
    int temp = A[i];
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

int binarySearch(int* A, int l, int r, int K) {
    if (r < l) {
        return -1;
    }

    int m = (l+r) / 2;
    if ( K == A[m]) {
        return m;
    
    } else if ( K < A[m]) {
        return binarySearch(A, l, m - 1, K);
    
    } else {
        return binarySearch(A, m + 1, r, K);
    }
}

int main() {
    int size, K, num, target, index;
    int count = 0;
    cin >> size;
    cin >> K;

    int* array = new int[size];

    for (int i = 0; i < size; i++) {
        cin >> num;
        array[i] = num;
    }

    quickSort(array, 0, size - 1);

    for (int x = 0; x < size; x++) {
        if (array[x] > K) {
            target = array[x] - K;
            
            index = binarySearch(array, 0, size, target);

            if (index != -1) {
                //cout << array[x] << " - " << array[index] << " = " << K << endl;
                count++;
            }
        }
    }

    cout << count;

    delete[] array;
    return 0;
}