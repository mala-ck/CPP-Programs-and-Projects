/* The zero-player Game of Life is a 2-dimentional array of cells that are either dead or alive at any generation. 
 In the next generation, a cell currently alive will continue to live only if 2 or 3 of its immediate neighbors are alive. 
 Similarly, in the next generation, a cell currently dead will spring to life spontaneously, only if exactly 3 of its neighboring cells are alive. 
 Show the game of life through 30 generations, using a two-dimensional array of characters with ~41 rows (or whatever fits your computer screen completely) 
 and at least 60 columns.
 */

#include <iostream>
#include <fstream>
using namespace std;
#define GOL_ROWS 41
#define GOL_COLS 60
#define GOL_GEN 30

//Read a sample input file into gol_matrix
int populate_gen0(bool gol_matrix [][GOL_COLS], int x, int y)
{
    string line;
    ifstream my_inp;
    int row=0;
    
    my_inp.open("/Users/home/Documents/xcode_projects/hw3_game_of_life/ten_point.txt");
    if(my_inp.is_open())
    {
        while (my_inp.good())
        {
            getline(my_inp, line);
            //cout<< line.length();
            for(int i=0; i< line.length();i++)
            {
                if(line[i] == 'o')
                {
                gol_matrix[row][i]=true;
                }
                    
                else 
                {
                    gol_matrix[row][i]=false;
                }
            }
            row++;
            //cout<< line<<endl;
        }
        my_inp.close();
    }
    else cout<< "unable to open file";
    //cout<< system("pwd");
    
    /*for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            cout << gol_matrix[i][j]<< " ";
        }
        cout<<endl;
    }*/
    return 0;
        
}

//get the count of neighbors for a particular cell in gol_matrix
int get_neighbor_cnt(int x, int y, bool gol_matrix [][GOL_COLS], int rows, int cols)
{
    int x_next=0;
    int y_next=0;
    
    int neighbor_cnt=0;
    
    //1--------------------------------------------------------
    //left cell. same row previous col
    x_next = x;
    y_next = y-1;
    
    //If column goes beyond left edge, then column has to wrap around to other end i.e last column
    if(y_next == -1) //left cell edge

    {
        y_next=cols-1;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;
    
    //2-----------------------------------------------------------
    //right cell same row, next col
    x_next = x;
    y_next = y+1;
    //If column goes betond right edge, then it has to wrap around to the left edge i.e first column
    if(y_next == cols) //left cell edge
    {
        y_next=0;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;

    //3------------------------------------------------------
    //top cell. same column, previous row
    x_next = x-1;
    //If row goes beyond top edge, then wrap around to bottom edge i.e last row
    if(x_next == -1)
    {
        x_next = rows-1;
    }
    y_next = y;
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;

    //4-------------------------------------------------------
    //bottom cell. same column next row
    x_next = x+1;
    // for row goes beyond bottom edge, then wrap around to top i.e first row
    if(x_next == rows)
    {
        x_next = 0;
    }
    y_next = y;
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;
    
    
    //5-------------------------------------------------------
    // diagonal top-rt , previous row, next column
    x_next = x-1;
    y_next = y+1;
    
    if(x_next == -1)
    {
        x_next = rows-1;
    }
    
    if(y_next == cols)
    {
        y_next = 0;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;

    
    //6--------------------------------------------------------
    //diagonal bottom right, next row ,next column
    x_next = x+1;
    y_next = y+1;
    
    //If row goes beyond max rows, then wrap around to first row
    if(x_next == rows)
    {
        x_next = 0;
    }
    
    //If column goes beyond max columns then wrap around to first column
    if(y_next == cols)
    {
        y_next = 0;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;

    
    //7---------------------------------------------------------
    //diagonal top left prev row, prev col
    x_next = x-1;
    y_next = y-1;
    
    //if row goes below first row, then wrap around to last row
    if(x_next == -1)
    {
        x_next = rows-1;
    }
    
    //if column goes below first col, then wrap around ot last column
    if(y_next == -1)
    {
        y_next = cols-1;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;


    //8----------------------------------------------------
    //diagonal bottom left next row, prec col
    x_next = x+1;
    y_next = y-1;
    
    //if row goes beyond last row then wrap around to first row
    if(x_next == rows)
    {
        x_next = 0;
    }
    
    //if column goes beyond first row,t hen wrap around to last column
    if(y_next == -1)
    {
        y_next = cols-1;
    }
    if(gol_matrix[x_next][y_next] == true) neighbor_cnt++;
    

    return neighbor_cnt;
    
}

//method to copy matrices
int copy_matrix(bool src[][GOL_COLS], bool trgt[][GOL_COLS], int rows, int cols)
{
    for(int i =0; i< rows; i++)
    {
        for(int j = 0; j< cols; j++)
            {
                trgt[i][j] = src[i][j];
            }
    }
    
    return 0;
}

//Method to print GOL matrix
int print_gen(int gen, bool next_gen[][GOL_COLS], int rows, int cols)
{
    cout<<endl << endl <<"GOL Generation - " << gen <<endl<<endl;
    
    cout<<"+------------------------------------------------------------+"<<endl;
    for(int i =0; i< rows; i++)
    {
        cout<<'|';
        for(int j = 0; j< cols; j++)
        {
            if(next_gen[i][j]==true)
            {
                cout << "o";
            }
            else 
            {
                cout << " ";
            }
        }
        cout<<'|';

        cout << endl;        
    }
    
    cout<<"+------------------------------------------------------------+"<<endl;
    
    return 0;
}

//Methos ot reset entire matrix to dead celll values
int empty_matrix(bool mat[][GOL_COLS], int rows, int cols)
{
    for(int i =0; i< rows; i++)
    {
        for(int j = 0; j< cols; j++)
        {
            mat[i][j] = false;
        }
    }
    return 0;
    
}

//Main 
int main(int argc, const char * argv[])
{
    
    int rows = GOL_ROWS;
    int cols = GOL_COLS;
    int max_gen = GOL_GEN;
    int neighbor_cnt=0;
    
    bool gol_matrix[GOL_ROWS][GOL_COLS]={false};
    bool next_gol[GOL_ROWS][GOL_COLS]={false};
    
    //Load sample input from file to matrix
    populate_gen0(gol_matrix, rows, cols);
    
    //Print the original sample input
    print_gen(0, gol_matrix, rows, cols);
    
    
    //loop through generations
    for(int gen_cnt=0; gen_cnt < max_gen; gen_cnt++)
    {
        //loop through every element in gol_matrix and create the next generation life called next_gol
        for(int i = 0; i< rows; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                neighbor_cnt = get_neighbor_cnt(i,j,gol_matrix, rows, cols);
                
                switch (neighbor_cnt) 
                {
                    case 0:
                    case 1:
                        //if number of neighbors is less than 2 , the cell dies
                        next_gol[i][j] = false;
                        break;
                    
                    case 2:
                        //if number of neighbors is 2 , then cell sustains
                        next_gol[i][j] = gol_matrix[i][j];
                        break;
                        
                    case 3:
                        //if number of neighbors is exactly 3 then new cell comes alive/existing cell sustains
                        next_gol[i][j] = true;
                        break;
                        
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        //If number of neighbors is more than 3 then cell dies of over crowding
                        next_gol[i][j] = false;
                        break;
                        
                    default:
                        // invalid neighbor count
                        break;
                }
                
                
            }
        }
        
        //print the new generaiton
        print_gen(gen_cnt+1,next_gol, rows, cols);
        //copy new to old
        copy_matrix(next_gol, gol_matrix, rows, cols);
        //empty the new to create next generation
        empty_matrix(next_gol, rows, cols);
        
    }
    
    return 0;
}

