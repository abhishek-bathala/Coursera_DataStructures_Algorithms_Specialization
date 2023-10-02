#include <iostream>
#include <vector>

using namespace std;


struct square {
    string up;
    string left;
    string down;
    string right;
    bool placed;
};

typedef vector<vector<pair <square, int>> > grid;

void print_grid (grid g) {
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            cout << "(" << g[i][j].first.up << "," << g[i][j].first.left << "," << g[i][j].first.down << "," << g[i][j].first.right << ")";
            if (j != 4) {
                cout << ";";
            }
            else {
                if (i != 4) {
                    cout << endl;
                }
            }
        }
    }
}

grid build_graph (vector<square> &squares) {
    grid g(5, vector<pair <square, int> > (5));
    int num_of_squares_placed = 0;
    
    //finding squares that go in corners
    for (int i = 0; i < squares.size(); i++) {
        square s = squares[i];

        if (s.left == "black" && s.up == "black") { //top left
            g[0][0] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.right == "black" && s.up == "black") { //top right
            g[0][4] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.left == "black" && s.down == "black") { //bottom left 
            g[4][0] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.right == "black" && s.down == "black") { //bottom right
            g[4][4] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        if (num_of_squares_placed == 4) {
            break;
        }
    }
    
    //cout << num_of_squares_placed << endl;
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    //finding squares adjacent to corners
    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].placed) { //square is already placed
            continue;
        }

        square s = squares[i];
        if (s.left == "black") { //left edge of grid
            if (s.up == g[0][0].first.down) { //below top left corner
                g[1][0] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
            else if (s.down == g[4][0].first.up) { //above bottom left corner
                g[3][0] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
        }

        if (s.up == "black") { //top edge of grid
            if (s.left == g[0][0].first.right) { //right side of top left corner
                g[0][1] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
            else if (s.right == g[0][4].first.left) { //left side of top right corner
                if (g[0][3].first.down != "") {
                    squares[g[0][3].second].placed = false;
                    num_of_squares_placed--;
                }
                g[0][3] = pair <square, int> (s, i);
                squares[i].placed = true;
                num_of_squares_placed++;
            }
        }

        if (s.right == "black") { //right edge of grid
            if (s.up == g[0][4].first.down) { //right side of top left corner
                g[1][4] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
            else if (s.down == g[4][4].first.up) { //left side of top right corner
                g[3][4] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
        }

        if (s.down == "black") { //bottom edge of grid
            if (s.right == g[4][4].first.left) { //left side of top right corner
                if (g[4][3].first.down != "") {
                    squares[g[4][3].second].placed = false;
                    num_of_squares_placed--;
                }
                g[4][3] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
            else if (s.left == g[4][0].first.right) { //right side of top left corner
                g[4][1] = pair <square, int> (s, i);
                squares[i].placed = true;
            num_of_squares_placed++;
            }
        }
        if (num_of_squares_placed == 12) {
            break;
        }
    }
    
    //cout << num_of_squares_placed << endl;
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    //finding remaining squares in edges
    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].placed) {
            continue;
        }
        square s = squares[i];

        if (s.left == "black" && s.right != "black" && s.up != "black" && s.down != "black") {
            g[2][0] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.up == "black" && s.right != "black" && s.left != "black" && s.down != "black") {
            g[0][2] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.right == "black" && s.up != "black" && s.left != "black" && s.down != "black") {
            g[2][4] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.down == "black" && s.right != "black" && s.left != "black" && s.up != "black") {
            g[4][2] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        if (num_of_squares_placed == 16) {
            break;
        }
    }
    
    //cout << num_of_squares_placed << endl;
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    //finding corners of inner 3x3 grid
    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].placed) {
            continue;
        }
        square s = squares[i];

        if (s.up == g[0][1].first.down && s.left == g[1][0].first.right) {
            g[1][1] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.up == g[0][3].first.down && s.right == g[1][4].first.left) {
            g[1][3] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.down == g[4][3].first.up && s.right == g[3][4].first.left) {
            g[3][3] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.down == g[4][1].first.up && s.left == g[3][0].first.right) {
            g[3][1] = pair <square, int> (s, i);
            num_of_squares_placed++;
            squares[i].placed = true;
        }
        if (num_of_squares_placed == 20) {
            break;
        }
    }
    
    //cout << num_of_squares_placed << endl;
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    //finding squares for edges of inner 3x3 grid
    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].placed) {
            continue;
        }
        square s = squares[i];

        if (s.up == g[1][1].first.down && s.down == g[3][1].first.up && s.left == g[2][0].first.right) {
            g[2][1] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.left == g[1][1].first.right && s.up == g[0][2].first.down && s.right == g[1][3].first.left) {
            g[1][2] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.up == g[1][3].first.down && s.right == g[2][4].first.left && s.down == g[3][3].first.up) {
            g[2][3] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        else if (s.down == g[4][2].first.up && s.right == g[3][3].first.left && s.left == g[3][1].first.right) {
            g[3][2] = pair <square, int> (s, i);
            squares[i].placed = true;
            num_of_squares_placed++;
        }
        if (num_of_squares_placed == 24) {
            break;
        }
    }
    
    //cout << num_of_squares_placed << endl;
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    for (int i = 0; i < squares.size(); i++) {
        if (squares[i].placed) {
            continue;
        }
        g[2][2] = pair <square, int> (squares[i], i);
    }
    
    //print_grid(g);
    //cout << endl << "------------------------" << endl;
    

    return g;

}



int main () {
    vector<square> squares;

    //take input
    for (int i = 0; i < 25; i++) {
        string line;
        cin >> line;
        //removing brackets from input
        line.erase(line.begin());
        line.erase(line.end()-1);

        //seperating colours from commas from input
        square temp;
        vector<string> sides_of_temp;
        int index = 0;
        int start_of_word = 0;
        for (int j = 0; j < 4; j++) {
            while (line[start_of_word] < 97 || line[start_of_word] > 122) {
                start_of_word++;
            }
            index = start_of_word;

            while (line[index] >= 97 && line[index] <= 122) {
                index++;
            }
            sides_of_temp.push_back(line.substr(start_of_word, index-start_of_word));
            index++;
            start_of_word = index;
        }

        temp.up = sides_of_temp[0];
        temp.left = sides_of_temp[1];
        temp.down = sides_of_temp[2];
        temp.right = sides_of_temp[3];
        temp.placed = false;
        squares.push_back(temp);
    }

    grid g = build_graph(squares);

    print_grid(g);

    /*cout << "(black,black,blue,cyan);(black,cyan,yellow,brown);(black,brown,maroon,red);(black,red,white,red);(black,red,green,black)" << endl <<
    "(blue,black,orange,yellow);(yellow,yellow,yellow,orange);(maroon,orange,brown,orange);(white,orange,maroon,blue);(green,blue,blue,black)" << endl <<
    "(orange,black,maroon,cyan);(yellow,cyan,orange,maroon);(brown,maroon,orange,yellow);(maroon,yellow,white,cyan);(blue,cyan,white,black)" << endl <<
    "(maroon,black,yellow,purple);(orange,purple,purple,purple);(orange,purple,maroon,cyan);(white,cyan,red,orange);(white,orange,orange,black)" << endl <<
    "(yellow,black,black,brown);(purple,brown,black,blue);(maroon,blue,black,orange);(red,orange,black,orange);(orange,orange,black,black)";
    */

}