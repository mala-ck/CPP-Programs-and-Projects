#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* Problem is to move a knight on chess board to bottom-right corner of the board from any start location.
 * Point to note , we can map each location on board to a vertex of a graph and each valid move
 * of knight from that node to an edge. This way we can construct a graph of knight moves.
*/

#define BOARD_SIZE 3

//Class to define a location/square on the chess board and it's operations.
class LOCATION {
public:
    int x;
    int y;

    LOCATION(){ x=0; y=0;};
    LOCATION(int r,int c):x(r), y(c){}
    LOCATION(LOCATION const &loc);
    LOCATION& operator= (LOCATION const &obj);
    friend bool operator== (LOCATION &l1, LOCATION &l2);
    friend bool operator!= (LOCATION &l1, LOCATION &l2);
    LOCATION operator + (LOCATION &l1);
    bool out_of_board();

};

LOCATION::LOCATION(LOCATION const &loc)
{
    x=loc.x;
    y=loc.y;
}

LOCATION& LOCATION::operator= (LOCATION const &obj)
{
    x=obj.x;
    y=obj.y;
    return *this;
}

bool operator== (LOCATION &l1, LOCATION &l2)
{
    return (l1.x == l2.x &&
            l1.y == l2.y);
}

bool operator!= (LOCATION &l1, LOCATION &l2)
{
    return !(l1 == l2);
}

LOCATION LOCATION::operator + (LOCATION &l1)
{
    LOCATION add_res;
    add_res.x = this->x+l1.x;
    add_res.y = this->y+l1.y;

    return add_res;
}

bool LOCATION::out_of_board()
{
    if(x > BOARD_SIZE-1 || x<0 || y> BOARD_SIZE-1 || y<0) return true;

    return false;
}

// Map each square on the chess board to a vertex in graph and all possible adjacent moves into it's edges
// Following class is used to define a verted-edges pair of the graph
class NODE
{
public :
    vector<LOCATION> adjacent_moves;
    bool visited;
    LOCATION parent;
};

// Construct the chess board sctructure.
// Declare it as a 2-D array of lists/vector of nodes
NODE chess_board[BOARD_SIZE][BOARD_SIZE];


// Given a location on board, this funciton generates all possible valid one-step knight-moves from the location
int generate_valid_moves(LOCATION &loc, vector<LOCATION> &valid_moves)
{
    // From a location on chess board, a knight can make one move in 8 possible ways at max
    LOCATION knight_moves[8] = { LOCATION(-2,-1), LOCATION(-2,1), LOCATION(-1,-2), LOCATION(-1,2), LOCATION(1,-2), LOCATION(1,2), LOCATION(2,-1), LOCATION(2,1) };

    if(loc.out_of_board())
    {
        return 1;
    }

    for(int mv_cnt = 0; mv_cnt < 8; mv_cnt++)
    {
        LOCATION tmp = loc+knight_moves[mv_cnt];
        if(!tmp.out_of_board())
        {
            valid_moves.push_back(tmp);
        }
    }

    if(valid_moves.empty()) return 1;
    return 0;

}



// This module just constructus a shortest path between source and destinaiton nodes if it exists using BFS
int construct_path(vector<LOCATION> &path, LOCATION &start_loc)
{

    queue<LOCATION> qu;

    //Define destination location
    LOCATION dest_loc(BOARD_SIZE-1,BOARD_SIZE-1);

    //mark that the popped node is visited
    chess_board[start_loc.x][start_loc.y].visited = true;

    LOCATION current_loc(start_loc);

    while(current_loc != dest_loc)
    {

        vector<LOCATION> valid_moves;

        //generate valid moves for current location
        if(generate_valid_moves(current_loc, valid_moves)!=0) return 1;

        //Store these valid moves of current node in chess bord
        chess_board[current_loc.x][current_loc.y].adjacent_moves = valid_moves;

        //Enqueue all the non-visited ajacent nodes of current node marking them visited
        for(int mv_cnt = 0; mv_cnt < (int)valid_moves.size(); mv_cnt++)
        {
            if(chess_board[valid_moves[mv_cnt].x][valid_moves[mv_cnt].y].visited == false)
            {
                //Enque the adjacent nodes of current nodes and mark them visited on board
                // Also mark current node the parent of adjacent nodes
                qu.push(valid_moves[mv_cnt]);
                chess_board[valid_moves[mv_cnt].x][valid_moves[mv_cnt].y].visited = true;
                chess_board[valid_moves[mv_cnt].x][valid_moves[mv_cnt].y].parent = current_loc;
            }
        }

        //Store the first  element in the queue
        current_loc = qu.front();

        // Dequeue one element from queue
        qu.pop();

    } // End of while loop

    while(current_loc != start_loc)
    {
        path.push_back(current_loc);
        current_loc = chess_board[current_loc.x][current_loc.y].parent;
    }

    path.push_back(start_loc);

return 0;
}


// Function to display the shortest path
void dispplay_path(vector<LOCATION> path)
{
    if(path.size() == 0)
    {
        cout<< "Location "<< BOARD_SIZE << " " << BOARD_SIZE << " cannot be reached.\nSpecify a different starting point \n" ;
    }
    else
    {
           int path_size = (int)path.size();
           for(int node_cnt=0; node_cnt < path_size; node_cnt++)
           {
              cout << "(" << path[path_size-1-node_cnt].x+1 << "," << path[path_size-1-node_cnt].y+1 << ") \n" ;
           }

    }
}

// Function to process command line arguments
int process_cmd_line(int& argc, char** argv, int& row, int& col)
{
    if(argc < 3)
    {
        cout<< "Insuffecient arguments..\nEnter row number and column number in commandline eg. \"1 2\" \n";
        return 1;
    }

    row = atoi(argv[1]);
    col = atoi(argv[2]);

    if(row < 1 || row > BOARD_SIZE)
    {
        cout<< "Row number should be greater than 0 and less than " << BOARD_SIZE << endl;
        return 1;
    }

    if(col < 1 || col > BOARD_SIZE)
    {
        cout<< "Column number should be greater than 0 and less than " << BOARD_SIZE << endl;
        return 1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    int row = 1, col = 1 ;
    vector<LOCATION> path_to_dest;

    if(process_cmd_line(argc, argv, row, col)!=0) return 0;

    LOCATION start_loc(row-1,col-1);

    construct_path(path_to_dest, start_loc);

    dispplay_path(path_to_dest) ;

    return 0;
}

