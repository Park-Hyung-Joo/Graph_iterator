#include<iostream>
#include<queue>
#include<stack>
#include<list>
namespace MyGraph{
class Graph{
    struct Node{
        int num;
        std::list< std::pair<int, int> > adj;
    };
    std::vector<Node> vertex;
public:
    using iter_edge = std::list< std::pair<int, int> >::iterator;
    using iter_node = std::vector<Node>::iterator;
    using stackItem = std::pair<iter_node, iter_edge>;

    Graph(int V){ vertex.resize(V+1); for(int i=1;i<=V;i++) vertex[i].num = i;}
    void insertEdge(int from, int to, int weight=1){ vertex[from].adj.push_back(std::make_pair(to,weight)); }
    struct Iterator;
    struct Iterator_DFS;
    struct Iterator_BFS;
    
    struct Iterator{
        Graph *graph;
        iter_node current;
        Iterator(){};
        Iterator(Graph &g,int source){
            graph = &g;  current = g.vertex.begin()+source;
        }
        Iterator(Graph &g,iter_node start){
            graph = &g;  current = start;
        }
        operator Iterator_BFS(){
            Iterator_BFS temp(*graph,current - graph->vertex.begin());
            return temp;
        }
        operator Iterator_DFS(){
            Iterator_DFS temp(*graph,current - graph->vertex.begin());
            return temp;
        }
        Node& operator*(){return *current;}
        bool operator==(const Iterator &itr)const{ return current == itr.current; }
        bool operator!=(const Iterator &itr)const{ return current != itr.current; }
    };
    struct Iterator_DFS: public Iterator{
        std::vector<bool> visited;
        std::stack< stackItem > stack;//pair<nodeNum,edge>
        Iterator_DFS(){};
        Iterator_DFS(Graph &g,int source);
        Iterator_DFS(const Iterator_DFS &itr){
            graph=itr.graph;
            current=itr.current;
            stack=itr.stack;
            visited=itr.visited;
        }
        void DFS();
        Iterator_DFS& operator=(const Iterator_DFS &itr);
        Iterator_DFS& operator++(){ DFS(); return *this; }//prefix
        Iterator_DFS operator++(int){ Iterator_DFS temp=*this; DFS(); return temp; }//postfix
    };
    struct Iterator_BFS: public Iterator{
        std::vector<bool> visited;
        std::queue< iter_node > queue;
        Iterator_BFS(){};
        Iterator_BFS(Graph &g,int source);
        Iterator_BFS(const Iterator_BFS &itr): Iterator(*(itr.graph),itr.current){
            queue=itr.queue;
            visited=itr.visited;
        }
        void BFS();
        Iterator_BFS& operator=(const Iterator_BFS &itr);
        Iterator_BFS& operator++(){ BFS(); return *this; }//prefix
        Iterator_BFS operator++(int){ Iterator_BFS temp=*this; BFS(); return temp; }//postfix
    };
    friend Iterator_DFS;
    friend Iterator_BFS;
    Iterator source(int s){ Iterator temp(*this,s); return temp;}
    const Iterator end(){ Iterator itr(*this,vertex.end()); return itr; }
    const Iterator begin(){ Iterator itr(*this,vertex.begin()); return itr;}
};
}//namespace end