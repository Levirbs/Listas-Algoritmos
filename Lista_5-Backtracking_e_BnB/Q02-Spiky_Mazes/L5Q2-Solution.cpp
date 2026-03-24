#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;
 
bool is_valid(vector<vector<char>>& maze, vector<vector<bool>>& visited, int row, int column, int x, int y) {
    // para ser valido ele precisa: estar dentro dos limites do labirinto;
    // nao ser uma parede; e nao ter sido visitado

    // limites do labirinto
    if (row< 0 || row >= x || column < 0 || column >= y) return false;

    // parede
    if (maze[row][column] == '#') return false;
    
    // visitado
    if (visited[row][column]) return false;

    return true;
}

void solve_maze(vector<vector<char>>& maze, vector<vector<bool>>& visited, vector<vector<int>>& min_spikes, int current_row, int current_column, int current_spikes) {
    // dimensoes
    int x = maze.size();
    int y = maze[0].size();

    // se o caminho atual for pior que o melhor conhecido, volta
    if (current_spikes >= min_spikes[current_row][current_column]) {
        return;
    }
    
    min_spikes[current_row][current_column] = current_spikes;

    visited[current_row][current_column] = true;

    // checar caminhos possiveis.

    // esquerda
    if (is_valid(maze, visited, current_row, current_column - 1, x, y)) {
        if (maze[current_row][current_column - 1] == 's') {
            solve_maze(maze, visited, min_spikes, current_row, current_column - 1, current_spikes + 1);
        } else {
            solve_maze(maze, visited, min_spikes, current_row, current_column - 1, current_spikes);
        }
    }

    // cima
    if (is_valid(maze, visited, current_row - 1, current_column, x, y)) {
        if (maze[current_row - 1][current_column] == 's') {
            solve_maze(maze, visited, min_spikes, current_row - 1, current_column, current_spikes + 1);
        } else {
            solve_maze(maze, visited, min_spikes, current_row - 1, current_column, current_spikes);
        }
    }

    // direita
    if (is_valid(maze, visited, current_row, current_column + 1, x, y)) {
        if (maze[current_row][current_column + 1] == 's') {
            solve_maze(maze, visited, min_spikes, current_row, current_column + 1, current_spikes + 1);
        } else {
            solve_maze(maze, visited, min_spikes, current_row, current_column + 1, current_spikes);
        }
    }
    
    // baixo
    if (is_valid(maze, visited, current_row + 1, current_column, x, y)) {
        if (maze[current_row + 1][current_column] == 's') {
            solve_maze(maze, visited, min_spikes, current_row + 1, current_column, current_spikes + 1);
        } else {
            solve_maze(maze, visited, min_spikes, current_row + 1, current_column, current_spikes);
        }
    }

    visited[current_row][current_column] = false; // desfaz (backtrack)
}

int main () {
    int n, m, j;
    char character;
    cin >> n >> m >> j;
    vector<vector<char>> maze(n, vector<char>(m));
    vector<pair<int, int>> entrances;
    pair<int, int> treasure;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> character;
            maze[i][j] = character;
            if(character == '@') entrances.push_back({i, j}); 
            else if (character == 'x') treasure = {i, j};   
        }
    }

    // preciso achar o caminho com a menor soma de espinhos para o 'x'
    int min_spikes = INF;
    for (int i = 0; i < entrances.size(); i++) {
        vector<vector<int>> dist(n, vector<int>(m, INF));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int start_cost = (maze[entrances[i].first][entrances[i].second] == 's');
        
        solve_maze(maze, visited, dist, entrances[i].first, entrances[i].second, start_cost);
        
        min_spikes = min(min_spikes, dist[treasure.first][treasure.second]);
    }

    // a ideia é: para eu ter certeza que existe um caminho, tenho que calcular o menor caminho de uma entrada para o 'x',
    // depois preciso fazer o dobro desse valor para descubrir quantos espinhos preciso passa para entrar e sair.
    // o dobro pois se eu encontra um caminho que seja a menor soma, mesmo que tenha outro caminho, vai ter o mesmo valor,
    // entao posso apenas dobrar para encontrar o valor total para incluir o valor da volta.

    if (2 * min_spikes <= j) { // duas vezes pois tem que se considerar a ida e a volta
        cout << "SUCCESS" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}