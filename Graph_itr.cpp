#include "Graph_itr.h"
namespace MyGraph{

Graph::Iterator_DFS& Graph::Iterator_DFS::operator=(const Iterator_DFS &itr){
    graph=itr.graph; current=itr.current; visited=itr.visited; stack=itr.stack;
    return *this;
}
Graph::Iterator_DFS::Iterator_DFS(Graph &g,int source): Iterator(g,source){
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
Graph::Iterator_BFS::Iterator_BFS(Graph &g,int source): Iterator(g,source){
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