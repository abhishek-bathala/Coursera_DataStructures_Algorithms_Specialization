#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <climits>

using namespace std;

class MaxMatching {
 public:
  void Solve() {
    adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

  int num_left, num_right;
  vector<vector<bool> > adj_matrix;

  vector<vector<bool>> ReadData() {
    cin >> num_left >> num_right;
    int total = num_left + num_right + 2;
    vector<vector<bool>> adj_matrix(total, vector<bool>(total));
    for (int i = 0; i < total-1; ++i) {
      if (i == 0) {
        for (int j = 1; j <= num_left; j++) {
          adj_matrix[i][j] = 1;
        }
      }
      else if (i > num_left) {
        adj_matrix[i][total-1] = 1;
      }
      else {
        for (int j = 0; j < num_right; ++j) {
          int bit;
          cin >> bit;
          adj_matrix[i][j+num_left+1] = (bit == 1);
        }
      }
    }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i]);
    }
    cout << "\n";
  }

  vector<int> FindMatching(vector<vector<bool>>& adj_matrix) {
    vector<vector<int> > flow(adj_matrix.size(), vector<int> (adj_matrix.size()));
    vector<vector<int> > capacity(adj_matrix.size(), vector<int> (adj_matrix.size()));
    vector<int> result(num_left);
    fill_n(result.begin(), num_left, -1);
    int num_of_matches = 0;
    int from = 0;
    int to = adj_matrix.size() - 1;
    
    //adding capacities
    for (int i = 0; i < adj_matrix.size(); i++) {
      for (int j = 0; j < adj_matrix[i].size(); j++) {
        if (adj_matrix[i][j] == 1) {
          capacity[i][j] = 1;
        }
      }
    }
    //adding backwards edges
    for (int i = 0; i < adj_matrix.size(); i++) {
      for (int j = 0; j < adj_matrix[i].size(); j++) {
        if (adj_matrix[i][j] == 1) {
          adj_matrix[j][i] = 1;
        }
      }
    }

    /*cout << endl << "adjacency matrix" << endl;
    for (int i = 0; i < adj_matrix.size(); i++) {
      for (int j = 0; j < adj_matrix[i].size(); j++) {
        cout << adj_matrix[i][j] << " ";
      }
      cout << endl;
    }
    
    cout << endl << "capacity matrix" << endl;
    for (int i = 0; i < capacity.size(); i++) {
      for (int j = 0; j < capacity[i].size(); j++) {
        cout << capacity[i][j] << " ";
      }
      cout << endl;
    }
    */

    //matching crews to flights
    while (true) {
      vector<size_t> id_lst;
      vector<int> queue;
      vector<bool> visited;
      vector<int> dist;
      vector<int> prev_dist;
      bool path_exists = false;

      
      for (int i = 0; i < adj_matrix.size(); i++) {
          visited.push_back(false);
          dist.push_back(INT_MAX);
          prev_dist.push_back(-1);
      }
      
      visited[from] = true;
      queue.push_back(from);
      dist[from] = 0;

      //cout << "bfs" << endl;
      
      while(!queue.empty()) {
          int front = queue.front();
          //cout << "front is " << front << endl;
          queue.erase(queue.begin());
          
          //cout << "going to visit ";
          vector<int> adj_of_front;
          for (int i = 0; i < adj_matrix[front].size(); i++) {
            if (adj_matrix[front][i] == 1) {
              adj_of_front.push_back(i);
              //cout << i << " ";
            }
          }
          //cout << endl;

          

          for (int i = 0; i < adj_of_front.size(); i++) {
              //cout << "checking " << adj_of_front[i] << " ";
              //cout << "whose flow is " << flow[front][adj_of_front[i]] << " and capacity is " << capacity[front][adj_of_front[i]] << endl;
              if ((visited[adj_of_front[i]] == false) && (capacity[front][adj_of_front[i]] - flow[front][adj_of_front[i]] != 0) && capacity[front][adj_of_front[i]] > 0) {

                  visited[adj_of_front[i]] = true;
                  //cout << "visited " << adj_of_front[i] << endl;
                  dist[adj_of_front[i]] = dist[front] + 1;
                  prev_dist[adj_of_front[i]] = front;
                  queue.push_back(adj_of_front[i]);
                  /*cout << "queue contains ";
                  for (auto x : queue) {
                      cout << x << " ";
                  }
                  cout << endl;
                  */
                  

                  if (adj_of_front[i] == to) {
                      //cout << "destination found" << endl;
                      path_exists = true;
                      queue.clear();
                      break;
                  }
              }
              else {
                  //cout << adj_of_front[i] << " already visited " << endl;
              }
          }
      }

      /*cout << "prev dist" << endl;
      for (auto x : prev_dist) {
      cout << x << ' ';
      }
      cout << endl << "dist" << endl;

      for (auto x : dist) {
          cout << x << ' ';
      }
      cout << endl;

      
      cout << "reversing path" << endl;
      */
      

      int reverse_path = to;
      id_lst.push_back(reverse_path);
      while (prev_dist[reverse_path] != -1) {
          id_lst.push_back(prev_dist[reverse_path]);
          reverse_path = prev_dist[reverse_path];
      }

      reverse(id_lst.begin(), id_lst.end());

      /*cout << "printing path" << endl;
      for (int i = 0; i < id_lst.size(); i++) {
          cout << id_lst[i] << " ";
      }
      cout << endl;
      */
      
      
      //if no path, return 'flow'
      if (id_lst.size() == 1 && id_lst[0] == to) {
          break;
      }

      /*cout << "id_lst is " << endl;
      for (auto x : id_lst) {
        cout << x << " ";
      }
      cout << endl;
 
      cout << "finding smallest flow" << endl;
      */

      //smallest capacity in shortest path = smallest_flow
      int smallest_flow = INT_MAX;
      for (int i = 0; i < id_lst.size()-1; i++) {
        vector<int> adj_of_id;
        //cout << "adjacent of " << id_lst[i] << " is ";
        for (int a = 0; a < adj_matrix.size(); a++) {
          if(adj_matrix[id_lst[i]][a] == 1) {
            adj_of_id.push_back(a);
            //cout << a << " ";
          }
        }
        //cout << endl;

        for (int j = 0; j < adj_of_id.size(); j++) {
          //cout << endl << "i: " << i << " j: " << adj_of_id[j] << endl;
          if (adj_of_id[j] == id_lst[i+1]) {
            //cout << "checking " << adj_of_id[j] << " ";
            //cout << "whose flow is " << flow[id_lst[i]][adj_of_id[j]] << " and capacity is " << capacity[id_lst[i]][adj_of_id[j]] << endl;
            if (capacity[id_lst[i]][adj_of_id[j]] - flow[id_lst[i]][adj_of_id[j]] < smallest_flow && capacity[id_lst[i]][adj_of_id[j]] != 0 && capacity[id_lst[i]][adj_of_id[j]] - flow[id_lst[i]][adj_of_id[j]] != 0) {
              smallest_flow = capacity[id_lst[i]][adj_of_id[j]] - flow[id_lst[i]][adj_of_id[j]];
              //cout << "found smallest flow at " << adj_of_id[j] << " ";
              //cout << "whose flow is " << flow[id_lst[i]][adj_of_id[j]] << " and capacity is " << capacity[id_lst[i]][adj_of_id[j]] << endl;
            }
          } 
        }
      }
      

      //cout << "smallest flow is " << smallest_flow << endl;

      //cout << "adding smallest flow" << endl;

      //add smallest_flow to each edge in shortest path
      for (int i = 0; i < id_lst.size()-1; i++) {
        vector<int> adj_of_id;
        //cout << "adj of " << id_lst[i] << " is ";
        for (int a = 0; a < adj_matrix.size(); a++) {
          if(adj_matrix[id_lst[i]][a] == 1) {
            adj_of_id.push_back(a);
            //cout << a << " ";
          }
        }
        //cout << endl;

        for (int j = 0; j < adj_of_id.size(); j++) {
          //cout << "comparing " << id_lst[i+1] << " and " << adj_of_id[j];
          //cout << " whose capacity is " << capacity[id_lst[i]][adj_of_id[j]] << endl;
          if (adj_of_id[j] == id_lst[i+1] && capacity[id_lst[i]][adj_of_id[j]] != 0) {
            //cout << "adding flow to " << id_lst[i] << ":" << adj_of_id[j] << endl;

            flow[id_lst[i]][adj_of_id[j]] += 1;
            flow[adj_of_id[j]][id_lst[i]] -= 1;
            capacity[adj_of_id[j]][id_lst[i]] += 1;
            //cout << "capacity of " << adj_of_id[j] << ":" << id_lst[i] << " is now " << capacity[adj_of_id[j]][id_lst[i]] << endl;
              
          }
        }
      }

      /*cout << "flow is " << endl;
      for (int x = 0; x < flow.size(); x++) {
        for (int y = 0; y < flow[x].size(); y++) {
          cout << flow[x][y] << " ";
        }
        cout << endl;
      }
      */

    }
    

    for (int i = 0; i < flow.size(); i++) {
      if (flow[i][flow.size()-1] == 1) {
        num_of_matches++;
      }
    }
    //cout << "number of matches are " << num_of_matches << endl;

    vector<int> matched_crews;
    //matching done, finding crews that have been matched
    for (int i = 0; i < flow.size(); i++) {
      //cout << "checking " << flow[flow.size()-1][i] << endl;
      if (flow[i][flow.size()-1] == 1) {
        matched_crews.push_back(i);
        //cout << "crew " << i << " matched" << endl;
      }
    }

    //finding which crew belongs to which flight
    for (int i = 0; i < matched_crews.size(); i++) {
      for (int j = 0; j < flow.size(); j++) {
        if (flow[j][matched_crews[i]] == 1) {
          //cout << "flight " << j << " uses crew " << matched_crews[i]-num_left << endl;
          result[j-1] = matched_crews[i]-num_left;
        }
      }
    }

    return result;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
