/* Find all strongly connected components (SCC) in a graph, and print them out. 
 For each input, generate the graph, analyze the graph for strong connectivity, 
 and then produce 2 outputs, one with singleton-node SCCs, the other with singleton-nodes filtered out.
 The program reads input from stdin to build a graph G, 
 peforms SCC analysis according to Tarjan, and then prints information, explaining clearly, which nodes in G form SCCs. 
 */

#include <iostream>
using namespace std;
#include <stack>


// node may have any number of successors
// all need to be retrieved.
// so each node in G has a link pointer,
// pointing to Linked List of all successor nodes.
// Last one connected is the first one inserted

typedef struct link_tp * link_ptr_tp;	// forward ref

typedef struct node_tp * node_ptr_tp;


typedef struct link_tp
{
	link_ptr_tp	next_link;	// point to next link
	node_ptr_tp	next_node;	// point to successor node
} str_link_tp;

#define LINK_SIZE sizeof( str_link_tp )

node_ptr_tp finger = NULL;


typedef struct node_tp
{
	link_ptr_tp	link;		// points to LL of successors
	node_ptr_tp	finger;	// finger through all nodes
	int				name;		// name given at creation
	bool		   visited;	// to check connectivity
    int number;
    int lowlink;
    node_ptr_tp scc_pred;
    
} str_node_tp;

#define NODE_SIZE sizeof( str_node_tp )



// create a node in graph G, identified by “name”
// connect to the global “finger” at head of Llist

node_ptr_tp make_node( int name )
{ // make_node
	node_ptr_tp node = (node_ptr_tp) malloc( NODE_SIZE );
	if(node == NULL) 
    {
        std::cout << "insufficient memory" ;
    }
	// check once non-Null here, not oftenß on user side!
	node->finger	   = finger;	// re-assign finger!!
	node->lowlink	= 0;		// int. not pointer
	node->number	   = 0;		// int type
	node->link	   = NULL;		// pointer type
	node->name	   = name;		// IDs this node
	node->visited	= false;		// initially
	finger	= node;// now link to “this”
	return node;
} //end make_node


// check if the node with given name exists
bool exists(int node_name)
{
    node_ptr_tp trace = finger;
    while(trace != NULL)
    {
        if(trace->name == node_name)
        {
            return true;
        }
        else 
        {
            trace = trace->finger;
        }
    }
    return false;
    
}

node_ptr_tp get_node(int node_name)
{
    node_ptr_tp trace = finger;
    while(trace != NULL)
    {
        if(trace->name == node_name)
        {
            return trace;
        }
        else 
        {
            trace = trace->finger;
        }
    }
    return NULL;

}
// check, whether link between these 2 nodes already exists
// if not, return true: New! Else return false, NOT new!
bool new_link( node_ptr_tp first, node_ptr_tp second )
{ // new_link
	int target			= second->name;
	link_ptr_tp link	= first->link;
    
	while ( link ) {
        if ( target == link->next_node->name ) {
            return false; // it is an existing link, NOT new
        } //end if
        // check next node; if any
        link = link->next_link;
	} //end while
	// none of successors equal the second node's name
	return true; // is a new link
} //end new_link


//link first node to secod. As second is the successor of firs
void make_link(node_ptr_tp first, node_ptr_tp second)
{
    //create a new link object
    link_ptr_tp new_lnk = (link_ptr_tp) malloc( LINK_SIZE );
    if(new_lnk == NULL)
    {
        cout << "Unable to create link" ;
        return ;
    }

    new_lnk->next_link = NULL;
    new_lnk->next_node = second;
    
    //if the link linked list is empty , then add the newly created node as first node
    if(first->link == NULL)
    {
        first->link = new_lnk;
    }
    else //if there are already nodes int he link linked list, then add the new node ot the beginning
    {
        new_lnk->next_link = first->link->next_link;
        first->link = new_lnk;
        
    }
    
    return  ;
}


int buildGraph()
{
    int a, b;
    node_ptr_tp first, second;
    // input is list of pairs, each element being a node name
    // craft edge from first to second name = number
    // If a node is new: create it; else use ptr = exists()
    while(1) 
    { 		
        cout << "Enter edge : " ;

        // a, b are ints
        cin >> a >> b;
        
        if( a== 0 | b== 0)
        {
            break;
        }
        if ( ! exists( a )  ) 
        {	// ‘a’ new node
			first = make_node( a );				// allocate ‘a’
		} //end if
        else 
        {
            first = get_node(a);
        }
		if ( ! exists( b )  ) 
        {	// ‘b’ new node
			second = make_node( b );			// allocate ‘b’
		}
        else 
        {
            second = get_node(b);
        }//end if
        // both exist. Either created, or pre-existed: Connect!
		if ( new_link( first, second ) ) 
        {
			//link = make_link( first->link, second );
            make_link( first, second );

            /*if (link == NULL)
            {
                
                cout<< "No space for link \n" ;
            }*/
			//first->link = link;
		}else
        {
			// link was there already, no need to add again!
			cout << "<><> skip duplicate link\n";
		} //end if


    } //end while
    
    return 0;
}


// globals for scc
int				scc_number	= 0;	// Tarjan's SCC numbers
node_ptr_tp	scc_stack	= NULL;	// stack exists via link in nodes
int				scc_count	= 0;	// tracks # of SCCs

// initial point of stack is global "scc_stack"
// each node has scc_pred link, linking up in fashion of a stack
void push( node_ptr_tp v )
{ // push
    if(v == NULL)
    {
        return;
    }
    if(!v->visited)
    {    
        v->scc_pred	= scc_stack;	// first time NULL, then stack ptr
        v->visited	= true;			// will be handled now
        scc_stack	= v;			// global pts ID’s head
    }
} //end push

// starting with global scc_stack, we can traverse whole stack
// all elements are connected by node field scc_stack
void pop()
{ // pop
	//ASSERT( scc_stack, "error, empty SCC stack" );
    if(scc_stack == NULL)
    {
        return;
    }
	scc_stack->visited 	= false; 	// remove from stack
	scc_stack 			= scc_stack->scc_pred;
} //end pop


void scc( node_ptr_tp v )
{ // scc
	node_ptr_tp w;
    
    if(v == NULL)
    {
        return;
    }
    if(v->number != 0) // i.e if the node is already visited, then return
    {
        return ;
    }
    
    v->number = v->lowlink = ++scc_number;
    push( v );
    
    for( link_ptr_tp link=v->link; link; link=link->next_link ) 
    {
        w = link->next_node;
               //ASSERT( w, “node w linked as successor must be /= 0" );
                      if( w->number == 0 ) 
                      {		// alias for “->visited”
                          scc( w );
                          v->lowlink = min( v->lowlink, w->lowlink );
                      }
                      else if( w->number < v->number ) 
                      {
                          // frond, AKA “cross link”
                          if( w->visited ) 
                          {
                              v->lowlink = min( v->lowlink, w->number );
                          } //end if
                      } //end if
    } //end for
    
    // now see, whether v is part of an SCC
    // and if so, record SCC  number and all nodes belonging to it
    if ( v->lowlink == v->number ) 
    {
        // found next scc; but if singleton node SCC, then skip it
        if ( scc_stack == v ) 
        {
            // yes, singleton node; so be silent! Uninteresting!
            pop();
        }
        else
        {
            // multi-node scc; THAT we do consider
            scc_count++;
            cout << "next scc number is: " << scc_count << endl;
            while( scc_stack && ( scc_stack->number >= v->number ) ) 
            {
                cout << "node " << scc_stack->name << " is in." << endl;
                pop();
            } //end while
        } //end if
    } //end if
    
} //end scc
                      
int main(int argc, const char * argv[])
{
    int start_node_name = 0;
    cout<< "Input graph edges in form a b \n" ;
    
    buildGraph();
        
    node_ptr_tp traverse = finger;
    
    cout << "graph is : \n" ;
    
    while(traverse != NULL)  
    {
        if(traverse->visited)
        {
            traverse = traverse->finger;
            continue;
        }
        scc(traverse);
        traverse = traverse->finger;

        
    }
     
    return 0;
}

