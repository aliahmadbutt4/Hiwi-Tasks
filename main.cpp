#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <experimental/random>


/* Write a short data generator that creates 2x one million <key, value> pairs.
 * Key and Value should be two integers, keys randomly generated (between 0 and 100.000, with repetition).
 * Store both data sets into two vectors. Implement three functions that perform a regular database join between both
 * vectors based on equal keys (e.g. <5,128> from the first vector and <5,28> from the second vector
 * result into <5,128,28>):
 *      First function: Nested Loop (compare each tuple in the first vector with all tuples of the second vector)
 *
 *      Second function: Hash Join (insert all tuples of the first vector in a hash table, probe afterwards with all
 *      tuples of the second vector)
 *
 *      Third function: Sort-Merge Join (sort both vectors according to their key, afterwards, iterate over the elements
 *      for matches)
 *
 * Measure the execution time for all three functions (==join algorithms) to join the two million tuples.
 * Which implementation is the fastest? After measurement, store the join results in one .txt file each - are they equal?
 *
 * use the standard library (e.g. std::sort, std::vector, std::unordered_multimap, rand(), etc.).
 *
 *
 */

using namespace std;

// Vector type to hold key value pair
typedef std::vector<std::tuple<int , int>> KeyValueType;

//
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

// Creating a file to hold the data set
    std::ofstream file1, file2;

    // Opening the files

    file1.open ("Dataset1.csv");
    file2.open ("Dataset2.csv");

    // Writing into the csv file
    file1 << "Key , Value\n";
    file2 << "Key , Value\n";

    //
    for  (auto it : dataSet1){
        file1 << std::get<0>(it) << " , " << std::get<1>(it) << endl;
    }

    for  (auto it : dataSet2){
        file2 << std::get<0>(it) << " , " << std::get<1>(it) << endl;
    }

    // closing the files
    file1.close();
    file2.close();
    
    return 0;
}
