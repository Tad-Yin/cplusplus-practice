/*
 * =====================================================================================
 *
 *       Filename:  toplogical.cpp
 *
 *    Description:  graph algorithm without design pattern
 *
 *        Version:  1.0
 *        Created:  2018年06月15日 10时03分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <fstream>
const int MAX = 10000 + 5;

int num;
int head[MAX];
struct edge{
    int v, dis;
    int next;
}e[MAX];
int length = 0;
int in[MAX];

void init(){
    length = 0;
    memset(head, -1, sizeof(head));
    memset(in, 0, sizeof(in));
}

void add_edge(int _u, int _v, int _dis){
    e[length].v = _v;
    e[length].dis = _dis;
    e[length].next = head[_u];
    head[_u] = length++;
    in[_v]++;
}

void toplogical(){
    std::queue<int> zero_in;
    for(int i = 0; i < num; i++){
        if(in[i] == 0) zero_in.push(i);
    }
    while(!zero_in.empty()){
        int temp = zero_in.front();
        zero_in.pop();
        std::cout <<temp << " ";
        for(int id = head[temp]; id != -1; id = e[id].next){
            int v = e[id].v;
            in[v]--;
            //std::cout << v << " " <<in[v] << "\n";
            if(in[v] == 0) zero_in.push(v);
        }
    }
    std::cout << "\n";
}

int main(){
    int x, y, z;
    std::ifstream tin("in3.txt");
    init();
    tin >> num;
    while(tin >> x >> y >> z){
        add_edge(x, y, z);
    }
    toplogical();
}
