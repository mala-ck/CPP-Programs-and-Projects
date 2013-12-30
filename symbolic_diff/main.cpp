/* Implement program diff that conducts differentiation of a function f(x) with respect to variable ‘x’. 
 Input to diff is a restricted arithmetic formula f(x), such a 2*x+x*(8-x*5)$, terminated by ‘$’. 
 The first output is input formula f(x), but with parenthesis explicitly showing precedence. 
 The second output is the first derivative f’(x) of the input formula. 
 The third output is a simplified first derivative f’(x)  
 */

#include <iostream> 
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

string input_expression;// variable to store the input expression entered by the user
int nxt_char_index = 0; // index pointing to next character to be processed in the expression
char nxt_char; // store for the next char read

//Method to return one character at a time from the input expression
char GetNextChar()
{
    nxt_char = input_expression[nxt_char_index];
    nxt_char_index++;
    return nxt_char;
    
}

//Enum for different type of content a node can have
typedef enum { Literal, Identifier, Operator } NodeClass;

// pinter to structure declared below. NodePtr is a pointer to structure type TreeNode
typedef struct TreeNode* NodePtr; 

struct TreeNode
{
    NodeClass nodeClass; //flag for the type of content
    char symbol;         //identifier or literal like x
    int litVal;         //literal values of single digit integer 0...9
    NodePtr left_tree;  //left subtree
    NodePtr right_tree; //right subtree
        
};

//Constant value nodes whihc store 0 or 1
TreeNode NullNode;
TreeNode OneNode;

//Method to initialize 0 value node
void InitializeNullNode()
{
    NullNode.nodeClass = Literal;
    NullNode.litVal = 0;
    NullNode.symbol = '0';
    NullNode.left_tree = NULL;
    NullNode.right_tree = NULL;
    
}

//method to initialize 1 value node
void InitializeOneNode()
{
    OneNode.nodeClass = Literal;
    OneNode.litVal = 1;
    OneNode.symbol = '1';
    OneNode.left_tree = NULL;
    OneNode.right_tree = NULL;
    
}


//Method to create Node
NodePtr Make (NodeClass node_class_in, char symbol_in, int litVal_in , NodePtr left_in, NodePtr right_in)
{
    NodePtr Node = (NodePtr)malloc(sizeof(struct TreeNode));

    if (Node==NULL) exit (1);	
    
    Node->nodeClass  = node_class_in;
	Node->symbol = symbol_in;
	Node->litVal = litVal_in;
	Node->left_tree   = left_in;
	Node->right_tree  = right_in;
	return Node;
}

//Method to delete node
int Delete(NodePtr node)
{
    
    if(node == NULL)
    {
        return 0;
    }
    
    if(node->left_tree != NULL)
    {
        Delete(node->left_tree);
    }
    
    if(node->right_tree !=NULL)
    {
        Delete(node->right_tree);
    }
    
    if(node!=NULL)
    {
        
        delete node;
        node = NULL;
    }
    return 0;
}

//Method to delete entire tree and release the dynamic memory allotted
int DeleteTree(NodePtr Root)
{
    if ( Root == NULL ) 
    {
        return 0;
    }
    else if(Root->left_tree == NULL && Root->right_tree==NULL)
    {
        Delete(Root);
    }
    else
    {
        DeleteTree(Root->right_tree);
        DeleteTree(Root->left_tree);
    }
    
    return 0;
    
}


//Method which returns a copy of the tree passed to it
NodePtr Copy( NodePtr Root )
{ // Copy
	if ( Root == NULL ) 
    {
        return NULL;
	}
    else
    {
        return Make( Root->nodeClass, Root->symbol,
                    Root->litVal,
                    Copy( Root->left_tree ),
                    Copy( Root->right_tree )
                    );
	} //end if
} //end Copy


//Method to print tree and its corresponding expression with operator precedence depicted by appropriate braces
void PrintTree( NodePtr Root )
{ 
    // PrintTree
    if ( Root != NULL ) 
    {
        if ( Root->nodeClass == Operator ) 
        {
            cout<< "(" ;
        } //end if
        PrintTree( Root->left_tree );
        if ( Root->nodeClass == Literal ) 
        {
            cout<<Root->litVal;
        }else
        {
            cout<<Root->symbol ;
        } //end if
        PrintTree( Root->right_tree );
        if ( Root->nodeClass == Operator ) 
        {
            cout<< ")" ;
        } //end if
    } //end if
} //end PrintTree


//Forward declaration of Expression method
NodePtr Expression();


// parse expression and build tree
// using Term() and higher priority functions/ops
// all returning pointers to nodes
// in Expression() handle ‘+’ and ‘-’ operators

NodePtr primary()
{   
    // primary
    char Symbol = GetNextChar();		// first_set = { ‘(‘, ‘&’, IDENT, LIT } 
    NodePtr Temp;
    
    if ( isdigit(Symbol)) 
    {
        // end node: no recursion
        return Make( Literal, Symbol, (int)(Symbol-'0'), NULL, NULL );
    }
    else
    if ( isalpha(Symbol)) 
    {
        // also end node
        return Make( Identifier, tolower( Symbol ), 0, NULL, NULL );
    }
    else if ( '(' == Symbol ) 
    {
        Temp = Expression();
        if(nxt_char == ')' )
        {
            return Temp;
        }
        else
        {
            cout<< "Error missing right braces"<<endl;
            return NULL;
        }
    }
    else if ( Symbol == '&' ) 
    {
        return Make(  Operator, '&', 0, NULL, primary() );
    }
    else
    {
        cout<<"Illegal character " << Symbol <<endl;
        return NULL;
    } //end if
} //end primary


// handle exponentiation operator ‘^’
NodePtr Factor()
{ 
    // Factor
	NodePtr Left = primary();
    
    GetNextChar();
    
	while ( nxt_char == '^' ) 
    {
     	Left = Make( Operator, '^', 0, Left, primary() );
        GetNextChar();
    } //end while
    
    return Left;
} //end Factor



// multiply operators ‘*’ and ‘/’, later add ‘%’
NodePtr Term()
{ // Term
	char Op;
	NodePtr Left = Factor();
    
	while ( nxt_char == '*' || nxt_char == '/' ) 
    {
     	Op = nxt_char;			// remember ‘*’ or ‘/’
     	Left = Make( Operator, Op, 0, Left, Factor() );
    } //end while
    
    return Left;
} //end Term


//Constructing a tree from expression
NodePtr Expression()
{ 
    // Expression
	char Op;// remember ‘+’ or ‘-’
	NodePtr Left = Term();	// handle all higher prior.
    
	while ( nxt_char == '+' || ( nxt_char == '-' )) 
    {
        Op = nxt_char;			// remember ‘+’ or ‘-’
        Left = Make(Operator, Op, 0, Left, Term());
	} //end while
    
    return Left;
} //end Expression
           
     
//Fucntion to find the first derivative of ane xpression or function
NodePtr Derive( NodePtr Root )
{ 
    // Derive
	if ( NULL == Root ) 
    {
        return NULL;
	}
    else
    {
        switch ( Root->nodeClass ) 
        {
		    case Literal: 
				return Make( Literal, '0', 0, NULL, NULL );
                
		    case Identifier:
				if ( ( Root->symbol == 'x' ) || ( Root->symbol == 'X' ) ) 
                {
			    	return Make( Literal, '1', 1, NULL, NULL );
				}
                else
                {
			    	return Make( Literal, '0', 0, NULL, NULL );
				} //end if
                
			case Operator:
                switch ( Root->symbol ) 
                {
					case '+': case '-':
                        return Make( Operator, Root->symbol, 0,
                                    Derive( Root->left_tree ), Derive( Root->right_tree ) );
                    case '*':
                        return Make( Operator, '+', 0,
                                    Make( Operator, '*', 0, Derive( Root->left_tree ),
                                         Copy( Root->right_tree ) ),
                                    Make( Operator, '*', 0, Copy( Root->left_tree ),
                                         Derive( Root->right_tree ) ) );
                    case '/':
                        return Make( Operator, '/', 0,
                                    Make( Operator, '-', 0,
                                         Make( Operator, '*', 0, Derive( Root->left_tree ),
                                              Copy( Root->right_tree ) ),
                                         Make( Operator, '*', 0, Copy( Root->left_tree ),
                                              Derive( Root->right_tree ) ) ),
                                    Make( Operator, '*', 0,
                                         Copy( Root->right_tree ), Copy( Root->right_tree ) ) );
                        
                    case '^':
                        return
                        Make( Operator, '+', 0,
                             Make( Operator, '*', 0,
                                  Derive( Root->left_tree ),
                                  Make( Operator, '*', 0,
                                       Copy( Root->right_tree ),
                                       Make( Operator, '^', 0,
                                            Copy( Root->left_tree ),
                                            Make( Operator, '-', 0,
                                                 Copy( Root->right_tree ),
                                                 Copy( & OneNode ) ) ) ) ),
                             Make( Operator, '*', 0,
                                  Make( Operator, '*', 0,
                                       Make( Operator, '&', 0,
                                            NULL,
                                            Copy( Root->left_tree ) ),
                                       Derive( Root->right_tree ) ),
                                  Make( Operator, '^', 0,
                                       Copy( Root->left_tree ),
                                       Copy( Root->right_tree ) ) ) );
                        
                    case '&':
                        if ( Root->left_tree != NULL ) 
                        {
                            cout<<"ln has only one operand.\n";
                        } //end if
                        else 
                        {
                            return 
                            Make(Operator, '/', 0, Derive(Root->right_tree), Copy(Root->right_tree) );
                        }
                        // now do the work ...
                         
                        
                    
                }; //end inner switch
        };//end outer swithc
    }//end else
    return NULL;
}//end function
    
//Function to check if the character is an literal
bool IsLit(char c, NodePtr np)
{
    char ac[1] ;
    ac[0] = c;
    int int_val= atoi(ac);
    
    /*/if node is null, then it means it is zero
    if(np==NULL && int_val == 0)
    {
        return true;
    }*/
    
    if(np==NULL)
    {
        return false;
    }

    if((np->nodeClass == Literal) && (int_val == np->litVal))
    {
        return true;
    }
    else 
    {
        return false;
    }
    
}

//Function to check if both nodes are literal nodes
bool BothLit(NodePtr n1, NodePtr n2)
{
    if( (n1->nodeClass == Literal) && (n2->nodeClass==Literal))
    {
        return true;
    }
    else 
    {
        return false;
    }
}


//Funciton to check if the operator is associative
bool is_associative(char c)
{
    if(c=='+' || c== '-' || c=='*')
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// return true only if both subtrees left and right are equal
bool IsEqual( NodePtr Left, NodePtr Right )
{ // IsEqual
    if ( ( !Left ) && ( !Right ) ) 
    {
        return true;
    }
    else if ( NULL == Left ) 
    {
        // Right is known to be not NULL
        return false;
    }
    else if ( NULL == Right ) 
    {
        // Left is known to be NOT NULL
        return false;
    }
    else if ( ( Left->nodeClass == Literal ) && ( Right->nodeClass == Literal ) ) 
    {
        return ( Left->litVal ) == ( Right->litVal );
    }
    else if ( ( Left->nodeClass == Identifier ) && ( Right->nodeClass == Identifier ))
    {
        return ( Left->symbol ) == ( Right->symbol );
    }
    else
    {
        // must be Operator; same?
        if ( ( Left->symbol ) == ( Right->symbol ) ) 
        {
            // IsEqual yields true, only if both subtrees are equal
            return ( IsEqual( Left->left_tree, Right->left_tree ) &&
                    IsEqual( Left->right_tree, Right->right_tree ) ) ||
            ( is_associative( Left->symbol ) &&
			 IsEqual( Left->left_tree,  Right->right_tree ) &&
			 IsEqual( Left->right_tree, Right->left_tree ) );
        }
        else
        {
            return false;
        } //end if
    } //end if
    cout<<"Impossible to reach in IsEqual.\n" ;
} //end IsEqual



//Funciton ot simplify expresisons like 1+2 to be 3
NodePtr Simplify( NodePtr Root ) 
{ // Simplify
	int val = 0;			// accumulate integer values from + - * etc.
	if ( !Root ) 
    {
        return Root;
	}
    else
    {
        switch ( Root->nodeClass ) 
        {
            case Literal:
            case Identifier:
				return Root;
                
            case Operator:
                Root->left_tree  = Simplify( Root->left_tree );
                Root->right_tree = Simplify( Root->right_tree );
                switch ( Root->symbol ) {
        			case '+':
                        if ( IsLit( '0', Root->left_tree ) ) 
                        {
							return Root->right_tree;
                        }
                        else if ( IsLit( '0', Root->right_tree ) ) 
                        {
							return Root->left_tree;
                        }
                        else if ( BothLit( Root->left_tree, Root->right_tree ) ) 
                        {
							val = Root->left_tree->litVal + Root->right_tree->litVal;
							return Make( Literal, (char)( val + '0' ), val,
                                        NULL, NULL );
                        }
                        else
                        {
							return Root; // no other simplifiction for ‘+’
						} //end if
                    case '-':
                        if ( IsLit( '0', Root->right_tree ) ) 
                        {
                            return Root->left_tree;
                        }
                        else if ( BothLit( Root->left_tree, Root->right_tree ) ) 
                        {
                            val = Root->left_tree->litVal - Root->right_tree->litVal;
                            return Make( Literal, (char)( val + '0' ), val, NULL, NULL );
                        }
                        else if ( IsEqual( Root->left_tree, Root->right_tree ) ) 
                        {
                            return &NullNode;
                        }
                        else
                        {
                            return Root;
                        } //end if
                    case '*':
                        if ( IsLit( '1', Root->left_tree ) ) 
                        {
                            return Root->right_tree;
                        }else if ( IsLit( '1', Root->right_tree ) ) 
                        {
                            return Root->left_tree;
                        }else if ( IsLit( '0', Root->left_tree ) || IsLit( '0', Root->right_tree ) ) 
                        {
                            return &NullNode;
                        }
                        else if ( BothLit( Root->left_tree, Root->right_tree ) ) 
                        {
                            val = Root->left_tree->litVal * Root->right_tree->litVal;
                            return Make( Literal, (char)( val + '0' ), val, NULL, NULL );
                        }
                        else
                        {
                            return Root;
                        }//end if
                    case '/':
                        if ( IsLit( '1', Root->right_tree ) ) 
                        {
                            return Root->left_tree;
                        }
                        else if ( IsLit( '0', Root->left_tree ) ) 
                        {
                            return &NullNode;
                        }
                        else if ( IsEqual( Root->left_tree, Root->right_tree ) ) 
                        {
                            return &OneNode;
                        }
                        else if ( BothLit( Root->left_tree, Root->right_tree ) ) 
                        {
                            val = Root->left_tree->litVal / Root->right_tree->litVal;
                            return Make( Literal, (char)( val + '0' ), val, NULL, NULL );
                        }
                        else
                        {
                            return Root;
                        } //end if
                    case '^':
                        if ( IsLit( '0', Root->right_tree ) ) 
                        {
                            return &OneNode;
                        }
                        else if ( IsLit( '1', Root->right_tree ) ) 
                        {
                            return Root->left_tree;
                        }
                        else if ( BothLit( Root->left_tree, Root->right_tree ) ) 
                        {
                            val = pow(Root->left_tree->litVal, Root->right_tree->litVal);
                            return Make( Literal, (char)( val + '0' ), val, NULL, NULL );
                        }
                        else
                        {
                            return Root;
                        } //end if
                    case '&':
                        if(IsLit('0', Root->right_tree ) )
                        {
                            cout<< "ln log of 0 doesn't exist" <<endl;
                        }
                        if( IsLit( '1', Root->right_tree ) ) 
                        {
                            return &OneNode;
                        }
                        else if (!isnumber(Root->right_tree->litVal) ) 
                        {
                            val = log(Root->right_tree->litVal);
                            return Make( Literal, (char)( val + '0' ), val, NULL, NULL );
                        }                        
                        else
                        {
                            return Root;
                        } //end if

                };//end of inner switch
        };//end of outer switch
    }//end of else
         
    return NULL;
}



//Main function for differentiation
int main(int argc, const char * argv[])
{
    NodePtr root = NULL;
    
    InitializeNullNode();
    InitializeOneNode();
    
    
    cout<< "\n \n Enter the mathematical expression ending in $ /say eg x+2x$ : " ;
    
    cin >> input_expression;
    
    if(input_expression[input_expression.length()-1] != '$')
    {
        cout<< "Expected $ at the end of the expression, not found " <<endl;
    }
    else 
    {
        int len_exp = input_expression.length();
        input_expression = input_expression.substr(0, len_exp-1);
        
        root = Expression();
        cout << "The original f(x) is : ";
        PrintTree(root);
        cout<<endl;
        
        root = Simplify(root);
        cout << "The simplified f(x) is : ";
        PrintTree(root);
        cout<<endl;
        
        root = Derive(root);
        cout<<"The first derivative of the expression is : ";
        PrintTree(root);
        cout<< endl;
        
        
        root = Simplify(root);
        cout << "The simplified derivative f'(x) is : ";
        PrintTree(root);
        cout<<endl;
        
    }
    
    DeleteTree(root);
    
    
    return 0;
}

