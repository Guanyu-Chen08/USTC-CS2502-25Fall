#include "../include/graph.h"
#include<iostream>

void graph::init(int u[],int v[],int w[])
{
    //TODO:完成邻接表存储图
    for (int i = 0; i < edge_num; i++)
    {
        Edge* new_edge = new Edge();
        new_edge->adj = v[i];
        new_edge->weight = w[i];
        new_edge->next = vertex[u[i]].head;
        vertex[u[i]].head = new_edge;
    }
}
void graph::dfs(int s)
{
    //TODO:完成图的深度优先遍历，输出顶点编号
    if (vertex[s].visited) return;
    std::cout << s << " ";
    vertex[s].visited = 1;
    Edge* current = vertex[s].head;
    while (current)
    {
        dfs(current->adj);
        current = current->next;
    }
}