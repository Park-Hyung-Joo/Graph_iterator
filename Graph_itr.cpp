#include "Graph_itr.h"
namespace MyGraph{

Graph::Iterator_DFS::Iterator_DFS(Graph &g,int source): Iterator(g,source){
    visited.resize(g.vertex.size());
    visited[source]=true;
    stack.push(std::make_pair(g.vertex.begin()+source, g.vertex[source].adj.begin()));
}

Graph::Iterator_DFS::Iterator_DFS(const Iterator &itr): Iterator(itr){
    int source = current - graph->vertex.begin();
    visited.resize(graph->vertex.size());
    visited[source]=true;
    stack.push(std::make_pair(current, graph->vertex[source].adj.begin()));
}

Graph::Iterator_DFS::Iterator_DFS(const Iterator_DFS &itr):Iterator(*(itr.graph),itr.current){
    stack=itr.stack;
    visited=itr.visited;
}

Graph::Iterator_DFS& Graph::Iterator_DFS::operator=(const Iterator_DFS &itr){
    graph = itr.graph; current = itr.current;
    stack = itr.stack; visited = itr.visited;
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
    for(; itr != (*current).adj.end(); ++itr){
        if(!visited[(*itr).first]){
            queue.push(graph->vertex.begin()+(*itr).first);
            visited[(*itr).first]=true;
        }
    }
}

Graph::Iterator_BFS::Iterator_BFS(const Iterator &itr): Iterator(itr){
    int source = current - graph->vertex.begin();
    visited.resize(graph->vertex.size());
    visited[source]=true;
    iter_edge itr_edge = (*current).adj.begin();
    for(; itr_edge != (*current).adj.end(); ++itr_edge){
        int to= (*itr_edge).first;
        if(!visited[to]){
            queue.push(graph->vertex.begin()+to);
            visited[to]=true;
        }
    }
}

Graph::Iterator_BFS::Iterator_BFS(const Iterator_BFS &itr): Iterator(*(itr.graph),itr.current){
    queue=itr.queue;
    visited=itr.visited;
}

Graph::Iterator_BFS& Graph::Iterator_BFS::operator=(const Iterator_BFS &itr){
    graph=itr.graph; current=itr.current; visited=itr.visited; queue=itr.queue;
    return *this;
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

Graph::Iterator_dijk::Iterator_dijk(Graph &g,int source): Iterator(g,source){
    dist.resize(graph->vertex.size(),INF);
    dist[source] = 0;
    iter_edge itr = (*current).adj.begin();
    for(; itr != (*current).adj.end(); ++itr){
        int to = (*itr).first , weight = (*itr).second;
        if(dist[source]+ weight < dist[to]){
            dist[to] = dist[source] + weight;
            pq.push(std::make_pair(dist[to],to));
        }
    }
}

Graph::Iterator_dijk::Iterator_dijk(const Iterator &itr): Iterator(itr){
    int source = current - graph->vertex.begin();
    dist.resize(graph->vertex.size(),INF);
    dist[source] = 0;
    iter_edge itr_edge = (*current).adj.begin();
    for(; itr_edge != (*current).adj.end(); ++itr_edge){
        int to = (*itr_edge).first , weight = (*itr_edge).second;
        if(dist[source]+ weight < dist[to]){
            dist[to] = dist[source] + weight;
            pq.push(std::make_pair(dist[to],to));
        }
    }
}

Graph::Iterator_dijk::Iterator_dijk(const Iterator_dijk &itr): Iterator(*itr.graph, itr.current){
    dist=itr.dist;
    pq=itr.pq;
}

void Graph::Iterator_dijk::dijk(){
    while(pq.top().first > dist[pq.top().second] && ! pq.empty())
        pq.pop();
    if(pq.empty()){current = graph->vertex.end(); return;}
    //pq.top.first == dist[pq.top.second] not <
    int from = pq.top().second;
    current = graph->vertex.begin() + from;
    pq.pop();
    iter_edge itr = (*current).adj.begin();
    for(; itr!= (*current).adj.end(); ++itr){
        int to = (*itr).first , weight = (*itr).second;
        if(dist[from]+ weight < dist[to]){
            dist[to] = dist[from] + weight;
            pq.push(std::make_pair(dist[to],to));
        }
    }
}

Graph::Iterator_dijk& Graph::Iterator_dijk::operator=(const Iterator_dijk &itr){
    graph=itr.graph; current=itr.current; dist=itr.dist; pq=itr.pq;
    return *this;
}
}//namespace end