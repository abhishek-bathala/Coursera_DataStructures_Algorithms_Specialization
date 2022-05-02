#include <iostream>

using namespace std;

int get_change(int m) {
  int money[m+1];
  int coins[3];
  
  money[0] = 0;

  //denominations of available currency
  coins[0] = 1;
  coins[1] = 3;
  coins[2] = 4;

  for (int i = 1; i <= m; i++) {
    money[i] = money[i-1]+1;
    //cout << "money[" << i << "] is " << money[i] << endl;
    
    for (int j = 0; j < 3; j++) {
      if (i >= coins[j]) {
        //cout << "checking " << i << " > " << coins[j] << endl;
        int numOfCoins = money[i-coins[j]] + 1;
        if (numOfCoins < money[i]) {
          money[i] = numOfCoins;
          //cout << " for coins[j] " << coins[j] << " numofcoins is " << numOfCoins << endl;
        }
      }
    }
  }
  return money[m];
}

int main() {
  int m;
  cin >> m;
  cout << get_change(m) << '\n';
}
