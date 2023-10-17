#include <iostream>

using namespace std;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}


int fibonacci_sum_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    int sum = 0;
    int prev_last_digit = 0;
    int curr_last_digit = 1;
    int temp = 0;

    for (int i = 0; i < n; ++i) {
        sum = (sum + curr_last_digit) % 10;
        temp = (prev_last_digit + curr_last_digit) % 10;
        prev_last_digit = curr_last_digit;
        curr_last_digit = temp;
    }

    return sum;
}

int main() {
    long long n = 0;
    cin >> n;
    cout << endl << fibonacci_sum_fast(n);
}
