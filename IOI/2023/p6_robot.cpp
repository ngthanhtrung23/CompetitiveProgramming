// Solution write-up: https://www.facebook.com/code.cung.rr/posts/pfbid02xdPmREpwvVvgHRV1c2YzowHSCYX6vbAwS7AzjyGkxyuYfnTgyzBNkGvCNgtTdykGl
// Solution with Z=5: https://codeforces.com/blog/entry/120252

#include "robot.h"
#include <bits/stdc++.h>
using namespace std;
 
#define FOR(i,a,b) for(int i=(a),_##i##_b=(b); i<=_##i##_b; i++)
#define SET(color, action) { set_instruction(state, color, action); continue; }

void subtask1() {
    const int BLUE = 1;

    FOR(cur,0,1) FOR(west,-2,1) FOR(south,-2,1) FOR(east,-2,1) FOR(north,-2,1) {
        vector<int> state {cur, west, south, east, north};
        if (south == -2 && east == -2) {
            // Reach (R, C) -> terminal
            set_instruction(state, BLUE, 'T');
        } else if (east == -2) {
            // We reached rightmost column -> move south
            set_instruction(state, BLUE, 'S');
        } else {
            // We are in top row -> move east
            set_instruction(state, BLUE, 'E');
        }
    }
}

void subtask2() {
    const int BLUE = 1;
    const int RED = 2;

    FOR(cur,0,1) FOR(west,-2,1) FOR(south,-2,1) FOR(east,-2,1) FOR(north,-2,1) {
        vector<int> state {cur, west, south, east, north};

        // Final state -> terminate
        if (south == -2 && east == -2) {
            set_instruction(state, 1, 'T');

        // Otherwise we just move when possible
        } else if (east == 0) {
            set_instruction(state, 1, 'E');
        } else if (south == 0) {
            set_instruction(state, 1, 'S');
        } else if (north == 0) {
            set_instruction(state, 1, 'N');
        }
    }
}

void subtask3_50() {
    FOR(cur,0,2) FOR(west,-2,2) FOR(south,-2,2) FOR(east,-2,2) FOR(north,-2,2) {
        vector<int> state {cur, west, south, east, north};
        // Final state
        if (south == -2 && east == -2) SET(1, 'T');

        // Try moving in any direction
        if (east == 0) SET(1, 'E');
        if (south == 0) SET(1, 'S');
        if (north == 0) SET(1, 'N');
        if (west == 0) SET(1, 'W');

        // We cannot move. Backtrack
        if (north == 1) SET(2, 'N');
        if (west == 1) SET(2, 'W');
        if (south == 1) SET(2, 'S');
        if (east == 1) SET(2, 'E');
    }
}

void subtask4_50() {
    FOR(cur,0,2) FOR(west,-2,2) FOR(south,-2,2) FOR(east,-2,2) FOR(north,-2,2) {
        vector<int> state {cur, west, south, east, north};
        // Final state
        if (south == -2 && east == -2) SET(1, 'T');

        // Try moving in any direction
        if (east == 0) SET(1, 'E');
        if (south == 0) SET(1, 'S');

        // We cannot move. Go back
        if (north == 1) SET(2, 'N');
        if (west == 1) SET(2, 'W');
    }
}

void subtask3() {
    const int MAX_COLOR = 10;
 
    const int BOUNDARY = -2;
    const int BLOCKED = -1;
 
    const int FINAL = 1;
 
    const int TRY_EAST = 2;
    const int TRY_SOUTH = 3;
    const int TRY_WEST = 4;
    const int TRY_NORTH = 5;
 
    const int BACKTRACK = 10;
 
#define SET(color, action) { set_instruction(state, color, action); continue; }
 
    FOR(cur,0,MAX_COLOR) FOR(west,-2,MAX_COLOR) FOR(south,-2,MAX_COLOR) FOR(east,-2,MAX_COLOR) FOR(north,-2,MAX_COLOR) {
        vector<int> state {cur, west, south, east, north};
 
        // Found target
        if ((south == BOUNDARY && east == BOUNDARY) || west == FINAL || south == FINAL || east == FINAL || north == FINAL) {
            if (north > 1) SET(FINAL, 'N');
            if (west > 1) SET(FINAL, 'W');
            if (south > 1) SET(FINAL, 'S');
            if (east > 1) SET(FINAL, 'E');
            SET(FINAL, 'T');
        }
 
        if (cur == 0) SET(TRY_EAST, 'H');
 
        if (cur == TRY_EAST) SET(TRY_SOUTH, east == 0 ? 'E' : 'H');
        if (cur == TRY_SOUTH) SET(TRY_WEST, south == 0 ? 'S' : 'H');
        if (cur == TRY_WEST) SET(TRY_NORTH, west == 0 ? 'W' : 'H');
        if (cur == TRY_NORTH) SET(BACKTRACK, north == 0 ? 'N' : 'H');
 
        if (cur == BACKTRACK) {
            if (north > 0) SET(0, 'N');
            if (west > 0) SET(0, 'W');
            if (south > 0) SET(0, 'S');
            if (east > 0) SET(0, 'E');
        }
    }
}

// This is over-complicated since I reused code for subtask 3
void subtask4() {
    const int MAX_COLOR = 10;
 
    const int BOUNDARY = -2;
    const int BLOCKED = -1;
 
    const int FINAL = 1;
 
    const int TRY_EAST = 2;
    const int TRY_SOUTH = 3;
    const int TRY_WEST = 4;
    const int TRY_NORTH = 5;
 
    const int BACKTRACK = 6;
    const int TO_CLEAN_UP = 7;
    const int CLEAN_RIGHT = 8;
    const int CLEAN_DOWN = 9;
 
#define SET(color, action) { set_instruction(state, color, action); continue; }
 
    FOR(cur,0,MAX_COLOR) FOR(west,-2,MAX_COLOR) FOR(south,-2,MAX_COLOR) FOR(east,-2,MAX_COLOR) FOR(north,-2,MAX_COLOR) {
        vector<int> state {cur, west, south, east, north};

        // Clean up
        if (cur == CLEAN_DOWN) {
            if (south == 0) {
                if (east == TO_CLEAN_UP) SET(CLEAN_RIGHT, 'H');
                if (north == CLEAN_DOWN) SET(0, 'N');
                SET(CLEAN_RIGHT, 'H');
            }
        }
        if (cur == TO_CLEAN_UP) {
            if (west == FINAL) SET(CLEAN_RIGHT, 'H');
            if (north == CLEAN_DOWN) {
                if (east == TO_CLEAN_UP) SET(CLEAN_RIGHT, 'H');
                if (south == TO_CLEAN_UP) SET(CLEAN_DOWN, 'S');
                SET(0, 'N');
            }
            if (west == CLEAN_RIGHT) {
                SET(CLEAN_RIGHT, 'H');
            }
        }
        if (cur == CLEAN_RIGHT) {
            if (south == TO_CLEAN_UP) SET(CLEAN_DOWN, 'S');
            if (east == TO_CLEAN_UP) SET(CLEAN_RIGHT, 'E');
            if (north == CLEAN_DOWN) SET(0, 'N');
            SET(0, 'W');
        }
 
        // Found target
        if (cur == FINAL) {
            if (east == TO_CLEAN_UP) SET(FINAL, 'E');

            if (north > 1) SET(FINAL, 'N');
            if (west > 1) SET(FINAL, 'W');
            if (south > 1) SET(FINAL, 'S');
            if (east > 1) SET(FINAL, 'E');
            SET(FINAL, 'T');
        }
        if ((south == BOUNDARY && east == BOUNDARY) || west == FINAL || south == FINAL || east == FINAL || north == FINAL) {
            SET(FINAL, 'H');
        }
 
        if (cur == 0) SET(TRY_EAST, 'H');
 
        if (cur == TRY_EAST) SET(TRY_SOUTH, east == 0 ? 'E' : 'H');
        if (cur == TRY_SOUTH) SET(BACKTRACK, south == 0 ? 'S' : 'H');
        // if (cur == TRY_WEST) SET(TRY_NORTH, west == 0 ? 'W' : 'H');
        // if (cur == TRY_NORTH) SET(BACKTRACK, north == 0 ? 'N' : 'H');
 
        if (cur == BACKTRACK) {
            if (north > 0) SET(TO_CLEAN_UP, 'N');
            if (west > 0) SET(TO_CLEAN_UP, 'W');
            if (south > 0) SET(TO_CLEAN_UP, 'S');
            if (east > 0) SET(TO_CLEAN_UP, 'E');
        }
    }
}

void sol_88() {
    const int MAX_COLOR = 9;
 
    const int BOUNDARY = -2;
    const int BLOCKED = -1;
 
    const int FINAL = 1;

    // directions
    const int ONE_SOUTH = 2;
    const int ONE_EAST = 3;
    const int ONE_NORTH = 4;
    const int ONE_WEST = 5;

    // phase 2
    const int TWO_SOUTH = 6;
    const int TWO_EAST = 7;
    const int TWO_NORTH = 8;
    const int TWO_WEST = 9;

    FOR(cur,0,MAX_COLOR) FOR(west,-2,MAX_COLOR) FOR(south,-2,MAX_COLOR) FOR(east,-2,MAX_COLOR) FOR(north,-2,MAX_COLOR) {
        vector<int> state {cur, west, south, east, north};
        // Phase 3
        if (cur == FINAL) {
            if (south == BOUNDARY && east == BOUNDARY) SET(FINAL, 'T');
            if (north >= 6) SET(FINAL, 'N');
            if (south >= 6) SET(FINAL, 'S');
            if (east >= 6) SET(FINAL, 'E');
            if (west >= 6) SET(FINAL, 'W');
        }

        // Phase 2
        if (north >= 6 || south >= 6 || east >= 6 || west >= 6 || cur >= 6) {
            if (west == ONE_EAST) SET(cur >= 6 ? cur : cur + 4, 'W');
            if (south == ONE_NORTH) SET(cur >= 6 ? cur : cur + 4, 'S');
            if (east == ONE_WEST) SET(cur >= 6 ? cur : cur + 4, 'E');
            if (north == ONE_SOUTH) SET(cur >= 6 ? cur : cur + 4, 'N');

            if (north == BOUNDARY && west == BOUNDARY) SET(FINAL, 'H');
            if (north == FINAL || south == FINAL || east == FINAL || west == FINAL) SET(FINAL, 'H');

            if (cur == ONE_SOUTH || cur == TWO_SOUTH) SET(0, 'S');
            if (cur == ONE_NORTH || cur == TWO_NORTH) SET(0, 'N');
            if (cur == ONE_WEST || cur == TWO_WEST) SET(0, 'W');
            if (cur == ONE_EAST || cur == TWO_EAST) SET(0, 'E');
        }

        // Reached final state
        if (south == BOUNDARY && east == BOUNDARY) {
            SET(6, 'H');
        }

        // Starting state
        if (cur == 0 && north == BOUNDARY && west == BOUNDARY) {
            if (south == 0) SET(ONE_SOUTH, 'S');
            if (east == 0) SET(ONE_EAST, 'E');
        }

        // BFS
        if (cur == ONE_SOUTH) {
            if (east == 0 || east == ONE_WEST) SET(ONE_EAST, 'E');
            if (north == 0 || north == ONE_SOUTH) SET(ONE_NORTH, 'N');
            if (west == 0 || west == ONE_EAST) SET(ONE_WEST, 'W');
            if (south == 0 || south == ONE_NORTH) SET(ONE_SOUTH, 'S');
        }
        if (cur == ONE_EAST) {
            if (north == 0 || north == ONE_SOUTH) SET(ONE_NORTH, 'N');
            if (west == 0 || west == ONE_EAST) SET(ONE_WEST, 'W');
            if (south == 0 || south == ONE_NORTH) SET(ONE_SOUTH, 'S');
            if (east == 0 || east == ONE_WEST) SET(ONE_EAST, 'E');
        }
        if (cur == ONE_NORTH) {
            if (west == 0 || west == ONE_EAST) SET(ONE_WEST, 'W');
            if (south == 0 || south == ONE_NORTH) SET(ONE_SOUTH, 'S');
            if (east == 0 || east == ONE_WEST) SET(ONE_EAST, 'E');
            if (north == 0 || north == ONE_SOUTH) SET(ONE_NORTH, 'N');
        }
        if (cur == ONE_WEST) {
            if (south == 0 || south == ONE_NORTH) SET(ONE_SOUTH, 'S');
            if (east == 0 || east == ONE_WEST) SET(ONE_EAST, 'E');
            if (north == 0 || north == ONE_SOUTH) SET(ONE_NORTH, 'N');
            if (west == 0 || west == ONE_EAST) SET(ONE_WEST, 'W');
        }
        if (cur == 0) {
            if (north == ONE_SOUTH) SET(ONE_NORTH, 'N');
            if (south == ONE_NORTH) SET(ONE_SOUTH, 'S');
            if (east == ONE_WEST) SET(ONE_EAST, 'E');
            if (west == ONE_EAST) SET(ONE_WEST, 'W');
        }
    }
}
