#include <iostream>
#include <deque>

#include <sstream>
#include <cstdio>

using namespace std;

const int MAX_SIZE = 9;     // 九宫格

struct Pos {
    Pos(int x, int y) : row(x), col(y) {};
    int row;
    int col;
};

typedef deque <Pos> qpos;
qpos Q;     // 记录要放置数字的位置

// 九宫格数组，0表示玩家要放置数字的位置
int sudoku[MAX_SIZE][MAX_SIZE] = {
    {9, 0, 6, 0, 7, 0, 4, 0, 3},
    {0, 0, 0, 4, 0, 0, 2, 0, 0},
    {0, 7, 0, 0, 2, 3, 0, 1, 0},
    {5, 0, 0, 0, 6, 0, 1, 0, 0},
    {0, 4, 0, 2, 0, 8, 0, 6, 0},
    {0, 0, 3, 0, 0, 0, 0, 0, 5},
    {0, 3, 0, 7, 0, 0, 0, 5, 0},
    {0, 0, 7, 0, 0, 5, 0, 0, 0},
    {4, 0, 5, 0, 1, 0, 7, 0, 8},
};

void printSudoku()
{
    cout << "-------------------------" << endl;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j <MAX_SIZE; j++) {
            if (j % 3 == 0) {
                cout << "| ";
            }
            cout << sudoku[i][j] << " ";
        }
        cout << "| ";
        
        cout << endl;
        if ( (i+1) % 3 == 0 ) {
            cout << "-------------------------" << endl;
        }
    }
}

bool check(Pos p, int n)
{
    int cur_row = p.row;
    int cur_col = p.col;
    // 验证行列是否合格
    for (int i = 0; i < MAX_SIZE; i++) {
        if (n == sudoku[i][cur_col] || n == sudoku[cur_row][i]) {
            return false;
        }
    }
    
    // 验证九宫格内是无复生数字
    int grid_row = ( cur_row / 3 ) * 3;
    int grid_col = ( cur_col / 3 ) * 3;
    for (int i = 0; i < 3; i++) {
        if (n == sudoku[grid_row][i + grid_col] ||
            n == sudoku[grid_row + i][grid_col]) {
            return false;
        }
    }
    
    return true;
}

//bool place(qpos & Q)
//{
//    // 递归结束条件为没有要断续放置数字的位置
//    if (Q.empty()) {
//        printSudoku();
//        return true;
//    }
//    Pos cur(Q.front().row, Q.front().col);  // 当前需要放置的位置信息
//    Q.pop_front();
//    for (int i = 1; i <= 9; i++) {       // 从1到9轮流尝试
//        if ( check(cur, i) ) {
//            sudoku[cur.row][cur.col] = i;   // 放置数字i到当前位置
//            if ( !place(Q) ) {      // 放置下一位置
//                // 下一位置放置失败，则在当前位置尝试放置下一个i
//                sudoku[cur.row][cur.col] = 0;   // 将当前位置值重置
//            } else {    // 下一位置放置成功
//                return true;
//            }
//        }
//    }
//    Q.push_front(cur);  //当前位置不论怎么放置数字，下一位置都无法放置成功，
//    // 重新插入该位置信息，返回上一级放置位置
//    return false;
//}

bool place2(qpos & Q)
{
    // 递归结束条件为没有要断续放置数字的位置
    if (Q.empty()) {
        printSudoku();
        return true;
    }
    Pos cur(Q.front().row, Q.front().col);  // 当前需要放置的位置信息
    Q.pop_front();
    //printSudoku();
    
    for (int i = 1; i <= 9; i++) {       // 从1到9轮流尝试
        if ( check(cur, i) ) {
            sudoku[cur.row][cur.col] = i;   // 放置数字i到当前位置
            place2(Q);
            sudoku[cur.row][cur.col] = 0;   // 将当前位置值重置
        }
    }
    Q.push_front(cur);
    return false;// 重新插入该位置信息，返回上一级放置位置
}

int main()
{
    
    // Q中保存需要放置数字的位置
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (0 == sudoku[i][j]) {
                Q.push_back(Pos(i, j));
            }
        }
    }
    
    place2(Q);
    
    return 0;
}
