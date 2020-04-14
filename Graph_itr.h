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
    
    struct Iterator{//나중에 상속 개념을 사용해 고쳐라
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
    };
    struct Iterator_DFS{
        Graph *graph;
        iter_node current;
        std::vector<bool> visited;
        std::stack< stackItem > stack;//pair<nodeNum,edge>
        Iterator_DFS(){};
        Iterator_DFS(Graph &g,int source);
        Iterator_DFS(const Iterator_DFS &itr):graph(itr.graph),current(itr.current){
            stack=itr.stack;
            visited=itr.visited;
        }
        void DFS();
        Iterator_DFS& operator=(const Iterator_DFS &itr);
        Iterator_DFS& operator++(){ DFS(); return *this; }//prefix
        Iterator_DFS operator++(int){ Iterator_DFS temp=*this; DFS(); return temp; }//postfix
        bool operator==(const Iterator_DFS &itr)const{ return this->current == itr.current; }
        bool operator==(const Iterator &itr)const{ return this->current == itr.current; }
        bool operator!=(const Iterator_DFS &itr)const{ return this->current != itr.current; }
        bool operator!=(const Iterator &itr)const{ return this->current != itr.current; }
        iter_node& operator*(){ return this->current; }
    };
    struct Iterator_BFS{
        Graph *graph;
        iter_node current;
        std::vector<bool> visited;
        std::queue< iter_node > queue;
        Iterator_BFS(){};
        Iterator_BFS(Graph &g,int source);
        Iterator_BFS(const Iterator_BFS &itr):graph(itr.graph),current(itr.current){
            queue=itr.queue;
            visited=itr.visited;
        }
        void BFS();
        Iterator_BFS& operator=(const Iterator_BFS &itr);
        Iterator_BFS& operator++(){ BFS(); return *this; }//prefix
        Iterator_BFS operator++(int){ Iterator_BFS temp=*this; BFS(); return temp; }//postfix
        bool operator==(const Iterator_BFS &itr)const{ return this->current == itr.current; }
        bool operator==(const Iterator &itr)const{ return this->current == itr.current; }
        bool operator!=(const Iterator_BFS &itr)const{ return this->current != itr.current; }
        bool operator!=(const Iterator &itr)const{ return this->current != itr.current; }
        iter_node& operator*(){ return this->current; }
    };
    friend Iterator_DFS;
    friend Iterator_BFS;
    Iterator source(int s){ Iterator temp(*this,s); return temp;}
    const Iterator end(){ Iterator itr(*this,vertex.end()); return itr; }
    const Iterator begin(){ Iterator itr(*this,vertex.begin()); return itr;}
};

Graph::Iterator_DFS& Graph::Iterator_DFS::operator=(const Iterator_DFS &itr){
    graph=itr.graph; current=itr.current; visited=itr.visited; stack=itr.stack;
    return *this;
}
Graph::Iterator_DFS::Iterator_DFS(Graph &g,int source):current(g.vertex.begin()+source){
    graph = &g;
    visited.resize(g.vertex.size());
    visited[source]=true;
    stack.push(std::make_pair(g.vertex.begin()+source, g.vertex[source].adj.begin()));
}
void Graph::Iterator_DFS::DFS(){
    visited[current - graph->vertex.begin()] = true;
    while(!stack.empty()){
        stackItem &temp=stack.top();
        while(temp.second != (*temp.first).adj.end() && visited[(*temp.second).first])
            ++(temp.second);
        if(temp.second == (*temp.first).adj.end()) stack.pop();
        else break;
    }
    if(stack.empty()){ current=graph->vertex.end(); return; }
            
    stackItem &temp=stack.top();
    current = graph->vertex.begin() + (*temp.second).first;
    stack.push( std::make_pair( current, (*current).adj.begin() ) );  
}
Graph::Iterator_BFS::Iterator_BFS(Graph &g,int source):graph(&g),current(g.vertex.begin()+source){
    visited.resize(g.vertex.size());
    visited[source]=true;
    iter_edge itr = (*current).adj.begin();
    for(;itr != (*current).adj.end();++itr){
        if(!visited[(*itr).first]){
            queue.push(graph->vertex.begin()+(*itr).first);
            visited[(*itr).first]=true;
        }
    }
}
void Graph::Iterator_BFS::BFS(){
    if(queue.empty()){ current = graph->vertex.end(); return;}
    current=queue.front();
    queue.pop();
    iter_edge itr=(*current).adj.begin();
    for(;itr != (*current).adj.end();++itr)
        if(!visited[(*itr).first]){
            queue.push(graph->vertex.begin()+(*itr).first);
            visited[(*itr).first]=true;
        }
}

Graph::Iterator_BFS& Graph::Iterator_BFS::operator=(const Iterator_BFS &itr){
    graph=itr.graph; current=itr.current; visited=itr.visited; queue=itr.queue;
    return *this;
}
}//namespace end