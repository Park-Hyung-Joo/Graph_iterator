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