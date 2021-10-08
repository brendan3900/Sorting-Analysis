//Brendan Li

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>
using namespace std;

//declaring a const int for the size of the test arrays
const int SIZE = 1000;
//global variables for keeping track of moves and comps
int moves=0;
int comps=0;


//Selection sort
//first the find Largest function was created
int findIndexOfLargest(const int A[], int size){
    int indexSoFar = 0; // make index
    //go through array and compare elements
    for (int currentIndex=1; currentIndex<size; currentIndex++){
        comps=comps+1;//increment comparison
        if (A[currentIndex]>A[indexSoFar])
            indexSoFar=currentIndex;//update largest
    }
    return indexSoFar;//return largest's index
}
//actual sort function
void selectionSort(int A[], int n){
    //find largest of unsorted part of array
    for(int last=n-1; last>=1; last--){
        int largest = findIndexOfLargest(A, last+1);//update largest
        if (largest != last){
            //swap largest with last element and update moves
            swap(A[largest], A[last]); moves=moves+3;}
    }
}




//Insertion Sort
void insertionSort(int A[], int n){
    //go through unsorted section of array
    for(int unsorted=1; unsorted<n; unsorted++){
        //get nextItem and set location of unsorted
        int nextItem = A[unsorted];
        int loc=unsorted;
        comps=comps+1;//update compes
        while((loc>0)&&(A[loc-1]>nextItem)){
            //if unsorted, set and update move
            A[loc] = A[loc-1]; moves=moves+1;
            //decrement loc and update comps
            loc--; comps=comps+1;
        }
        //if not sorted, change A[loc] and update moves
        if (loc != unsorted){
            A[loc]=nextItem; moves=moves+1;}
    }
}




//Bubble Sort
void bubbleSort(int A[], int n){
    //bool value set to false
    bool sorted = false;
    //pass int
    int pass = 1;
    //while loop while sorted is false and pass<n
    while (!sorted && (pass<n)){
        sorted = true;//set to true
        //for the array
        for(int index=0; index<n-pass; index++){
            int nextIndex = index+1;//change the next index
            comps=comps+1;//update comps
            if (A[index]>A[nextIndex]){
                swap(A[index], A[nextIndex]); moves=moves+3;//swap and update moves
                sorted=false;//set back to fals
            }
        }
        //update pass int
        pass++;
    }
}



//Quick Sort
//order method
void order(int A[], int i, int j){
    //update comps
    comps=comps+1;
    //if ones larger, swap and update moves
    if(A[i]>A[j]){
        swap(A[i], A[j]); moves=moves+3;}
}
//sortFirstMiddleLast method
int sortFirstMiddleLast(int A[], int first, int last){
    //find mid
    int mid=first+(last-first)/2;
    //call order for the first middle and last elements
    order(A, first, mid);
    order(A, mid, last);
    order(A, first, mid);
    //return the mid value
    return mid;
}
//partition function
int partition(int A[], int first, int last){
    //pivot index set to mid
    int pivotIndex = sortFirstMiddleLast(A, first, last);
    swap(A[pivotIndex], A[last-1]);//swap values
    moves=moves+3;//update moves
    pivotIndex=last-1;//change pivot index
    int pivot=A[pivotIndex];//update pivot
    //left and right indexs
    int indexLeft=first+1;
    int indexRight=last-2;
    bool done = false;
    //while not done
    while (!done) {
        comps=comps+1;//update comps
        //while left is less than pivot, update and update comps
        while(A[indexLeft]<pivot){
            indexLeft=indexLeft+1; comps=comps+1;}
        //update comps
        comps=comps+1;
        //while right is greater than pivot, update and update comps
        while(A[indexRight]>pivot){
            indexRight=indexRight-1; comps=comps+1;}
        //update comps
        comps=comps+1;
        //if left is less than right still
        if(indexLeft<indexRight) {
            //swap and update moves
            swap(A[indexLeft], A[indexRight]);
            moves=moves+3;
            //increment left, decrement right
            indexLeft = indexLeft + 1;
            indexRight = indexRight - 1;
        }
        else{done = true;}//else, done and close while
        }
    //swap and update moves
    swap(A[pivotIndex], A[indexLeft]);
    moves=moves+3;
    //get pivot index and return
    pivotIndex=indexLeft;
    return pivotIndex;
}
void quickSort(int A[], int first, int last){
    //find size of array
    int sz=last-first+1;
    //if less than 25, use insertion
    if(sz<25){
        insertionSort(A+first, sz);
    }
    else {
        //else, get pivotIndex
        int pivotIndex = partition(A, first, last);
        //recursive calls for divided array
        quickSort(A, first, pivotIndex - 1);
        quickSort(A, pivotIndex + 1, last);
    }
}




//Merge sort
//merge function
void merge(int A[], int first, int mid, int last){
    //temporary array and the first1/last1 which is the first half of array
    int tempA[SIZE];
    int first1=first;
    int last1=mid;
    //second half of array
    int first2=mid+1;
    int last2=last;
    //index checking
    int index = first1;
    //while first1 is less than last one and same for 2
    while ((first1<=last1) && (first2<=last2)){
        comps=comps+1;//update comps
        //if
        if (A[first1]<=A[first2]){
            tempA[index]=A[first1]; moves=moves+1;//update temporary and update moves/first1
            first1++;
        }
        else{//else update temorary to other value and update moves/first2
            tempA[index]=A[first2]; moves=moves+1;
            first2++;
        }
        //update the index
        index++;
    }
    //while first1 is before last 1
    while(first1<=last1){
        tempA[index]=A[first1]; moves=moves+1;//update temporary and update moves/first1
        first1++;
        index++;
    }
//while first2 is before last 12
    while(first2<=last2){
        tempA[index] = A[first2]; moves=moves+1;//update temporary and update moves/first2
        first2++;
        index++;
    }
    //for, set real array to temporary array
    for(index=first; index<=last; index++){
        A[index]=tempA[index];
    }
}
//mergeSort to using merge function and recursion
void mergeSort(int A[], int first, int last){
    //if first is still less than last
    if(first<last){
        //find mid
        int mid = first + (last-first)/2;
        //recursion for two halves
        mergeSort(A, first, mid);
        mergeSort(A, mid+1, last);
        //call to merge function
        merge(A, first, mid, last);
    }
}



//copy Array function
void copy(int A[], int copy[], int size){
    for(int i=0; i<size; i++){//go through array
        copy[i]=A[i];//copy them all into separate array
    }
}


//Check function
bool check(int A[], int s){
    bool c=true;
    //compare all elements with a for loop
    for(int i=0; i<s-1; i++){
        if(A[i]>A[i+1])
            c=false;
    }
    //if true give the correct message
    if(c)
        cout<<"The sort worked correctly."<<endl;
    else
        cout<<"The sort didn't work correctly."<<endl;//else, give the incorrect message
    return c;//return that bool
}



int main() {
    //code for opening text file
    ofstream outf;
    //open at file location
    outf.open("\\Users\\Brend\\OneDrive\\Desktop\\EECE2560\\sort.txt");
    //if this fails display error message
    if(outf.fail()){
        cerr << "Error: Could not open output file\n";
        exit(1);
    }
    //create test arrays of the given size
    int BST[SIZE];
    int AVG[SIZE];
    int WST[SIZE];
    //variable for setting array values
    int val=10;
    for(int i=0; i<SIZE; i++){
        BST[i]=val;//BEST CASE
        val=val+10;//increment by 10 each element
    }
    //variable for setting array values, going down
    val=10000;
    for(int i=0; i< SIZE; i++){
        WST[i]=val;//WORST CASE
        val=val-10;//decrement by 10 each element
    }
    //random integers between 0 and 10000
    srand(time(NULL));
    for(int i=0; i<SIZE; i++)
        AVG[i]=rand()%10000;//set each element

    //testing selection Sort
    //make copy elemeeents and arrays
    int tBST[SIZE]; copy(BST, tBST, SIZE);
    int tAVG[SIZE]; copy(AVG, tAVG, SIZE);
    int tWST[SIZE]; copy(WST, tWST, SIZE);

    //test selection sort and write the moves/comps, best case
    selectionSort(tBST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test selection sort and write the moves/comps, avg case
    selectionSort(tAVG, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test selection sort and write the moves/comps, wst case
    selectionSort(tWST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    outf<<endl;
    //check to verify function
    check(tBST, SIZE);
    check(tAVG, SIZE);
    check(tWST, SIZE);


    //testing insertion sort
    //copy original array elements
    copy(BST, tBST, SIZE);
    copy(AVG, tAVG, SIZE);
    copy(WST, tWST, SIZE);
    //test insertion sort and write the moves/comps, best case
    insertionSort(tBST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test insdertion sort and write the moves/comps, avg case
    insertionSort(tAVG, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test insertion sort and write the moves/comps, wst case
    insertionSort(tWST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    outf<<endl;
    //check to verify function
    check(tBST, SIZE);
    check(tAVG, SIZE);
    check(tWST, SIZE);


    //testing Bubble sort
    //copy original array elements
    copy(BST, tBST, SIZE);
    copy(AVG, tAVG, SIZE);
    copy(WST, tWST, SIZE);
    //test bubble sort and write the moves/comps, best case
    bubbleSort(tBST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test bubble sort and write the moves/comps, avg case
    bubbleSort(tAVG, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test bubble sort and write the moves/comps, wst case
    bubbleSort(tWST, SIZE);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    outf<<endl;
    //check to verify function
    check(tBST, SIZE);
    check(tAVG, SIZE);
    check(tWST, SIZE);

    //testing Merge sort
    //copy original array elements
    copy(BST, tBST, SIZE);
    copy(AVG, tAVG, SIZE);
    copy(WST, tWST, SIZE);
    //test merge sort and write the moves/comps, best case
    mergeSort(tBST, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test merge sort and write the moves/comps, avg case
    mergeSort(tAVG, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test merge sort and write the moves/comps, wst case
    mergeSort(tWST, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    outf<<endl;
    //check to verify function
    check(tBST, SIZE);
    check(tAVG, SIZE);
    check(tWST, SIZE);

    //testing Quick sort
    //copy original array elements
    copy(BST, tBST, SIZE);
    copy(AVG, tAVG, SIZE);
    copy(WST, tWST, SIZE);
    //test quick sort and write the moves/comps, best case
    quickSort(tBST, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test quick sort and write the moves/comps, avg case
    quickSort(tAVG, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    //test quick sort and write the moves/comps, wst case
    quickSort(tWST, 0, SIZE-1);
    outf << moves <<endl; moves=0;
    outf << comps <<endl; comps=0;
    outf<<endl;
    //check to verify function
    check(tBST, SIZE);
    check(tAVG, SIZE);
    check(tWST, SIZE);

    return 0;
}
