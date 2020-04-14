2020.04.14
Node에 vertex number를 뜻하는 num추가
이유: main에서 DFS등을 print할 때 불편해서
문제점: (**itr).num이렇게 사용해야 한다.
수정계획: *operator를 바꿔본다, << operator를 따로 정의해본다. 