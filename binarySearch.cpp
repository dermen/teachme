#include <stdlib.h>
#include <iostream>
#include <stdio.h>

struct Node{
    int payload;
    Node* next;
};

class Stacksy{
    Node * top=NULL;
    public:
        void push( int data);
        int pop( );
};


void Stacksy::push( int data){
    Node* newNode = new Node();
    newNode->payload = data;
    newNode->next = top;
    top = newNode; 
}
 


int Stacksy::pop(){
    if (top == NULL) return -1;
    int value = top->payload;
    
    //  delete the node
    Node* temp = top;
    top = top->next;
    delete temp;
    return value;
}


class BinarySearchTools{
    public:
        int findPivot( int* numbers , int N );
        int find( int* numbers, int N, int value);   
        int countDuplicates( int* numbers, int N, int value);
        int firstOccurance( int * numbers, int N, 
                            int value, bool first );
};

int BinarySearchTools::findPivot( int * numbers, int N ){
    int low = 0;
    int high = N-1;
    int mid = (low + high) / 2;

    int pivot(-1);
    while( low <= high){
        if (numbers[low] <= numbers[high]){
            pivot = low;
            break;
        }
        int next = (mid+1 )%N;
        int prev = (mid-1 + N)%N;
        if ( numbers[next] > numbers[mid] & 
                   numbers[prev] > numbers[mid]){
            pivot = mid;
            break;}
        else if( numbers[mid] < numbers[low])
            high = mid -1;
        else
            low = mid +1;
        mid = (low + high)/2;
    }
    return pivot;
}

int BinarySearchTools::firstOccurance( int* list, int N, 
                                int value, bool first){
    int low(0);
    int high(N-1);
    int mid = (low+high)/2;
    int result(-1);
    while( low <= high){
        if (list[mid] == value){
            result = mid;
            if (first)
                high = mid -1;
            else
                low = mid+1;
        }
        else if (value > list[mid])
            low = mid +1;
        else
            high = mid -1;
        mid = (low + high)/2;
        //std::cout << value << " " << low << " " << high  << std::endl;
    }
    return result;

}

int BinarySearchTools::countDuplicates(  int* list, int N, int value){

    BinarySearchTools BStools;
    int first = BStools.firstOccurance( list, N, value, true );
    int last = BStools.firstOccurance( list, N, value, false );
    int numDuplicates(-1);
    if (first >=0  and last >= 0)
        numDuplicates = last - first + 1;

    return numDuplicates;
}


int BinarySearchTools::find( int* list, int N, int value){

    BinarySearchTools BStools;
    int pivot = BStools.findPivot( list, N );

    int low(0), high(N-1);
    int result(-1);

    if (list[pivot] == value){
        result = pivot;
        return result;
    }
    else if (value > list[pivot]  & value < list[high])
        low = pivot;

    else
        high = pivot;

    int mid = (low + high) / 2;
    while ( low <= high){
        if (list[mid] == value){
            result = mid;
            break;}
        else if( list[mid] < value  )
            low = mid+1;
        else
            high = mid - 1;
        mid = (low + high)/2;
    }
    return result;
}

void deleteDuplicates( int* list[], int N, int maxValue ){
    BinarySearchTools BStools;
    Stacksy S;
    int value(1);
    int counter(0);
    for(int value=1; value <= maxValue; value++){
        int first = BStools.firstOccurance( *list,N,value,true);
        int last = BStools.firstOccurance( *list,N,value,false);
        if (first >= 0){
            counter += 1;
            S.push( value );
        }
    }
    *list = new int[ counter];
    for(int i=0; i < counter; i++){
        std::cout << S.pop() << std::endl;
        (*list)[i] = S.pop();
    }
    //list = listWithoutDuplicates
    //return 0;
    //return &listWithoutDuplicates;
}

void PrintArray( int* list, int N ){
    printf("\n");
    printf( "This is the list:\n    ");
    for (int i=0; i< N; i++)
        printf( "%d ", list[i] );
    printf("\n");

}


int main(){
    int list[] = {1,3,3,4,5,5,6,7,7,7,7,8,10};
   
     
    BinarySearchTools BStools;

    PrintArray(list, 13);
    deleteDuplicates(&list, 13, 11);

    /*int pivotPosition = BStools.findPivot(list,9); 
    printf("\n");
    printf("Pivot is located at index %d.\n" , pivotPosition);

    int number(1);
    while( 1 ){
        printf("\nEnter a number in the list and"
                    " I will find it (enter 0 to quit): ");
        std::cin >> number;
        if (number==0) break;

        int position = BStools.find(list, 9, number);
        if (position == -1)
            printf("    The number %d is not in the list.\n", number);
        else
            printf("    The number %d is at index %d.\n",
                             number, position);
        }

    // fill with random numbers between 1 and 100
    //for (int i=0; i < N; i++)
        //randomNumbers[i] = rand()%100 +1;
    */
}




