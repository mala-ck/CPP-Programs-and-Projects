/* Write a program that solves the Game of Sudoku, level 0. If a solution exists, output the completed Sudoku board. 
 Input to the program is an incomplete Sudoku field with some numbers provided but many others omitted.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#define DEBUG
using namespace std;

#define SMALL_N 3
#define BIG_N ( SMALL_N * SMALL_N )
#define EOL '\n'
#define EMPTY 0
#define NO_CHAR ' '
#define FALSE 0
#define TRUE  1

#define P_BAR		printf( "|" )
#define P_LINE		printf( "-" )
#define P_PLUS		printf( "+" )
#define P_EOL   	printf( "\n" )
#define P_TAB		printf( "\t" )
#define P_BLANK	printf( " " )


// each element of an n*n X n*n sudoku board has the following structure:
// "field" has any of the values 0..n*n, with 0 meaning that it is empty.
// "option_count" states, how many of n*n numbers could be options.
// "can_be[]" is array of n*n+1 bools. Says whether element "i" is option
// if can_be[i] is false, number "i" cannot be option any longer.
// if option_count ever reaches 1, then we "know" the field value
// General data structure layout
//                             0     1     2     3             8     9
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//  | NAT |     | NAT |     |  DC |     |     |     |  ...  |     |     |
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//   field    option_count  can_be[ BIG_N + 1 ]
//  specific layout for empty field
//                             0     1     2     3             8     9
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//  |  0  |     |  9  |     |  DC |  T  |  T  |  T  |  ...  |  T  |  T  |
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//   field    option_count  can_be[ BIG_N + 1 ]
//
//  Specific layout for occupied field 3
//                             0     1     2     3             8     9
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//  |  3  |     |  0  |     |  DC |  F  |  F  |  T  |  ...  |  F  |  F  |
//  +-----+     +-----+     +-----+-----+-----+-----+- ... -+-----+-----+
//   field    option_count  can_be[ BIG_N + 1 ]
//
typedef struct board_cell_tp
{
	unsigned	field;				// 0 if empty, else one of 1..n*n
	unsigned	option_count;	 	// initially, all n*n are options
	bool     	can_be[ BIG_N + 1 ];	// if false, number "i" impossible
} struct_board_cell_tp;



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////                                                ////////////
////////////           G l o b a l   O j e c t s            ////////////
////////////                                                ////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// this is the complete sudoku board, n*n by n*n = BIG_N * BIG_N fields
struct_board_cell_tp sudoku_board[ BIG_N ][ BIG_N ];



//Read a sample input file into gol_matrix
int read_input_board(string input_file_path)
{
    string line;
    ifstream my_inp;
    int row=0;
    int col=0;
    
    my_inp.open(input_file_path.c_str());
    
    
    //my_inp.open("/Users/home/Documents/xcode_projects/hw6_sudoku/sudoku_input1.txt");
    if(my_inp.is_open())
    {
        while (my_inp.good())
        {
            getline(my_inp, line);
            col = 0;
            for(int i=0; i< line.length();i++)
            {
                if(line[i] == ' ') continue;
                        //int tmp = line[i] - '0';
                        sudoku_board[row][col++].field=line[i] - '0';
            }
            row++;
            //cout<< line<<endl;
        }
        my_inp.close();
    }
    else cout<< "unable to open file";

    return 0;
    
}

void init_input_board()
{
    for(int i=0; i<BIG_N ; i++)
    {
        for(int j=0; j<BIG_N ; j++)
        {
            sudoku_board[i][j].option_count = 0;
            
            for(int opt=1; opt<BIG_N+1; opt++)
            {
                sudoku_board[i][j].can_be[opt] = true;
            }
        }
    }
}


int print_board()
{
    cout << "    0 1 2   3 4 5   6 7 8  " <<endl;
    cout << "  +_______+_______+_______+" << endl; 
    cout << endl;
    for(int row = 0; row< BIG_N ; row++)
    {
        cout<< row << " | ";
        for(int col = 0; col<BIG_N ; col++)
        {
            cout << sudoku_board[row][col].field << " " ;
            if(col == 2 || col == 5 )
            {
                cout << "| ";
            }
        }
        cout<< "|" << endl;;

        if(row == 2 || row == 5 )
        {
            cout << "  +_______+_______+_______+" << endl; 
            cout << "  |                       |" << endl; 


        }
    }
    cout << "  +_______+_______+_______+" << endl; 

    
}


unsigned find_1_field(int row, int col)
{
    for(int i = 1; i< BIG_N+1; i++)
    {
        if(sudoku_board[row][col].can_be[i] == true )
        {
            return i;
        }
    }
    
}

unsigned count_fields(int row, int col)
{
    int count = 0;
    for(int i = 1; i< BIG_N+1; i++)
    {
        if(sudoku_board[row][col].can_be[i] == true )
        {
            count++ ;
        }
    }
    
    return count;

    
}

// check all horizontal and vertical lines for empty spaces.
// each empty space initially has BIG_N options
// but for each existing value in that row decrease the option.
// if per chance the options end up just 1, then we can plug in a number.
// return the number of fields changed from empty to a new value
unsigned row_analysis()
{ // horiz_vert
	unsigned changes = 0;
	unsigned options = 0;
	unsigned field   = 0;	// remember the next number to be excluded
    
	for ( int row = 0; row < BIG_N; row++ ) 
    {
		for ( int col = 0; col < BIG_N; col++ ) 
        {
			if ( sudoku_board[row][col].field ) 
            {	// there is a number
				//ASSERT( ( SRC.option_count == 0 ), "has # + option?" );
			}else
            {
				// field is EMPTY. Goal to count down options to 1
				//ASSERT( ( sudoku_board.option_count ), "0 field must have opt" );
				// go thru each field. For # found, exclude # from can_be[]
                for ( int i = 0; i < BIG_N; i++ ) 
                {
                    //row analysis
                    field = sudoku_board[ row ][ i ].field;
                    if ( field ) 
                    {
                        // we found a field
                        sudoku_board[row][col].can_be[ field ] = false;
                    } //end if
                }
                sudoku_board[row][col].option_count = options = count_fields( row, col );
                if ( options == 1 ) 
                {
                    // plug in only 1 of BIG_N numbers
                    // and set option_count to 0
                    field = find_1_field( row, col );
                    sudoku_board[row][col].field = field;
                    changes++;
                } //end if
            } //end if else
        } //end for col
    } //end for row
        return changes;
} //end horiz_vert
                    


unsigned col_analysis()
{ // horiz_vert
	unsigned changes = 0;
	unsigned options = 0;
	unsigned field   = 0;	// remember the next number to be excluded
    
	for ( int row = 0; row < BIG_N; row++ ) 
    {
		for ( int col = 0; col < BIG_N; col++ ) 
        {
			if ( sudoku_board[row][col].field ) 
            {	// there is a number
				//ASSERT( ( SRC.option_count == 0 ), "has # + option?" );
			}else
            {
				// field is EMPTY. Goal to count down options to 1
				//ASSERT( ( sudoku_board.option_count ), "0 field must have opt" );
				// go thru each field. For # found, exclude # from can_be[]
                for ( int i = 0; i < BIG_N; i++ ) 
                {
                    //row analysis
                    field = sudoku_board[ i ][ col ].field;
                    if ( field ) 
                    {
                        // we found a field
                        sudoku_board[row][col].can_be[ field ] = false;
                    } //end if
                }
                sudoku_board[row][col].option_count = options = count_fields( row, col );
                if ( options == 1 ) 
                {
                    // plug in only 1 of BIG_N numbers
                    // and set option_count to 0
                    field = find_1_field( row, col );
                    sudoku_board[row][col].field = field;
                    changes++;
                } //end if
            } //end if else
        } //end for col
    } //end for row
    return changes;
} //end horiz_vert


unsigned f(int row)
{
    switch(row)
    {
        case 0:
        case 1:
        case 2: return 0;
            
        case 3:
        case 4:
        case 5: return 3;
            
        case 6:
        case 7:
        case 8: return 6;
            
    };
}


// check all horizontal and vertical lines for empty spaces.
// each empty space initially has BIG_N options
// But for each field value in subsquare, decrease options.
// if per chance the options end up just 1, then we can plug in a number.
// return the number of fields changed from empty to a new value
unsigned subsquare( )
{ // subsquare
	unsigned changes = 0;
	unsigned options = 0;
	unsigned field   = 0;	// remember the next number to be excluded
    
	for ( int row = 0; row < BIG_N; row++ ) 
    {
		for ( int col = 0; col < BIG_N; col++ ) 
        {
			if ( sudoku_board[row][col].field ) 
            {	// there is a number
				//ASSERT( ( SRC.option_count == 0 ), "has # + option?" );
			}
            else
            {
				// field is EMPTY. Goal to count down options to 1
				//ASSERT( ( SRC.option_count ), "subsquare must have opt" );
				// analyze all fields in subsquare, exclude from can_be[]				
                    for ( int i = f( row ); i < ( f( row ) + SMALL_N ); i++ ) 
                    {
                        //ASSERT( ( i <= row+SMALL_N ), "wrong i_row in [][]" );
                        for ( int j = f( col ); j < ( f( col ) + SMALL_N ); j++ ) 
                        {
                            //ASSERT( j <= col+SMALL_N, "wrong j_col in [][]" );
                            field = sudoku_board[ i ][ j ].field;
                            if ( field ) 
                            {
                                // we found a non-zero field
                                sudoku_board[row][col].can_be[ field ] = false;
                            } //end if
                            sudoku_board[row][col].option_count = options = count_fields( row, col );
                            if ( options == 1 ) 
                            {
                                // plug in only 1 of BIG_N numbers
                                // and set option_count to 0
                                field = find_1_field( row, col );
                                sudoku_board[row][col].field = field;
                                changes++;
                            } //end if
                        } //end for j
                    } //end for i
                } //end if
            } //end for col
        } //end for row
        return changes;
    } //end subsquare
    

// simplest sudoku strategy by eliminating options for a field
// that would conflict with existing numbers in row, column, subsquare
unsigned sudoku_level0()
{ //sudoku_level0
	unsigned changes;			// count fieldsfilled in
	unsigned iterations = 0;	// count times we go around
	unsigned errors = 0;		// do final sanity check
    
	do {
        changes  = 0;
        changes  = row_analysis();
        changes += col_analysis();
        changes += subsquare();
        ++iterations;
	} while ( changes );
	//try_single_option();
#	ifdef DEBUG
    printf( "Iterated level0 %d times.\n", iterations );
    //errors = sanity_check();
#	endif // DEBUG
	return changes;
} //end sudoku_level0




int main(int argc, const char * argv[])
{

    string input_file_path;
    cout << "Enter input file path : " ;
    cin >> input_file_path ;
    read_input_board(input_file_path);
    init_input_board();
    print_board();
    
    sudoku_level0();
    
    print_board();
    return 0;
}

