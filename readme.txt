2020 04.17
Iterator, BFS, DFS 를 상속 개념을 이용해 수정
*opeartor의 return type을 Node& 로 수정 (*itr).num을 vertex number접근가능
 
2020.04.14
Node에 vertex number를 뜻하는 num추가
이유: main에서 DFS등을 print할 때 불편해서
문제점: (**itr).num이렇게 사용해야 한다.
수정계획: *operator를 바꿔본다, << operator를 따로 정의해본다. 