#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const double EPS = 1e-3;
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


Position SelectPivotElement(
  const Matrix &a, 
  vector <bool> &used_rows, 
  vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element {0, 0};
    while (used_rows[pivot_element.row]){
        ++pivot_element.row;
    }
    while (used_columns[pivot_element.column]) {
        ++pivot_element.column;
    }

    double biggest = -0.0;
    for (int row = pivot_element.row; row < a.size(); row++) {
      if (abs(biggest) - abs(a[row][pivot_element.column]) < EPS) {
        biggest = a[row][pivot_element.column];
        pivot_element.row = row;
      }
    }

    return pivot_element;

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

    /*for (int i = pivot_element.row + 1; i < a.size(); i++) {
      scale = a[i][pivot_element.column];
      for (int j =pivot_element.column; j < a.size(); j++) {
        a[i][j] -= scale*a[pivot_element.row][j];
      }
      b[i] -= scale*b[pivot_element.row];
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
        }
        */
    }
    
}

void MarkPivotElementUsed(const Position &pivot_element, vector <bool> &used_rows, vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
    //cout << "\tmarked row " << pivot_element.row << " & column " << pivot_element.column << " as used" << endl;
}

Column SolveEquation(Equation equation) {
  //cout << "in solveEquation" << endl; 
  Matrix &a = equation.a;
  Column &b = equation.b;
  int size = a.size();
  Position pivot_element(0, 0);

  vector <bool> used_columns(size, false);
  vector <bool> used_rows(size, false);
  for (int step = 0; step < size; ++step) {
      pivot_element = SelectPivotElement(a, used_rows, used_columns);
      //cout << "pivot element is " << pivot_element.row << ":" << pivot_element.column << endl;
      SwapLines(a, b, used_rows, pivot_element);
      /*for (int i = 0; i < a.size(); i++) {
          for (int j = 0; j < a[i].size(); j++) {
              cout << a[i][j] << " ";
          }
          cout << b[i] << endl;
      }
      */

      ProcessPivotElement(a, b, pivot_element);
      MarkPivotElementUsed(pivot_element, used_rows, used_columns);
  }

  for (int i = 0; i < a.size(); i++) {
    double x = b[i];
    for (int j = 0; j != i; j++) {
      b[j] -= x*a[j][i];
    }
  }

  return b;
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    Matrix A, 
    vector<double> b, 
    vector<double> c) {

  // Write your code here
  pair<int, vector<double>> result {0, vector<double>(m, 0)};
  bool allSolSatisfy = false;
  double maxPleasure = -__DBL_MAX__;

  //creating subsets from powerset
  bool subset_contains[m+n+1] = {0};
  for (int a = 0; a <= n+m+1; a++) {
    subset_contains[a] = 1;
    
    //only for subsets of size m
    if (a == m-1) {
      //generate subset
      int subset_num = 0;
      do {
        //for each generated subset
        Matrix subsetA; 
        Column subsetB;
        for (int j = 0; j < m+n+1; j++) {

          if (subset_contains[j]) {
            //assigning subset to subsetA and subsetB
            Row subset;
            for (int i = 0; i < A[j].size(); i++) {
              subset.push_back(A[j][i]);
            }
            subsetA.emplace_back(subset);
            subsetB.push_back(b[j]);
          }
        }
        subset_num++;

        //printing subset
        /*cout << "subset " << subset_num << " contains " << endl;
        for (int i = 0; i < subsetA.size(); i++) {
          for (int k = 0; k < subsetA[i].size(); k++) {
            cout << subsetA[i][k] << " ";
          }
          cout << subsetB[i] << endl;
        }
        cout << endl;
        */
       
        //generating equation
        Equation equation {subsetA, subsetB};
        //solving equation
        Column solution = SolveEquation(equation);
        /*cout << "solution is ";
        for (int i = 0; i < solution.size(); i++) {
          cout << solution[i] << " ";
        }
        cout << endl;
        */
        

        //checking whether solution fits against all inequalities
        double tempPleasure = 0.0;
        bool satisfiesAll = false;
        bool negativeSol = false;
        vector<double> tempSol;
        //for each inequality
        for (int s = 0; s < A.size(); s++) {
          double sum = 0.0;
          negativeSol = false;
          //for calculating sum
          for (int w = 0; w < A[s].size(); w++) {
            if (solution[w] == -0) {
              sum += A[s][w]*solution[w]*-1;
            }
            else if (abs(solution[w]) < EPS) {
              solution[w] = 0;
            }
            else if (solution[w] < -0.0) {
              negativeSol = true;
            }
            else {
              sum += A[s][w]*solution[w];
            }
          }

          //cout << "sum is " << sum <<  " b[s] is " << b[s] << endl;
          //checking if sum satisfies inequality
          if (negativeSol) {
            satisfiesAll = false;
            break;
          }
          if (b[s] == -0) {
            if (sum >= 0) {
              satisfiesAll = true;
            }
          }
          else if (sum - b[s] < EPS) {
            satisfiesAll = true;
          }
          else {
            satisfiesAll = false;
            break;
          }
        }

        if (satisfiesAll) {
          //cout << "solution satisfies all" << endl;
          allSolSatisfy = true;
          for (int p = 0; p < solution.size(); p++) {
            //cout << "solution[p] is " << solution[p] << endl;
            if (solution[p] != -0) {
              tempPleasure += solution[p]*c[p];
            }
          }
          //cout << "temppleasure is " << tempPleasure << " maxPleasure is " << maxPleasure << endl;

          if (tempPleasure > maxPleasure) {
            maxPleasure = tempPleasure;
            //cout << "maxPleasure is now " << maxPleasure << endl;
            result.first = 0;
            result.second = solution;
            /*cout << "solution contains ";
            for (auto sol : solution) {
              cout << sol << " ";
            }
            cout << endl;
            */
            
          }
        }
        else {
          //cout << "solution does not satisfy" << endl;
        }

        //cout << endl << "---------------" << endl;
        

      } while (prev_permutation(subset_contains, subset_contains + n + m + 1));
      
    }
  }

  if (!allSolSatisfy) {
    result.first = -1;
  }
  else {
    double sumOfAmount = 0.0;
    for (auto amount : result.second) {
      sumOfAmount += amount;
    }
    //cout << "sumofsolution is " << sumOfAmount << endl;
    if (abs(sumOfAmount - 1.0e+9) < EPS) {
      result.first = 1;
    }
  }

  return result;
}

int main(){
  int n, m;
  cin >> n >> m;
  Matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }

  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  while (n < m) {
    A.emplace_back(m, 0);
    b.push_back(0);
    n++;
  }

  for (int i = 0; i < m; i++) {
    vector <double> temp(m, 0.0);
    temp[i] = 1;
    A.emplace_back(temp);
    b.push_back(-0.0);
  }

  /*for (int i = m+1; i < A.size(); i++) {
    //cout << "i and i-m are " << i << i-m << endl;
    if (i < A.size() && i-m-1 < A[i].size()) {
      A[i][i-m-1] = 1;
    }
  }*/

  A.emplace_back(vector <double> (m, 1));
  b.push_back(1.0e+9);

  /*cout << "A & B contains " << endl;
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      cout << A[i][j] << " ";
    }
    cout << b[i] << endl;
  }
  */
  

  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  
  return 0;
}
