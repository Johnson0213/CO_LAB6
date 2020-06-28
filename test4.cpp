#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <math.h>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#define K 1024
using namespace std;

void simulate(int cacheSizeKB, int blockSize, int Associate) {
    
    int cacheSizeByte = cacheSizeKB * K;
    int set_count = (int)(cacheSizeByte / blockSize / Associate);
    int miss_count = 0, hit_count = 0, access_count = 0;
    int byteAddress, tag, set_index;
    // Init LRU Size
    vector< list<int> > LRU_cache(set_count); 
    
    int offset_bit = (int)log2(blockSize);
    int set_index_bit = (int)log2(cacheSizeByte / blockSize / Associate);

    FILE *fp = fopen("LRU.txt", "r");
    if (!fp) 
    {
        cerr << "test file open error!" << endl;
    }

    while (fscanf(fp, "%x", &byteAddress) != EOF)  //Define the type of input data : Hexadecimal Integer(%x)
    {
        // bit extraction
        set_index = (byteAddress >> offset_bit) & (set_count - 1);
        tag = byteAddress >> (set_index_bit + offset_bit);

        list<int>::iterator findIter = find(LRU_cache[set_index].begin(), LRU_cache[set_index].end(), tag);
        
        access_count++;

        if (findIter != LRU_cache[set_index].end())  //cache hit
        {     
            hit_count++;
            LRU_cache[set_index].remove(tag);
            LRU_cache[set_index].push_back(tag);
        }
        else  //cachemiss
        {
            miss_count++;
            
            if(LRU_cache[set_index].size() == Associate) {
                LRU_cache[set_index].pop_front();            
            }
            
            LRU_cache[set_index].push_back(tag);

        }
    }

    fclose(fp);
    cout<< Associate << "-N Way" << endl;
    cout << "Cache_size:" << cacheSizeKB << "K" << endl;
    cout << "Block_size:" << blockSize << endl;
    cout << "Hit rate: " << fixed << setprecision(3) << (hit_count / (double)access_count * 100) << "%";
    cout << " (" << hit_count << "),  ";
    cout << "Miss rate: " << fixed << setprecision(3) << (miss_count / (double)access_count * 100) << "%";
    cout << " (" << miss_count << ")"<<endl<<endl;

    // ofstream outFile("Result.txt", ios::out);
    // outFile<< Associate << "-N Way" << endl;
    // outFile << "Cache_size:" << cacheSizeKB << "K" << endl;
    // outFile << "Block_size:" << blockSize << endl;
    // outFile << "Hit rate: " << fixed << setprecision(2) << (hit_count / (double)access_count * 100) << "%";
    // outFile << " (" << hit_count << "),  ";
    // outFile << "Miss rate: " << fixed << setprecision(2) << (miss_count / (double)access_count * 100) << "%";
    // outFile << " (" << miss_count << ")"<<endl<<endl;

}

int main(void) 
{
    simulate(1, 64, 1);
    simulate(1, 64, 2);
    simulate(1, 64, 4);
    simulate(1, 64, 8);
    // simulate(1, 64, 16);

    simulate(2, 64, 1);
    simulate(2, 64, 2);
    simulate(2, 64, 4);
    simulate(2, 64, 8);

    simulate(4, 64, 1);
    simulate(4, 64, 2);
    simulate(4, 64, 4);
    simulate(4, 64, 8);

    simulate(8, 64, 1);
    simulate(8, 64, 2);
    simulate(8, 64, 4);
    simulate(8, 64, 8);

    simulate(16, 64, 1);
    simulate(16, 64, 2);
    simulate(16, 64, 4);
    simulate(16, 64, 8);
    
    simulate(32, 64, 1);
    simulate(32, 64, 2);
    simulate(32, 64, 4);
    simulate(32, 64, 8);
    
    simulate(64, 64,1);
    simulate(64, 64,2);
    simulate(64, 64,4);
    simulate(64, 64,8);

    return 0;
}