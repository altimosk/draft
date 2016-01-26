#include "stdafx.h"
#include <boost/pool/pool_alloc.hpp>
#include <iostream>
#include <list>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <set>

using std::multiset;
using std::list;
using boost::pool_allocator;
using std::cin;
using std::cout;
using std::endl;

const int m = 100000;

int main()
{
    /*time_t now1, end1, now2, end2;

    list<int, pool_allocator<int> > pool_allocator_list;
    list<int, std::allocator<int> > standart_allocator_list;


    for (auto i = 1; i < 3*m; i++)
    {
        pool_allocator_list.push_back(i);
        standart_allocator_list.push_back(i);
    }


    time(&now1);
    for (auto i = 1; i < m; i++)
    {
        pool_allocator_list.remove(2*i);
    }

    for (auto i = 1; i < m; i++)
    {
        pool_allocator_list.push_back(2*i);
    }
     
    time(&end1);
    cout << now1 << " s" << endl;
    cout << end1 << " s" << endl;
    cout << -difftime(now1, end1) << " s" << endl;

    time(&now2);
    for (auto i = 1; i < m; i++)
    {
        standart_allocator_list.remove(2 * i);
    }

    for (auto i = 1; i < m; i++)
    {
        standart_allocator_list.push_back(2*i);
    }

    time(&end2);
    cout << now2 << " s" << endl;
    cout << end2 << " s" << endl;
    cout << -difftime(now2, end2) << " s" << endl;

    
    
    
    
    srand(time(NULL));
    time(&now1);
    for (auto i = 1; i < m; i++)
    {
        pool_allocator_list.remove(rand() %m + 1);
    }

    for (auto i = 1; i < m; i++)
    {
        pool_allocator_list.push_back(rand() % m + 1);
    }

    time(&end1);
    cout << now1 << " s" << endl;
    cout << end1 << " s" << endl;
    cout << -difftime(now1, end1) << " s" << endl;

    time(&now2);
    for (auto i = 1; i < m; i++)
    {
        standart_allocator_list.remove(rand() % m + 1);
    }

    for (auto i = 1; i < m; i++)
    {
        standart_allocator_list.push_back(rand() % m + 1);
    }

    time(&end2);
    cout << now2 << " s" << endl;
    cout << end2 << " s" << endl;
    cout << -difftime(now2, end2) << " s" << endl;*/
    multiset<int> first,second;
    int binary[m];
    int* pointer1[m];
    int* pointer2[m];
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        binary[i] = rand() % 2;
    }
    time_t now1, end1;
    pool_allocator<int> palloc;
    time(&now1);
    for (int i = 0; i < m; i++)
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
    cout << difftime(end1, now1) << endl;
    /*time(&now1);
    for (int i = 0; i < m; i++)
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
    cout << difftime(end1, now1) << endl;*/
    return 0;
}
