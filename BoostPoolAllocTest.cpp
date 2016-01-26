#include "stdafx.h"
#include <boost/pool/pool_alloc.hpp>
#include <iostream>
#include <list>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include<math.h>

using std::vector;
using std::multiset;
using std::list;
using boost::pool_allocator;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int testVectorSize = 10000;
    time_t now1, end1;
    list<int, pool_allocator<int> > pool_allocator_list;
    list<int, std::allocator<int> > standart_allocator_list;
    vector<int> binary;
    vector<int*> pointer1;
    vector<int*> pointer2;
    multiset<int> first, second;
    pool_allocator<int> palloc;

    binary.resize(testVectorSize);
    pointer2.resize(testVectorSize);
    pointer1.resize(testVectorSize);

    cin >> testVectorSize;

    for (auto i = 1; i < 3*testVectorSize; i++)
    {
        pool_allocator_list.push_back(i);
        standart_allocator_list.push_back(i);
    }
    time(&now1);
    for (auto i = 1; i < testVectorSize; i++)
    {
        pool_allocator_list.remove(2*i);
    }

    for (auto i = 1; i < testVectorSize; i++)
    {
        pool_allocator_list.push_back(2*i);
    }
    cout << "list with pool_allocation time = ";
    time(&end1);
    cout << -difftime(now1, end1) << " s" << endl;

    time(&now1);
    for (auto i = 1; i < testVectorSize; i++)
    {
        standart_allocator_list.remove(2 * i);
    }

    for (auto i = 1; i < testVectorSize; i++)
    {
        standart_allocator_list.push_back(2*i);
    }

    time(&end1);
    cout << "list with standart allocation time = ";
    cout << -difftime(now1, end1) << " s" << endl;

    for (int i = 0; i < testVectorSize; i++)
    {
        binary[i] = (i*i*i*i*i %3)%2;
    }
    time(&now1);
    for (int i = 0; i < testVectorSize; i++)
    {
        if (binary[i])
        {
            pointer1[i] = palloc.allocate(sizeof(int));
            first.insert(i);
        }
        else
        {
            if (!first.empty())
            {
                int point;
                for (int j = 0; j < i; j++)
                {
                    if (first.count(j))
                        point = j;
                }
                palloc.deallocate(pointer1[point], sizeof(int));
                first.erase(point);
            }
        }
    }
    time(&end1);
    cout << "pointers to int random vector witn pool allocator time = " << difftime(end1, now1) << endl;
    time(&now1);
    for (int i = 0; i < testVectorSize; i++)
    {
        if (binary[i])
        {
            pointer2[i] = new int;
            second.insert(i);
        }
        else
        {
            if (!second.empty())
            {
                int point;
                for (int j = 0; j < i; j++)
                {
                    if (second.count(j))
                        point = j;
                }
                palloc.deallocate(pointer2[point], sizeof(int));
                second.erase(point);
            }
        }
    }
    time(&end1);
    cout << "pointers to int random vector witn new/delete allocator time = " << difftime(end1, now1) << endl;
    return 0;
}
