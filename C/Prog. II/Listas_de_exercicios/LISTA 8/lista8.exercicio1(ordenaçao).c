#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bolha
void bubbleSort(char arr[], int n) {
    int i, j;
    char temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// QuickSort (implementacao)
void quickSort(char arr[], int low, int high) {
    if(low < high) {
        int pivot = arr[high], i = low - 1;
        for(int j = low; j < high; j++) {
            if(arr[j] < pivot) {
                i++;
                char temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        i++;
        char temp = arr[i];
        arr[i] = arr[high];
        arr[high] = temp;
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

// qsort - funcao comparadora
int cmpChar(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int main() {
    char str[100];
    printf("Digite uma string: ");
    scanf(" %[^\n]", str);
    int n = strlen(str);
    char strBubble[100], strQuick[100], strQsort[100];
    strcpy(strBubble, str);
    strcpy(strQuick, str);
    strcpy(strQsort, str);

    bubbleSort(strBubble, n);
    quickSort(strQuick, 0, n - 1);
    qsort(strQsort, n, sizeof(char), cmpChar);

    printf("Ordenacao com bubble sort: %s\n", strBubble);
    printf("Ordenacao com quick sort: %s\n", strQuick);
    printf("Ordenacao com qsort: %s\n", strQsort);

    return 0;
}
