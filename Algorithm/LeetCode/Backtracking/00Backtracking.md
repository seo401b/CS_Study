https://leetcode.com/discuss/post/8346110/how-to-solve-any-backtracking-problem-st-bel5/


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