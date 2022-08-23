#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long MaxPairwiseProduct(const vector<int>& numbers) {
    int n = numbers.size();
    int index = -1;
    int next_index = -1;

    for (int i = 0; i < n; ++i) {
        if(index == -1 || numbers[index] < numbers[i]){
            index = i;
        }
    }

    for (int j = 0; j < n; ++j) {
        if((next_index == -1 && numbers[index] != numbers[j]) || (numbers[j] > numbers[next_index] && j != index)){
            next_index = j;
            //cout << "next index is " << next_index << endl;
        }
    }

    //cout << "max is " << numbers[index] << endl;
    //cout << "next max is " << numbers[next_index] << endl;

    return ((long long) numbers[index]*numbers[next_index]);
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
