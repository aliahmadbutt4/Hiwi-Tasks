//
// Created by aab on 27.05.19.
//


#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <experimental/random>
#include <chrono>

// Vector type to hold key value pair

typedef std::vector<std::tuple<int , int>> KeyValueType;

// Vector type to hold the result

typedef std::vector<std::tuple<int , int, int>> ResultType;


// Utility function to print unordered_multimap

ResultType HashJoin (const KeyValueType& ds1, const KeyValueType& ds2){

// Vector object to store the result
    ResultType result;
    std::unordered_multimap<int ,int> DS1;
    for (auto it : ds1)
            DS1.emplace(std::get<0>(it), std::get<1>(it));

    for (auto it2 : ds2) {
        auto range = DS1.equal_range(std::get<0>(it2));
        if(range.first != range.second)
        for_each(range.first, range.second, [it2, &result](std::unordered_multimap<int, int>::value_type
         &x ){result.push_back(make_tuple(x.first, x.second, std::get<1>(it2) ) ); } );
    }

    return result;
}


// Data Generator
KeyValueType dataGenerator()
{
    KeyValueType data;

    int key =0 ,value = 0;

    for (int i = 0; i < 100; i++) {

        key = std::experimental::randint(1, 50);
        value = std::experimental::randint(1, 50);

        data.push_back(std::make_tuple(key,value));
    }

    return data;
}

int main() {

    // DataSet Generation
    KeyValueType dataSet1 = dataGenerator();
    KeyValueType dataSet2 = dataGenerator();

    // Applying Sort Merge Join and calculating the execution time

    auto start = std::chrono::high_resolution_clock::now();

    ResultType resultHJ = HashJoin(dataSet1,dataSet2);

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<< "Execution Time for Hash Join : " << diff << " microseconds" << std::endl;


    // Creating a file to hold the data set
    std::ofstream file1, file2, resultHJfile;

    // Opening the files

    file1.open ("Dataset1.csv");
    file2.open ("Dataset2.csv");
    resultHJfile.open("ResultNL.txt");


    // Writing into the csv file
    file1 << "Key , Value\n";
    file2 << "Key , Value\n";
    resultHJfile << "Key , Value , Value\n";


    //Writing into the files
    for  (auto it : dataSet1){
        file1 << std::get<0>(it) << " , " << std::get<1>(it) << std::endl;
    }


    for  (auto it : dataSet2){
        file2 << std::get<0>(it) << " , " << std::get<1>(it) << std::endl;
    }



    for (auto it : resultHJ){
        resultHJfile << std::get<0>(it)<< " , "<< std::get<1>(it) << " , "<< std::get<2>(it) << std::endl;
    }


    // closing the files
    file1.close();
    file2.close();
    resultHJfile.close();


    return 0;
}

