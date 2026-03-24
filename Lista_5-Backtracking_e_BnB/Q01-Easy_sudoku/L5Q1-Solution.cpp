#include <iostream>
#include <vector>

using namespace std;

bool valid(vector<vector<int>>& sudoku, int linha, int coluna, int k) {
    // para ser valido, tenho que checar: linha; coluna; e na area 3x3
    
    // linha
    for (int i = 0; i < 9; i++) {
        if (sudoku[linha][i] == k) return false;
    }

    // coluna
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][coluna] == k) return false;
    }

    // area
    int area_linha = linha / 3;
    int area_coluna = coluna / 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int l = area_linha * 3 + i;
            int c = area_coluna * 3 + j;
            if (sudoku[l][c] == k) return false;
        }
    }
    return true;
}

bool solve_sudoku(vector<vector<int>>& sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                for (int n = 1; n < 10; n++) { // tenta todos os numeros de 1 a 9
                    if (valid(sudoku, i, j, n)) {
                        sudoku[i][j] = n;
                        if (solve_sudoku(sudoku)) {
                            return true;
                        }
                        sudoku[i][j] = 0; // desfazer (backtrack)
                    }
                }            
                return false; // nenhum numero de 1 a 9 funcionou
            }
        }
    } 
    return true; // se nao retornou falso, esta resolvido
}

int main() {
    int n, num;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> sudoku(9, vector<int>(9));
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                cin >> num;
                sudoku[j][k] = num;
            }
        }

        if (solve_sudoku(sudoku)) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << sudoku[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            cout << "No solution" << endl;
        }
    }
    return 0;
}