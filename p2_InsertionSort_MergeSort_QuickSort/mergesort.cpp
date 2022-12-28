// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int &cnt, int &memacc) {
   MergeSortRecurse(numbers, 0, numbers->size() - 1, cnt, memacc);
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int &cnt, int &memacc) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, cnt, memacc);
      MergeSortRecurse(numbers, j + 1, k, cnt, memacc);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, cnt, memacc);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int &cnt, int &memacc) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
     cnt++;
     memacc = memacc + 2;
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         memacc = memacc + 2;
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;
      }
      else {
         memacc = memacc + 2;
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      memacc = memacc + 2;
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      memacc = memacc + 2;
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      memacc = memacc + 2;
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
   }
}