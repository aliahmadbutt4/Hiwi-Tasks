#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <experimental/random>
#include <chrono>

/*********************************************************************************************************
 * Write a short data generator that creates 2x one million <key, value> pairs.
 * Key and Value should be two integers, keys randomly generated (between 0 and 100.000, with repetition).
 * Store both data sets into two vectors. Implement three functions that perform a regular database join
 * between both vectors based on equal keys (e.g. <5,128> from the first vector and <5,28> from the second
 * vector result into <5,128,28>):
 *      First function: Nested Loop (compare each tuple in the first vector with all tuples of the second
 *      vector)
 *
 *      Second function: Hash Join (insert all tuples of the first vector in a hash table, probe afterwards
 *      with all tuples of the second vector)
 *
 *      Third function: Sort-Merge Join (sort both vectors according to their key, afterwards, iterate over
 *      the elements for matches)
 *
 * Measure the execution time for all three functions (==join algorithms) to join the two million tuples.
 * Which implementation is the fastest? After measurement, store the join results in one .txt file each -
 * are they equal? use the standard library (e.g. std::sort, std::vector, std::unordered_multimap, rand(),
 * etc.).
 *
 *
 ***********************************************************************************************************/

using namespace std;

// Vector type to hold key value pair

typedef std::vector<std::tuple<int , int>> KeyValueType;

// Vector type to hold the result

typedef std::vector<std::tuple<int , int, int>> ResultType;

// Nested loop join
// It takes two data sets of key value pair(KeyValueType) and apply the nested loop join and returns ResultType


ResultType NestedLoopJoin ( const KeyValueType& ds1, const KeyValueType& ds2)
{
    ResultType result;
    try {

    for  (auto it1 : ds1){

    for (auto it2 : ds2){
        if ( std::get<0>(it1) == std::get<0>(it2)){
            result.push_back(std::make_tuple(std::get<0>(it1), std::get<1>(it1), std::get<1>(it2)));

        }
    }
    }
    } catch (const std::exception& e){
        std::cout << e.what();
    }
    return result;
}

/********************Hash join***********************************************************************************************
 * This function uses two data sets of "KeyValueType" the first data set 'ds1' is converted to unordered_multimap<int, int>
 * 'DS1' due to the property to unordered_multimap of storing elements by applying hash function. Next 'key' from ds2 is
 * used to locate the bucket in 'DS1' if found then each element inside the bucket is joined the 'ds2' key and resulting
 * into 'ResultType' container.
 ***************************************************************************************************************************/

ResultType HashJoin (const KeyValueType& ds1, const KeyValueType& ds2){

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


// Sort Merge Join
/* It takes two data sets of key value pair(KeyValueType) and apply sorting algorithm on each set and then iterate
 * both data sets once to merge the key value pair and return the ResultType. This implementation is missing co-grouping
 * Can be added later?
 */

ResultType SortMergeJoin (KeyValueType ds1 , KeyValueType ds2){

    ResultType result;
    std::sort(ds1.begin(), ds1.end());

    std::sort(ds2.begin(), ds2.end());

    auto iteratorDs1 = ds1.begin();
    auto iteratorDs2 = ds2.begin();
    while(iteratorDs1 != ds1.end() && iteratorDs2 != ds2.end() )
    {
         if (std::get<0>(*iteratorDs1) == std::get<0>(*iteratorDs2)){
             result.push_back(std::make_tuple(std::get<0>(*iteratorDs1), std::get<1>(*iteratorDs1), std::get<1>(*iteratorDs2)));
             iteratorDs1 ++;
         } else if (std::get<0>(*iteratorDs1) < std::get<0>(*iteratorDs2)){
             iteratorDs1 ++;
         }
         else if (std::get<0>(*iteratorDs1) > std::get<0>(*iteratorDs2))
            {
             iteratorDs2++;
            }

    }

    return result;
}



// Data Generator
KeyValueType dataGenerator()
{
    KeyValueType data;

    int key =0 ,value = 0;

    for (int i = 0; i < 1000000; i++) {

        key = std::experimental::randint(1, 1000000);
        value = std::experimental::randint(1, 1000000);

        data.push_back(std::make_tuple(key,value));
    }

    return data;
}

int main() {

    // DataSet Generation
    KeyValueType dataSet1 = dataGenerator();
    KeyValueType dataSet2 = dataGenerator();

/*********** Applying Sort Merge Join and calculating the execution time *************/

    auto start = std::chrono::high_resolution_clock::now();

    ResultType resultSMJoin = SortMergeJoin(dataSet1,dataSet2);

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<< "Execution Time for Sort-Merge Join : " << diff << " microseconds" << std::endl;

/**************     Applying Hash Join and Calculating Execution Time    **************/


    start = std::chrono::high_resolution_clock::now();

    ResultType resultHJ = HashJoin(dataSet1,dataSet2);

    end = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<< "Execution Time for Hash Join : " << diff << " microseconds" << std::endl;

/**************     Applying Nested Loop and Calculating the execution time     ***************/

    start = std::chrono::high_resolution_clock::now();

    ResultType resultNL = NestedLoopJoin(dataSet1,dataSet2);

    end = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<< "Execution Time for Nested Loop Join : " << diff << " microseconds" << std::endl;



    // Creating a file to hold the data set
    std::ofstream file1, file2, resultNLfile, resultHashJoinFile, resultSMJoinFile;

    // Opening the files

    file1.open ("Dataset1.csv");
    file2.open ("Dataset2.csv");
    resultNLfile.open("ResultNL.txt");
    resultSMJoinFile.open("ResultSMJoin.txt");
    resultHashJoinFile.open("ResultHashJoin.txt");

    // Writing into the csv file
    file1 << "Key , Value\n";
    file2 << "Key , Value\n";
    resultNLfile << "Key , Value , Value\n";
    resultSMJoinFile << "Key , Value , Value\n";
    resultHashJoinFile << "Key , Value , Value\n";

    //Writing into the files
    for  (auto it : dataSet1){
        file1 << std::get<0>(it) << " , " << std::get<1>(it) << endl;
    }


    for  (auto it : dataSet2){
        file2 << std::get<0>(it) << " , " << std::get<1>(it) << endl;
    }



    for (auto it : resultHJ){
        resultHashJoinFile << std::get<0>(it)<< " , "<< std::get<1>(it) << " , "<< std::get<2>(it) <<endl;
    }


    for (auto it : resultSMJoin){
        resultSMJoinFile << std::get<0>(it)<< " , "<< std::get<1>(it) << " , "<< std::get<2>(it) <<endl;
    }


    for (auto it : resultNL){
        resultNLfile << std::get<0>(it)<< " , "<< std::get<1>(it) << " , "<< std::get<2>(it) <<endl;
    }


    // closing the files
    file1.close();
    file2.close();
    resultNLfile.close();
    resultSMJoinFile.close();
    resultHashJoinFile.close();


    return 0;
}
