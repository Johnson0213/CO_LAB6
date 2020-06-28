
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

struct cache_content {
    bool v;
    unsigned int tag;
};

const int K = 1024;

void simulate(int cacheSizeKB, int block_size, string cacheName)
{
    unsigned int cacheSizeByte = cacheSizeKB * K, tag, index, byteAddress;
    int accessNum = 0, missNum = 0, hitNum = 0;
    string fileName = cacheName + ".txt";

    int offset_bit = (int)log2(block_size);
    int index_bit = (int)log2(cacheSizeByte / block_size);
    // Question ?
    int line = cacheSizeByte >> (offset_bit);   //block number(line) = cache size / block size

    cache_content* cache = new cache_content[line];

    for (int j = 0; j < line; j++)
    {
        cache[j].v = false;
    }

    FILE *fp = fopen(fileName.c_str(), "r");  // FILE* fp = fopen("DCACHE.txt", "r");
    if (!fp) 
    {
        cerr << "test file open error!" << endl;
    }

    while (fscanf(fp, "%x", &byteAddress) != EOF)  //Define the type of input data : Hexadecimal Integer(%x)
    {
        accessNum++;
        index = (byteAddress >> offset_bit) & (line - 1);
        tag = byteAddress >> (index_bit + offset_bit);

        if (cache[index].v && cache[index].tag == tag)  //cache hit
        {
            cache[index].v = true;            
            hitNum++;
        }
        else                                            //cachemiss
        {
            cache[index].v = true;            
            cache[index].tag = tag;
            missNum++;
        }
    }

    fclose(fp);

    delete[] cache;

    cout << cacheName << endl;
    cout << "Cache_size:" << cacheSizeKB << "K" << endl;
    cout << "Block_size:" << block_size << endl;
    cout << "Hit rate: " << fixed << setprecision(2) << (hitNum / (double)accessNum * 100) << "%";
    cout << " (" << hitNum << "),  ";
    cout << "Miss rate: " << fixed << setprecision(2) << (missNum / (double)accessNum * 100) << "%";
    cout << " (" << missNum << ")"<<endl<<endl;
}


int main(void) 
{
    simulate(4, 16, "ICACHE");
    simulate(4, 32, "ICACHE");
    simulate(4, 64, "ICACHE");
    simulate(4, 128, "ICACHE");
    simulate(4, 256, "ICACHE");

    simulate(16, 16, "ICACHE");
    simulate(16, 32, "ICACHE");
    simulate(16, 64, "ICACHE");
    simulate(16, 128, "ICACHE");
    simulate(16, 256, "ICACHE");
    
    simulate(64, 16, "ICACHE");
    simulate(64, 32, "ICACHE");
    simulate(64, 64, "ICACHE");
    simulate(64, 128, "ICACHE");
    simulate(64, 256, "ICACHE");

    simulate(256, 16, "ICACHE");
    simulate(256, 32, "ICACHE");
    simulate(256, 64, "ICACHE");
    simulate(256, 128, "ICACHE");
    simulate(256, 256, "ICACHE");

    // simulate(4, 16, "DCACHE");
    // simulate(4, 32, "DCACHE");
    // simulate(4, 64, "DCACHE");
    // simulate(4, 128, "DCACHE");
    // simulate(4, 256, "DCACHE");

    // simulate(16, 16, "DCACHE");
    // simulate(16, 32, "DCACHE");
    // simulate(16, 64, "DCACHE");
    // simulate(16, 128, "DCACHE");
    // simulate(16, 256, "DCACHE");

    // simulate(64, 16, "DCACHE");
    // simulate(64, 32, "DCACHE");
    // simulate(64, 64, "DCACHE");
    // simulate(64, 128, "DCACHE");
    // simulate(64, 256, "DCACHE");

    // simulate(256, 16, "DCACHE");
    // simulate(256, 32, "DCACHE");
    // simulate(256, 64, "DCACHE");
    // simulate(256, 128, "DCACHE");
    // simulate(256, 256, "DCACHE");

    return 0;
}
