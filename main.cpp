//Colden Gosselin
//COMP 271 HW_5
//Recieved assistance from CS Tutor Abdul

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Bubble_Sort(int A[], int n);
void Insertion_Sort(int A[], int n);
void Quick_Sort(int a[], int left, int right);
void Shell_Sort(int A[], int n);
void Merge_Sort(int A[], int low, int high);
int comparisons = 0;
int exchanges = 0;

void Bubble_Sort(int A[], int n)    //Bubble sorting
{
    int i, j, temp;
    for(i = 1; i < n; i++)      //# of passes
    {
        for(j = 0; j < n - 1; j++)      //j varies in the range of 0 to n - 1
        {
            comparisons++;         //comparison incremented
            if(A[j] > A[j + 1])     //compare the two numbers
            {
                temp = A[j];        //changes A[j] to A[j + 1]
                A[j] = A[j + 1];
                A[j + 1] = temp;
                exchanges++;        //exchanges incremented
            }
        }
    }
    cout << "Bubble Comparisons: " << comparisons << endl; //print output
    cout << "Bubble Exchanges: " << exchanges << endl; //print output
    cout << endl;
}

void Insertion_Sort(int A[], int n)     //Insertion sorting
{
    int i, j, element;
    for(i = 1; i < n; i++)
    {
        element = A[i];     //insert the ith element in array
        j = i;
        comparisons++;      //comparisons incremented
        while ((j > 0) && (A[j - 1] > element))
        {

            A[j] = A[j - 1];        //change elements
            j = j - 1;
            exchanges++;        //exchanges incremented
            comparisons++;      //comparisons incremented
        }
        A[j] = element;         //place element at jth position
    }
    cout << "Insertion Comparisons: " << comparisons << endl;
    cout << "Insertion Exchanges: " << exchanges << endl;
    cout << endl;
}

void swap(int &x, int &y)       //for Quick_Sort, passing by reference instead of value
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int partition(int a[], int left, int right, int pivotIndex)     //function for Quick_Sort
{
    int pivot = a[pivotIndex];      //create a pivot
    do
    {
        while (a[left] < pivot)
        {
            left++;     //left incremented
            comparisons++;      //comparisons incremented
        }
        comparisons++;
        while (a[right] > pivot)
        {
            right--;        //reight decreased by 1
            comparisons++;      //comparisons incremented
        }
        comparisons++;
        if (left < right && a[left] != a[right])
        {
            swap(a[left], a[right]);        // swap left and right
            exchanges++;        //exchanges incremented
        }
        else
        {
            return right;
        }
    }
    while (left < right);
    return right;
}

void Quick_Sort(int a[], int left, int right)
//Quick sorting will utilize the function above
{
    if (left < right)
    {
        int pivot = (left + right) / 2;
        int pivotNew = partition(a, left, right, pivot);
        Quick_Sort(a, left, pivotNew - 1);
        Quick_Sort(a, pivotNew + 1, right);
    }
}

void Shell_Sort(int A[], int n)     //Shell sorting
{
    int temp, gap, i;
    int swapped;
    gap = n/2;
    do
    {
        do
        {
            swapped = 0;
            for(i = 0; i < n - gap; i++)
            {
                comparisons++;      //comparisons incremented
                if(A[i] > A[i + gap])
                {
                    temp = A[i];
                    A[i] = A[i + gap];
                    A[i + gap] = temp;
                    swapped = 1;
                    exchanges++;    //exchanges incremented
                }
            }
        }
        while(swapped == 1);    //set swap=1
    }
    while((gap = gap/2) >= 1);
    cout << "Shell Comparisons: " << comparisons << endl;   //print output
    cout << "Shell Exchanges: " << exchanges << endl;       //print output
    cout << endl; //space
}

void merge(int A[], int low, int high, int mid)     //function for Merge_Sort
{
    int i, j, k, C[10000];
    i = low;          //index
    j = mid + 1;      //index
    k = 0;            //merge arrays A and B in array C
    while ((i <= mid) && (j <= high))
    {
        comparisons++;      //comparisons incremented
        if (A[i] < A[j])
        {
            C[k] = A[i++];
            exchanges++;        //exchanges incremented
        }
        else
        {
            C[k] = A[j++];
            exchanges++;        //exchanges incremented
        }
            k++;
    }
    while (i <= mid)
    {
        C[k++] = A[i++];
        exchanges++;        //exchanges incremented
    }
    while (j <= high)
    {
        C[k++] = A[j++];
        exchanges++;        //exchanges incremented
    }
    for (i = low, j = 0; i < high; i++, j++)
        //copy array C contents to array A
    {
        A[i] = C[j];
    }
}

void Merge_Sort(int A[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low + high)/2;
        Merge_Sort(A, low, mid);
        Merge_Sort(A, mid + 1, high);
        merge(A, low, high, mid);       //call the function
    }
    return;
}

bool arrayx(string apple, int *& pear)
{
    ifstream mainFile;      //input file stream
    mainFile.open(apple.c_str());     //c-style string and open the file that is inputted

    if(!mainFile.is_open())     //if the file cannot be opened
    {
        cout << "Cannot locate the file" << apple << endl;
        cout << "Incorrect. Check the file location \n";
        cout << endl;
        return false;
    }
    string cat;       //create a string called cat
    string dog = " ";     //create a string called dog
    while(mainFile.peek()!= EOF)
    {
        mainFile >> dog;      //read in string dog
        cat += dog + " ";
    }
    mainFile.clear();
    mainFile.close();       //close the file

    vector<string> blue;        //vector of string
    dog = "";
    for( int i = 0; i < cat.length();i++)
    {
        if (cat[i] == ' ')
        {
            blue.push_back(dog);
            dog = "";
        }
        else
        {
            dog += cat[i];
        }
    }
    if(pear != NULL)        //check to see if there is enough memory
    {
        delete pear;
    }
   pear = new int[blue.size()];
   for(int i = 0; i < blue.size(); i++)
    {
        pear[i]= atoi(blue[i].c_str());
    }
    return true;
}

int main(int argc, const char * argv[])
{
    int * numbers;
    string names[4];
    names[0] = "FewUnique.txt";
    names[1] = "NearlySorted.txt";
    names[2] = "Random.txt";
    names[3] = "Reversed.txt";

    for(int i = 0; i < 4; i++)
    {
        //NOTE: reading each algorithm one by one so the sorted array is reset
        //to unsorted array

       /*arrayx(names[i], numbers);
       Bubble_Sort(numbers, 10000);*/

       /*arrayx(names[i], numbers);
       Insertion_Sort(numbers, 10000);*/

       /*arrayx(names[i], numbers);
       Quick_Sort(numbers, 0, 9999);
       cout << "Quick Comparisons: " << comparisons << endl;    //console output
       cout << "Quick Exchanges: " << exchanges << endl;      //console output
       cout << endl;*/    //space

       /*array_y(just_names[i], Every_nums);
       Shell_Sort(Every_nums, 10000);*/

       arrayx(names[i], numbers);
       Merge_Sort(numbers, 0, 9999);
       cout << "Merge Comparisons: " << comparisons << endl;
       cout << "Merge Exchanges: " << exchanges << endl;
       cout << endl;
    return 0;
    }
}
