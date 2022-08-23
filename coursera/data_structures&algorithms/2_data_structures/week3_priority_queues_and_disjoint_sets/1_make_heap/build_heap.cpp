#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];

    /*for (int i = 0; i < data_.size(); i++) {
      cout << data_[i] << " ";
    }
    cout << endl;*/
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation

    for (int i = floor(data_.size()/2); i >= 0; i--) {
      siftDown(i);
    }
    
  }

  void siftDown(int i) {
    /*for (int i = 0; i < data_.size(); i++) {
      cout << data_[i] << " ";
    }
    cout << endl;*/

    int maxIndex = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < data_.size() && data_[l] < data_[maxIndex]) {
      maxIndex = l;
    }
    if (r < data_.size() && data_[r] < data_[maxIndex]) {
      maxIndex = r;
    }
    if (i != maxIndex) {
      swaps_.push_back(pair<int, int>(i, maxIndex));
      int temp = data_[i];
      data_[i] = data_[maxIndex];
      data_[maxIndex] = temp;
      siftDown(maxIndex);
    }
  }

  int parent(int i) {
    return floor((i-1)/2);
  }

  int leftChild(int i) {
    return (2*i)+1;
  }

  int rightChild(int i) {
    return (2*i)+2;
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
