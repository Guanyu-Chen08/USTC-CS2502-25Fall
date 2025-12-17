#include "../include/dijkstra.h"
#include <iostream>
void dijkstra::ssp(int s)
{
    //TODO:实现以s为起始点的dijkstra算法求最短路径
    int i = 0, j = 0;
    for (i = 0; i < g.vertex_num; i++)
    {
        vertex[i].sure = 0;
        vertex[i].path = -1;
        vertex[i].dist = INT_MAX;
    }
    vertex[s].path = -1;
    vertex[s].dist = 0;
    for (i = 0; i < g.vertex_num; i++)
    {
        int target = -1;
        int min_dist = INT_MAX;
        for (j = 0; j < g.vertex_num; j++)
        {
            if (!vertex[j].sure && vertex[j].dist < min_dist)
            {
                min_dist = vertex[j].dist;
                target = j;
            }
        }
        if (target == -1) break;
        vertex[target].sure = 1;
        graph::Edge* p = g.vertex[target].head;
        while (p)
        {
            if (!vertex[p->adj].sure && vertex[target].dist + p->weight < vertex[p->adj].dist)
            {
                vertex[p->adj].dist = vertex[target].dist + p->weight;
                vertex[p->adj].path = target;
            }
            p = p->next;
        }
    }
    for (i = 0; i < g.vertex_num; i++)
    {
        std::cout << i << ": " << vertex[i].dist << std::endl;
        print(i);
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
void dijkstra::print(int u)
{
    //TODO:用于输出最短路径的辅助函数，可以使用递归实现
    if (vertex[u].path == -1)
    {
        std::cout<< u;
        return;
    }
    print(vertex[u].path);
    std::cout << " -> " << u;
}