#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

typedef vector<vector<int>> matrix;

vector<matrix> magicSquares;
matrix m;

int cost(int a, int b) {
  return abs(a - b);
}

int complement(int a) {
  return 10 - a;
}

bool between(int a, int b, int c) {
  return a >= b && a <= c;
}

void generateMagicSquares() {
  for (int a = 1; a <= 9; ++a) {
    for (int c = 1; c <= 9; ++c) {
      if (a == c || a == complement(c)) continue;

      int d = 5 + c - a;
      int b = 15 - c - a;

      if (a == b || a == complement(b)) continue;
      if (a == d || a == complement(d)) continue;
      if (b == c || b == complement(c)) continue;
      if (b == d || b == complement(d)) continue;
      if (c == d || c == complement(d)) continue;

      if (between(d, 1, 9) && between(b, 1, 9)) {
        vector<int> line1 = {a, b, c};
        vector<int> line2 = {d, 5, complement(d)};
        vector<int> line3 = {complement(c), complement(b), complement(a)};
        matrix m = {line1, line2, line3};
        magicSquares.push_back(m);
      }
    }
  }
}

int distance(matrix& a, matrix& b) {
  int dist = 0;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      dist += cost(a[i][j], b[i][j]);
    }
  }

  return dist;
}

int main () {
  int aux, minCost = INT32_MAX;
  generateMagicSquares();

  for (int i = 0; i < 3; ++i) {
    m.push_back(vector<int>());
    for (int j = 0; j < 3; ++j) {
      cin >> aux;
      m[i].push_back(aux);
    }
  }

  for (matrix& magicSquare : magicSquares) {
    minCost = min(minCost, distance(m, magicSquare));
  }

  cout << minCost << endl;
  return 0;
}