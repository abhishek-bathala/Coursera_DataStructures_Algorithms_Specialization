#include <cmath>
#include <iostream>
#include <vector>
#include <string>

const double EPS = 1e-6;
const int PRECISION = 20;

using namespace std;

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;


struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    cin >> size;
    Matrix a(size, vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        string temp, temp2;
        for (int column = 0; column < size; ++column) {
            cin >> temp;
            a[row][column] = stod(temp);
        }
        cin >> temp2;
        b[row] = stod(temp2);
    }
    return Equation(a, b);
}

Position SelectPivotElement(
  const Matrix &a, 
  vector <bool> &used_rows, 
  vector <bool> &used_columns, Position &pivot_element) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    /*while (used_rows[pivot_element.row]){
        ++pivot_element.row;
    }
    while (used_columns[pivot_element.column]) {
        ++pivot_element.column;
    }*/

    for (int i = 0; i < a[pivot_element.row].size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (!used_columns[i] && !used_rows[j] && a[j][i] != 0) {
                pivot_element.column = i;
                pivot_element.row = j;
                return pivot_element;
            }
        }
    }
}

void SwapLines(Matrix &a, Column &b, vector <bool> &used_rows, Position &pivot_element) {
    swap(a[pivot_element.column], a[pivot_element.row]);
    swap(b[pivot_element.column], b[pivot_element.row]);
    swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here

    //rescaling row w/pivot element so that pivot element is 1
    double scale = a[pivot_element.row][pivot_element.column];
    //cout << "scaling by factor of " << scale << endl;
    for (int i = 0; i < a[pivot_element.row].size(); i++) {
        a[pivot_element.row][i] /= scale;
    }
    b[pivot_element.row] /= scale;
    /*cout << "after scaling row with pivot" << endl;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << b[i] << endl;
    }*/


    for (int i = 0; i < a.size(); i++) {
        //cout << "i is " << i << endl;
        if (a[i][pivot_element.column] != 0 && i != pivot_element.row) {
            if (a[i][pivot_element.column] > 0 || a[pivot_element.row][pivot_element.column] > 0) {
                //checking if subtraction makes entry below pivot 0
                if ((a[i][pivot_element.column] > 0 && a[pivot_element.row][pivot_element.column] > 0) || (a[i][pivot_element.column] < 0 && a[pivot_element.row][pivot_element.column] < 0)) {
                    //cout << "subtraction makes below pivot 0" << endl;
                    double scale = a[i][pivot_element.column];
                    //cout << "scale is " << scale << endl;
                    for (int j = 0; j < a[pivot_element.row].size(); j++) {
                        a[i][j] -= scale*a[pivot_element.row][j];
                    }
                    b[i] -= scale*b[pivot_element.row];
                }
                else {
                    //cout << "addition makes below pivot 0" << endl;
                    double scale = a[i][pivot_element.column];
                    scale *= -1;
                    //cout << "scale is " << scale << endl;
                    for (int j = 0; j < a[pivot_element.row].size(); j++) {
                        //cout << "adding " << a[pivot_element.row][j] << " to " << scale << "*" << a[i][j] << endl;
                        a[i][j] += scale*a[pivot_element.row][j];
                    }
                    b[i] += scale*b[pivot_element.row];
                }
            }
        }
        /*cout << "after row " << i << " matrix is" << endl;
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < a[i].size(); j++) {
                cout << a[i][j] << " ";
            }
            cout << b[i] << endl;
        }*/
    }
}

void MarkPivotElementUsed(const Position &pivot_element, vector <bool> &used_rows, vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
    //cout << "\tmarked row " << pivot_element.row << " & column " << pivot_element.column << " as used" << endl;
}

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();
    Position pivot_element(0, 0);

    vector <bool> used_columns(size, false);
    vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        pivot_element = SelectPivotElement(a, used_rows, used_columns, pivot_element);
        //cout << "pivot element is " << pivot_element.row << ":" << pivot_element.column << endl;
        SwapLines(a, b, used_rows, pivot_element);
        /*for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < a[i].size(); j++) {
                cout << a[i][j] << " ";
            }
            cout << b[i] << endl;
        }*/

        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }

    return b;
}

void PrintColumn(const Column &column) {
    int size = column.size();
    cout.precision(PRECISION);
    //cout << "result is " << endl;
    for (int row = 0; row < size; ++row)
        cout << column[row] << " ";
    cout << endl;
}

int main() {
    Equation equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}
