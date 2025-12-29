#include <bits/stdc++.h>
using namespace std;


string readFile(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

vector<vector<string>> parse(const string& conteudo) {
    vector<vector<string>> matriz;
    string line;
    stringstream ss(conteudo);

    while (getline(ss, line)) {
        if (line.empty()) continue;
        stringstream ls(line);
        vector<string> row;
        string token;
        while (ls >> token) {
            row.push_back(token);
        }
        matriz.push_back(row);
    }
    return matriz;
}

long long part01(const string& conteudo) {
    auto matriz = parse(conteudo);

    int linhas = matriz.size();
    int colunas = matriz[0].size();

    vector<long long> resultados(colunas, 0);

    for (int c = 0; c < colunas; c++) {
        string operador = matriz[linhas - 1][c];
        long long resultado = (operador == "+") ? 0 : 1;

        for (int l = 0; l < linhas - 1; l++) {
            long long valor = stoll(matriz[l][c]);
            if (operador == "+")
                resultado += valor;
            else
                resultado *= valor;
        }

        resultados[c] = resultado;
    }

    long long somaFinal = 0;
    for (auto v : resultados) somaFinal += v;
    return somaFinal;
}

vector<vector<char>> parseGrid(const string& raw) {
    vector<string> linhas;
    string line;
    stringstream ss(raw);

    while (getline(ss, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        linhas.push_back(line);
    }

    while (!linhas.empty() && linhas.back().empty())
        linhas.pop_back();

    size_t width = 0;
    for (auto& l : linhas)
        width = max(width, l.size());

    vector<vector<char>> grid;
    for (auto& l : linhas) {
        l.resize(width, ' ');
        grid.push_back(vector<char>(l.begin(), l.end()));
    }

    return grid;
}

vector<pair<int,int>> splitEmBlocos(const vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    auto separador = [&](int c) {
        for (int r = 0; r < rows; r++) {
            if (grid[r][c] != ' ') return false;
        }
        return true;
    };

    vector<pair<int,int>> blocos;
    int c = 0;

    while (c < cols) {
        while (c < cols && separador(c)) c++;
        if (c >= cols) break;

        int start = c;
        while (c < cols && !separador(c)) c++;
        int end = c - 1;

        blocos.emplace_back(start, end);
    }

    return blocos;
}

long long resolveBlocoParte2(
    const vector<vector<char>>& grid,
    int start,
    int end
) {
    int rows = grid.size();
    int opRow = rows - 1;

    char operador = 0;
    for (int c = start; c <= end; c++) {
        char ch = grid[opRow][c];
        if (ch == '+' || ch == '*') {
            operador = ch;
            break;
        }
    }

    if (operador == 0) return 0;

    vector<long long> numeros;
    for (int c = end; c >= start; c--) {
        string s;
        for (int r = 0; r < opRow; r++) {
            char ch = grid[r][c];
            if (ch >= '0' && ch <= '9')
                s.push_back(ch);
        }
        if (!s.empty())
            numeros.push_back(stoll(s));
    }

    long long acc = (operador == '+') ? 0 : 1;
    for (auto n : numeros) {
        if (operador == '+')
            acc += n;
        else
            acc *= n;
    }

    return acc;
}

long long part02(const string& conteudo) {
    auto grid = parseGrid(conteudo);
    auto blocos = splitEmBlocos(grid);

    long long total = 0;
    for (auto& [start, end] : blocos) {
        total += resolveBlocoParte2(grid, start, end);
    }

    return total;
}

int main() {
    string conteudo = readFile("input.txt");

    cout << part01(conteudo) << endl;
    cout << part02(conteudo) << endl;

    return 0;
}
