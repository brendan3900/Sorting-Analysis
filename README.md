# Sorting-Analysis
This program was created to test/analyze the complexities of Selection, Bubble, Insertion, Merge, and Quick sort algorithms.


Summary of Approach

o To begin this program, the Selection, Bubble, Insertion, Merge, and Quick sort algorithms were implemented. Three arrays were created, each containing 1000 integers, including the best case (already sorted), average case (randomly generated integers), and the worst case (reverse sorted). The array values ranged from 0 to 10,000. 

o The five sorting algorithms were tested using these three arrays. The arrays were copied into arrays named tBST, tAVG, and tWST, and reinitialized to the original array before each function call. This was to make sure that all algorithms were tested with an identical set of arrays. To perform this copy task, a separate function was created. 

o Two global variables were created called moves and comps: 
     Moves: this variable was incremented with every movement of any of the elements to be sorted from one location in the array to another. 
     Comps: this variable was incremented with each comparison operation on the elements to be sorted. 
     Both of these variables were set to zero before each call of a sorting algorithm function. Also, after each call to a sorting algorithm, the values of moves and comps were         written to an external .txt file called sort.txt. 
    
o The functions of these sorting algorithms were verified. This was done through a new function which checks each element in the sorted array and compares it with the next element in the array. If any element is greater than the element after it, the function returns false and displays a message saying that the sorting algorithm did not work correctly. 

o sort.txt was used to make the two graphs included in this repository, comparing the number of moves and the number of comparisons for each of these algorithms.
