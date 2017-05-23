/*
 *File: SortingAlgorithms.c
 *Author: Andrew Seale
 *Purpose: Sorts Integer arrays through various sorting algorithms:
 *	   Bubble Sort
 *	   Insertion Sort
 *	   Merge Sort
 *	   Quick Sort
 */

#include "header.h"

  //Purpose: sorts an array with the Bubble Sort algorithm
  //compares two elements at a time, and if they are out of order, swap them
  //continue this until the array is sorted
  //Parameters: int* array: the array to be sorted
  //            int arrayLength: the size of the pointer, as pointers don't
  //                             carry that information
void bubbleSort(int* array,int arrayLength){
     //boolean flag meant to check whether the array is sorted or not
     //0 means true, 1 means false
   int sorted = 1;
   while(sorted != 0){
      sorted = 0;
      int i;
        //stop one element before the end of the array to avoid a segfault
      for(i=0;i<arrayLength-1;i++){
           //equivalent expression: if(array[i] > array[i+1])
         if(*(array+i) > *(array+i+1)){
            sorted = 1;
            int temp = *(array+i);
            *(array + i) = *(array + i + 1);
            *(array + i + 1) = temp;
         }
      }
   }
}

  //Purpose: sorts an array with the Insertion Sort algorithm
  //traverses the array until an out of order element is found
  //then traverses back until its proper place is found, inserting
  //the element in its proper place
void insertionSort(int* array,int arrayLength){
     //start at the 1st element instead of the 0th because the 0th
     //element is considered to be in order, as it is compared to nothing
     //else at this point
   int i,j;
   for(i=1;i<arrayLength;i++){
        //an element is out of place, must insert it into its correct place
        //in the array
      int temp = *(array+i);
      j = i;

      while(j > 0 && temp < *(array+j-1)){
         *(array+j) = *(array+j-1);
         j--;
      }

      *(array+j) = temp;
   }
}

  //prototype for helper methods used in Merge Sort
void merge(int *array,int low, int mid, int high);
void sort(int* array, int low, int high);

  //Purpose: sorts an array using the Merge Sort algorithm
  //breaks the arrays down into smaller parts, and then reorganizes them
  //into larger sorted arrays
  //utilizes "Divide-and-conquer" methodology
void mergeSort(int* array,int arrayLength){
     //call to recursive function sort to break the array into smaller 
     //pieces for sorting later on
   sort(array,0,arrayLength-1);
}
   //Purpose: breaks the arrays into smaller parts designed to be merged
   //back together with the merge function
void sort(int* array, int low, int high){
     //if the array is larger than size one (low == high)
     //perform the Merge Sort algorithm upon it
   if(high > low){
      int mid = (low + high)/2;
        //split the array into smaller halves and perform Merge Sort on
        //each half
      sort(array,low,mid);
      sort(array,mid+1,high);
      merge(array,low,mid,high);
   }
}
  //Purpose: Takes the elements in an array, places them into two smaller
  //arrays, and uses the smaller arrays to hold the elements to be placed
  //back into the bigger array in order
void merge(int* array, int low, int mid, int high){
   int i,j,k;
   int leftHalf = mid - low + 1;
   int rightHalf = high - mid;

   int *lSubArray = malloc(sizeof(int) * leftHalf);
   int *rSubArray = malloc(sizeof(int) * rightHalf);

   for(i=0;i<leftHalf;i++)
      *(lSubArray + i) = *(array + low + i);
   for(j=0;j<rightHalf;j++)
      *(rSubArray + j) = *(array + mid + 1 + j);

   i = j = 0; 
   k = low;

   while(i < leftHalf && j < rightHalf){
      if(*(lSubArray + i) <= *(rSubArray + j)){
         *(array + k) = *(lSubArray + i);
         i++;
      }
      else{
         *(array + k) = *(rSubArray + j);
         j++;
      }

      k++;
   }

   while(i < leftHalf){
      *(array + k) = *(lSubArray + i);
      i++;
      k++;
   }

   while(j < rightHalf){
      *(array + k) = *(rSubArray + j);
      j++;
      k++;
   }
   free(lSubArray);
   free(rSubArray);
}

  //Prototypes for quickSort helper functions
void quicklySort(int* array, int low, int high);
int partitionify(int* array, int low, int high);
  //Purpose: sorts an integer array using the Quick Sort algorithm
  //picks a pivot in the array and sorts all elements in the array into
  //greater than or less than said pivot
  //it then recurses down into each half of the array performing the same 
  //action
  //utilizes "Divide-and-conquer" methodology
void quickSort(int* array,int arrayLength){
   quicklySort(array,0,arrayLength-1);
}

  //Purpose: Performs the Quick Sort algorithm upon a given array
void quicklySort(int* array,int low,int high){
   int partition;
   if(high > low){
      partition = partitionify(array,low,high);
      quicklySort(array,low,partition-1);
      quicklySort(array,partition+1,high);     
   }
}
  //Purpose: picks a pivot, and organizes all elements less than the pivot
  //to go to the left of the pivot, and all greater to go right of the pivot
int partitionify(int* array, int low,int high){
     //the element picked to sort around
     //truly, the pivot doesn't matter as the array is randomly sorted
     //and therefore we wouldn't know the location of the perfect pivot
   int pivot = *(array + high);
   int i = low - 1;
   int j,temp;
   for(j=low;j<=high-1;j++){
      if(*(array + j) <= pivot){
         i++;
         temp = *(array + j);
         *(array + j) = *(array + i);
         *(array + i) = temp;
      }
   } 
   temp = *(array + high);
   *(array + high) = *(array + i + 1);
   *(array + i + 1) = temp;
   return i+1;
}
