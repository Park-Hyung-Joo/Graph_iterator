사용법
1. declaration:
MyGraph::Graph graphName(n);//n = number of vertex , directional graph
2. member function
    - insertEdge(int from, int to) // add edge (from,to) ( 1 <= from,to <= n )
    - source(int s = 1) // return Iterator pointing vertex number 's'
    - end()// return Iterator pointing after last vertex ( almost same with stl iterator end() )
    - Iterator begin() return Iterator pointing vertex number 1 ( same with source() )

3. Iterator:
    - Iterator_BFS: visit vertex in BFS order by ++ operator or Iterator_BSF::BFS()
    - Iterator_DFS: visit vertex in DFS order by ++ operator or Iterator_DSF::DFS()
    - Iterator_dijk: visit vertex in dijk order by ++ operator or Iterator_dijk::dijk()
    *notice: ++ operator, BFS(), DFS(), dijk() don't visit every node at once. Just visit next vertex in it's order 
example code

MyGraph::Graph g(5); // declare graph
    g.insertEdge(5,4); //insert edge 5->4
    g.insertEdge(5,2);
    g.insertEdge(1,2);
    g.insertEdge(3,4);
    g.insertEdge(3,1);
    
    //visit vertex in BFS order and print vertex number
    for(MyGraph::Graph::Iterator_BFS itr = g.source(3);itr!=g.end();++itr){
        std::cout<<(*itr).num <<' ';
    }
    std::cout<<std::endl;

    //visit vertex in DFS order and print vertex number
    for(MyGraph::Graph::Iterator_DFS itr = g.source(3);itr!=g.end();++itr){
        std::cout<<(*itr).num <<' ';
    }
    std::cout<<std::endl;

    //visit vertex in Dijkstra order and print vertex number
    for(MyGraph::Graph::Iterator_dijk itr(g,3);itr != g.end();++itr){
        std::cout<<(*itr).num << ' ';
    }
    std::cout<<std::endl;

2020 04 24
Iterator_dijk를 추가함
여담: Iterator_dijk는 main에서 itr = g.source() 가 통하지 않았다. 알고보니 iterator class에서 
Iterator_dijk형변환이 정의되지 않은 거었다. 이를 자손 class에서 부모 class를 이용한 생성자를 정의해 형변환을 대체하여 해결했다.

2020 04.18
헤더파일과 cpp파일로 분리. 내용을 동일

2020 04.17
Iterator, BFS, DFS 를 상속 개념을 이용해 수정
*opeartor의 return type을 Node& 로 수정 (*itr).num을 vertex number접근가능

2020.04.14
Node에 vertex number를 뜻하는 num추가
이유: main에서 DFS등을 print할 때 불편해서
문제점: (**itr).num이렇게 사용해야 한다.
수정계획: *operator를 바꿔본다, << operator를 따로 정의해본다. 