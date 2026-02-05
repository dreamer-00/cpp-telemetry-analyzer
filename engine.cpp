#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<chrono>
using namespace std;
using namespace std::chrono;
int main(){
    auto start = high_resolution_clock::now();
    ifstream dataFile("data.txt");
    vector<int> data;
    if(!dataFile.is_open()){
        cerr << "Error: Unable to open the file.\n";
        return 1;
    };
    int num;
    while(dataFile >> num){
        data.push_back(num);
    };
    dataFile.close();
    if(data.empty()){
        cout << "No data to analyze.\n";
        return 0;
    };
    //calculate mean
    double mean = 0.0;
    for(const int& value : data){
        mean += value;
    }        
    mean /= data.size();
    //calculate standard deviation
    double variance = 0.0;
    for(const int& value : data){
        variance += (value - mean) * (value - mean);
    }
    double stndev = sqrt(variance / data.size());
    cout << "The Volatility (Standard Deviation) of the data is: " << stndev << "\n";
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Processing took " << duration.count() << " milliseconds.\n";
    return 0;
}