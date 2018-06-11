#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <memory>
#include <fstream>
#include <cassert>

class Graph {
public:
    struct Edge {
        Edge(int _u, int _v, int _dis)
            :u(_u), v(_v), dis(_dis), next(nullptr) {
            }
        int u;
        int v;
        int dis;
        Edge* next;
    };

    virtual ~Graph() {
        for (int i = 0; i < edges.size(); i++) delete edges[i];
        edges.clear();
        head.clear();
    }

    std::vector<Edge*> edges;
    std::unordered_map<int, Edge*> head;

    void add_edge(int _u, int _v, int _dis) {
        if (head.find(_u) == head.end()) head.insert(HeadType::value_type(_u, nullptr));
        if (head.find(_v) == head.end()) head.insert(HeadType::value_type(_v, nullptr));
        add_edge_derived(_u, _v, _dis);
    }
protected:
    using HeadType = std::unordered_map<int, Edge*>;
    virtual void add_edge_derived(int _u, int _v, int _dis) = 0;
    void add_edge_impl(int _u, int _v, int _dis) {
        Edge* newNode = new Edge(_u, _v, _dis);
        newNode->next = head[_u];
        head[_u] = newNode;
        edges.push_back(newNode);
    }
    void deep_clone(const Graph& gra) {
        for (int i = 0; i < edges.size(); i++) delete edges[i];
        edges.clear();
        head.clear();
        for (auto i = 0; i < gra.edges.size(); i++) {
            add_edge(gra.edges[i]->u, gra.edges[i]->v, gra.edges[i]->dis);
        }
        //std::cout << "1\n";
    }
};

class DirectedGraph : public Graph {
public:
    DirectedGraph() = default;
    DirectedGraph(const DirectedGraph& gra) {
        *this = gra;
    }
    DirectedGraph(DirectedGraph&& gra) {
        *this = gra;
    }
    DirectedGraph& operator=(const DirectedGraph& gra) {
        this->deep_clone(gra);
        return *this;
    }
    DirectedGraph& operator=(DirectedGraph&& gra) {
        edges = std::move(gra.edges);
        head = std::move(gra.head);
        return *this;
    }
    virtual ~DirectedGraph() {
    }
protected:
    virtual void add_edge_derived(int _u, int _v, int _dis) {
        add_edge_impl(_u, _v, _dis);
    }
};

class UndirectedGraph : public Graph {
public:
    UndirectedGraph() = default;
    UndirectedGraph(const UndirectedGraph& gra) {
        *this = gra;
    }
    UndirectedGraph(UndirectedGraph&& gra) {
        *this = gra;
    }
    UndirectedGraph& operator=(const UndirectedGraph& gra) {
        this->deep_clone(gra);
        return *this;
    }
    UndirectedGraph& operator=(UndirectedGraph&& gra) {
        edges = std::move(gra.edges);
        head = std::move(gra.head);
        return *this;
    }
    virtual ~UndirectedGraph() {
    }
protected:
    virtual void add_edge_derived(int _u, int _v, int _dis) {
        add_edge_impl(_u, _v, _dis);
        add_edge_impl(_v, _u, _dis);
    }
};

class MinPath {
public:
    virtual int algorithm(int, int) = 0;
protected:
    std::shared_ptr<Graph> gra;
    struct MinHeap{
        MinHeap(int _v = 0, int _dis = 0):id(_v), dis(_dis) {}
        int id;
        int dis;
        friend bool operator<(const MinHeap& a, const MinHeap& b){
            return a.dis > b.dis;
        }
    };
};

class DijstraMinPath : public MinPath {
public:
    DijstraMinPath(std::shared_ptr<Graph> _gra){
        gra = _gra;
    }
    virtual int algorithm(int, int);
protected:
};

class SpfaMinPath : public MinPath {
public:
    SpfaMinPath(std::shared_ptr<Graph> _gra){
        gra = _gra;
    }
    virtual int algorithm(int, int);
protected:
};

int DijstraMinPath::algorithm(int start, int end) {
    std::unordered_map<int, int> dis;
    std::priority_queue<MinHeap> mh;
    mh.push(MinHeap(start, 0));
    dis.insert(std::unordered_map<int, int>::value_type(start, 0));
    while(!mh.empty()){
        MinHeap temp = mh.top();
        mh.pop();
        int u = temp.id;
        //std::cout << temp.id << " " << temp.dis << "\n";
        if(dis.find(u) != dis.end()){
            if(temp.dis > dis[u]) continue;
        }
        for(Graph::Edge* it = gra->head[u]; it != nullptr; it = it->next){
            int v = it->v;
            //std::cout<<"from " << u << " " << v << "\n"; 
            if(dis.find(v) == dis.end()){
                dis[v] = dis[u] + it->dis;
                mh.push(MinHeap(v, dis[v]));
            }
            else {
                if(dis[v] > dis[u] + it->dis){
                    dis[v] = dis[u] + it->dis;
                    mh.push(MinHeap(v, dis[v]));
                }
            }
        }
    }

    if(dis.find(end) == dis.end()) return -1;
    else return dis[end];
}

int SpfaMinPath::algorithm(int start, int end){
    std::unordered_map<int, int> dis;
    std::unordered_map<int, bool> in_queue;
    std::queue<int> mh;
    in_queue[start] = true;
    dis[start] = 0;
    mh.push(start);
    while(!mh.empty()){
        int u = mh.front();
        mh.pop();
        in_queue[u] = false;
        for(Graph::Edge* it = gra->head[u]; it != nullptr; it = it->next){
            int v = it->v;
            if(dis.find(v) == dis.end()){
                dis[v] = dis[u] + it->dis;
                mh.push(v);
                in_queue[v] = true;
            }
            else if(dis[u] + it->dis < dis[v]){
                dis[v] = dis[u] + it->dis;
                if(!in_queue[v]){
                    in_queue[v] = true;
                    mh.push(v);
                }
            }

        }
    }
    if(dis.find(end)==dis.end()) return -1;
    else return dis[end];
}

int main() {
    int x, y, z;
    int len;
    std::ifstream in("in2.txt");
    DirectedGraph dirg;

    in >> len;
    while (in >> x >> y >> z) {
        dirg.add_edge(x, y, z);
    }
    in.close();
    // Graph Copy constructor and assignment test
    for (int i = 0; i < 1000; i++) {
        DirectedGraph dirg2(std::move(dirg));
        dirg = std::move(dirg2);
    }
    std::cout << "Graph move constructor and move assignment pass" << "\n";
    for (int i = 0; i < 1000; i++) {
        DirectedGraph dirg2(dirg);
        dirg = dirg2;
    }
    std::cout << "Graph copy constructor and copy assignment pass" << "\n";


    std::ifstream in2("in.txt");
    //min path
    in2 >> len;
    auto sh_dirg = std::make_shared<DirectedGraph>();
    while (in2 >> x >> y >>z) {
        sh_dirg->add_edge(x, y, z);
    }
    MinPath* dij = new DijstraMinPath(sh_dirg);
    //std::cout << dij->algorithm(1, 8) << "\n";
    //std::cout << dij->algorithm(1, -1) << "\n";
    assert(dij->algorithm(1, 8) == 7);
    assert(dij->algorithm(1, -1) == -1);
    std::cout << "min_path dijstra algorithm pass\n";

    MinPath* spfa = new SpfaMinPath(sh_dirg);
    //std::cout << spfa->algorithm(1, 8) << "\n";
    //std::cout << spfa->algorithm(1, 8) << "\n";
    assert(spfa->algorithm(1, 8) == 7);
    assert(spfa->algorithm(1, -1) == -1);
    std::cout << "min_path spfa algorithm pass\n";
    return 0;
}
