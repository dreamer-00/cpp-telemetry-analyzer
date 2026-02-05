#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <ctime>
#include <random>

using namespace std;
int main(){
    ofstream dataFile("data.txt");
    if(dataFile.is_open()){
        // generate random millions of numbers
        const int num_to_generate= 5000000;
        const int min_value=1;
        const int max_value=100;
        unsigned seed=chrono::system_clock::now().time_since_epoch().count();
        mt19937 gen(seed);
        uniform_int_distribution<> distribute(min_value, max_value);
        vector<int> random_numbers;
        random_numbers.reserve(num_to_generate);
        for(int i=0; i< num_to_generate; ++i){
            random_numbers.push_back(distribute(gen));
        }
        for(const int& num : random_numbers){
            dataFile << num <<"\n";
        }
        dataFile.close();
        cout << "Successfully saved 5,000,000 numbers.\n";
    }
    else{
        cerr << "Error: Unable to open the file.";
    }
    return 0;
}