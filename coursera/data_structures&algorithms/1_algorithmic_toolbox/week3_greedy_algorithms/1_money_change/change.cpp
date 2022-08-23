#include <iostream>

int get_change(int m) {
  int n = 0;

  n += (m/10);
  m -= (m/10)*10;

  n += (m/5);
  m -= (m/5)*5;

  n += (m/1);
  m -= (m/1)*1;

  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
