https://leetcode.com/discuss/post/8346110/how-to-solve-any-backtracking-problem-st-bel5/

#백트래킹 기본 구조
void backtrack(state, choices) {
    if (goal reached) {
        result.push_back(state);   // record the solution
        return;
    }

    for (each valid choice) {
        make choice;        // add to state
        backtrack(...);     // explore deeper
        undo choice;        // restore state — this is the backtrack
    }
}

순서가 중요한가? 
예 -> Permutation
아니오 -> Subset/Combination

모든 결과를 구하는가?
예 -> Subset
아니오 -> Combination (조건 만족하는 것)

선택 시 지켜야하는 규칙?
예 -> Constrain Satisfaction (N-Queens)


1. 백트래킹 기본 구조 작성 -> subset
2. 순서 고려 -> used 배열 사용
3. 특정 조건 만족(합이 5) -> target을 만족할 때 result.push_back
4. 만약 Combination에서 숫자가 재사용 가능하면 다음 함수에 i 전달, 불가능하면 i+1전달
5. N-Queens, Sudoku라면 현재 상태 유효를 기준으로 
Yes -> 재귀
No -> 가지치기

                    백트래킹
                       │
             ┌─────────┴─────────┐
             │                   │
          순서 중요?            순서 중요 X
             │                   │
            YES              ┌───┴────┐
             │               │        │
       Permutation        전부 필요?  조건 필요?
                             │        │
                            YES      YES
                             │        │
                          Subset  Combination
                                     
                    + 별도로
                 강한 제약조건이
                 있으면 Constraint


① cur에 무엇을 넣는가?
숫자?
문자?
문자열 조각?
Queen?


② 다음 재귀에서 어디부터 볼 것인가?
i
i + 1
start
0


③ 이미 사용한 것을 다시 써도 되는가?
YES → i
NO  → i+1 / used


④ 같은 결과를 중복해서 만들 가능성이 있는가?
sort
+
skip duplicate


⑤ 언제 res.push_back() 하는가?
모든 상태가 답
→ 매 level

완성된 상태만 답
→ base case

조건을 만족한 상태만 답
→ 조건 충족 시



"이 상태/선택이 앞으로 유효한 답을 만들 가능성이 있는가?"
                 현재 상태
              /      |      \
            A        B        C
          후보      후보      후보

continue
"너(A)만 안 돼."
→ 다음 후보 B로

return
"여기까지 온 경로 자체가 끝났어."
→ 부모로

break
"너(A)부터 뒤에 있는 애들도 전부 안 돼."
→ for문 끝