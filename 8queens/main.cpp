/*  The problem is, placing eight chess queens on an 8×8 chessboard so that no two queens attack each other */

#include <iostream>
#include <algorithm>
using namespace std;
int print_board(int outp[], int n);


//n-queens problem where n=8
int main(int argc, const char * argv[])
{
    int n= 5;//number of queens and board nxn
    int queen_pos_in_col[] = {1,2,3,4,5};// First fix each queen in unique rows. So the first condition of no queen can occupy same row i solved by this
    int permut_cnt=0;// counter to count the number of solutions
    bool valid = true;// flag to point invalid solution
    int step_cnt=0;
 
    
    do{// For each permutaiton do the following
        
        //Print the permutation
        /*for(int i=0; i<n;i++)
            {
                cout<<queen_pos_in_col[i];
            }
        cout << endl;
         */
        
        //filter diagonal combinaitons
        //For each location of queen check if there exixts another queen in its diagonal
        valid = true;//This is a flag to break out if the diagonal check fails
        for(int col=0; col<n; col++)
        {
            // check in each oclumn after the chosen column
            // since we are startin at the first column always ther ei no need to chec back wad diagonals. We only check for forward diagonals
            
            // So as soon as the diagonal rule breaks for any queen in the permutaiton the solution is discarded. This reduces the number of steps to a great extent(ie for n=8 it reduces from 11258960 to 235090)
            for(int nxt_col=col+1; nxt_col<n;nxt_col++)
            {
                step_cnt++;
                if(queen_pos_in_col[nxt_col] == queen_pos_in_col[col]+(nxt_col-col) || 
                   queen_pos_in_col[nxt_col] == queen_pos_in_col[col]-(nxt_col-col))
                {
                    valid = false;
                    break;
                }
               }
            if(valid == false)
            {
                break;
            }
        }
        if(valid == true)
        {
            for(int i=0; i<n;i++)
            {
                cout<<queen_pos_in_col[i];
            }
            cout << endl;
            //call the method to print the board with queens
            print_board(queen_pos_in_col, n);
            cout<<endl;
            permut_cnt++;
        }
    }while(next_permutation(queen_pos_in_col,queen_pos_in_col+n));//get the next permutaiton
    
    cout<<"valid solutions permutation count="<<permut_cnt<<endl;
    cout<<"step_cnt="<<step_cnt<<endl;
    
 
    return 0;
}

//method to print the output
int print_board(int outp[], int n)
{
    char **print_matrix = 0;
    int ROWS = n;
    int COLS = n;
    //memory allocated for elements of rows.
    print_matrix = new char *[ROWS] ;
    
    //memory allocated for  elements of each column.
    for( int i = 0 ; i < ROWS ; i++ )
        print_matrix[i] = new char[COLS]; 
    
    //print the header row of A B C D E..
    for(int i=65;i<65+n;i++)
    {
        cout<<char(i)<<" ";
    }
    cout<<endl;
    
    for(int i =0; i< ROWS; i++)
    {
        print_matrix[i][outp[i]] = 'Q';
        for(int j = 0; j<COLS; j++)
        {
            if(print_matrix[i][j]!='Q')
            {
                print_matrix[i][j]='_';
            }
            cout<<print_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

  
    
    for( int i = 0 ; i < ROWS ; i++ )
    {
        delete [] print_matrix[i] ;
    }
    delete [] print_matrix ;
    return 0;
}

