#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
vector<int> RandomNumbers(int size);
vector<int> selectionSort(vector<int> vec);
vector<int> bubbleSort(vector<int> vec);
vector<int> bubbleSortEscapeClause(vector<int> vec);
void swap(vector<int> &vec, int i, int j);
void print(vector<double> &vec);
vector<double> timespec(int size);


int main(){
    // declaration
    int N;
    vector<int> unordered;
    ofstream timeFile;

    // initialization
    cin >> N;
    vector<double> times = timespec(N);
    timeFile.open("data.txt");

    for (int i = 0; i < 3; i++)
    {
        for (int j = i; j < times.size(); j= j+3)
        {
            if(j + 3 >= times.size()){
                timeFile << times[j] << endl;
            }else{
                timeFile << times[j]<<",";
            }
        }
    }
    
    return 0;
}

// find time for each algo
vector<double> timespec(int size){
    vector<double> v;
    vector<int> vec;
    double avarageA, avarageB, avarageC;
    int count = 5;
    for(int i = size; i <= 20000; i = i + 1000){
        long long timeA = 0.0;
        long long timeB = 0.0;
        long long timeC = 0.0;

        for (int j = 0; j < count; j++)
        {
            vec = RandomNumbers(i);
            auto start_A = std::chrono::high_resolution_clock::now();
            selectionSort(vec);
            auto end_A = std::chrono::high_resolution_clock::now();
            long long A = std::chrono::duration_cast<chrono::nanoseconds>(end_A- start_A).count();
            timeA += A;

            auto start_B = std::chrono::high_resolution_clock::now();
            bubbleSort(vec);
            auto end_B = std::chrono::high_resolution_clock::now();
            long long B = std::chrono::duration_cast<chrono::nanoseconds>(end_B- start_B).count();
            timeB += B;

            auto start_C = std::chrono::high_resolution_clock::now();
            bubbleSortEscapeClause(vec);
            auto end_C = std::chrono::high_resolution_clock::now();
            long long C = std::chrono::duration_cast<chrono::nanoseconds>(end_C - start_C).count();
            timeC += C;

        }
        avarageA = timeA / (double)count;
        avarageB = timeB / (double)count;
        avarageC = timeC / (double)count;

        v.push_back(avarageA); v.push_back(avarageB); v.push_back(avarageC);
    }
    return v; 
}

vector<int> RandomNumbers(int size){
    vector<int> vec;
    int numbers;

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<> uni(1,1000000);

    for (int i = 0; i < size; i++)
    {
        numbers = uni(rng);
        vec.push_back(numbers);
    }
    return vec;
}

// does selection sort
vector<int> selectionSort(vector<int> vec){
    for(int i = 0; i < vec.size() - 1; i++){
        int minimumPosition = i;
        for (int j = i + 1 ; j < vec.size(); j++)
        {
            if(vec[j] < vec[minimumPosition]){
                minimumPosition = j;
            }
        }
        swap(vec, i, minimumPosition);
    }
    return vec;
}

// does normal bubble sort without escape clause
vector<int> bubbleSort(vector<int> vec){
    for (int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec.size(); j++){
            if(vec[j] > vec[j + 1]){
                swap(vec, j, j + 1);
            }
        }
    }
    return vec;
}
// does bubble sort with escape clause
vector<int> bubbleSortEscapeClause(vector<int> vec){
    int k = vec.size();
    bool stillSorting = true;
    bool swapped;

    while(k >= 1 && stillSorting){
        swapped = false;
        for(int i = 0; i < vec.size(); i++) {
            if(vec[i] > vec[i + 1]){
                swap(vec, i, i + 1);
                swapped = true;
            }
        }
        if(swapped == false){
            stillSorting = false;
            break;
        }
        else{
            k = k + k;
        }
    }
    return vec;
}

// swaps two elements given its index in a vector
void swap(vector<int> &vec, int i, int j){
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

// prints a vector 
void print(vector<double> &vec){
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i] << " ";
    }
}