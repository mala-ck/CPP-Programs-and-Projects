

//Program that replaces all common arithmetic operations for integer operands with recursion

#include <iostream>
using namespace std;

//Declaration of recursive methods to be defined later
int add(int,int);//integer addition
int sub(int,int);//integer subtraction
int multi(int,int);//integer multiplicaiton
int divs(int,int);//integer division
int expo(int, int);//integer exponentiation

#define MAX 6//Max range of testing input -6 to +6

int main(int argc, const char * argv[])
{
    
    //Test for recursive addition
    cout<< "Test for recursive addition \n" ;
    for(int i = -MAX; i < MAX; i++ ) 
    {	
		for(int j = -MAX; j < MAX; j++ ) 
        {
			cout<< i << " + "<< j << " = "<< add(i, j) << endl;
		} //end for
	} //end for
    
    //Test for recursive subtraction
    cout<< "\n \n Test for recursive subtraction \n" ;
    for(int i = -MAX; i < MAX; i++ ) 
    {	
		for(int j = -MAX; j < MAX; j++ ) 
        {
			cout<< i << " - "<< j << " = "<< sub(i, j) << endl;
		} //end for
	} //end for
    
    
    //Test for recursive multiplication
    cout<< "\n \n Test for recursive multiplication \n" ;
    for(int i = -MAX; i < MAX; i++ ) 
    {	
		for(int j = -MAX; j < MAX; j++ ) 
        {
			cout<< i << " * "<< j << " = "<< multi(i, j) << endl;
		} //end for
	} //end for
   
    //Test for recursive division
    cout<< "\n \n Test for recursive division \n" ;
    for(int i = -MAX; i < MAX; i++ ) 
    {	
		for(int j = -MAX; j < MAX; j++ ) 
        {
			cout<< i << " / "<< j << " = "<< divs(i, j) << endl;
		} //end for
	} //end for
        
    //Test for recursive exponentiation
    cout<< "\n \n Test for recursive exponentiation \n" ;
    for(int i = -MAX; i < MAX; i++ ) 
    {	
		for(int j = -MAX; j < MAX; j++ ) 
        {
			cout<< i << " ** "<< j << " = "<< expo(i, j) << endl;
		} //end for
	} //end for
    
    
    
    return 0;
}


//recursive Addition method
int add(int inp1, int inp2)
{
 
    if(inp2 == 0) return inp1;
    
    //If the second argument is negative integer, this case takes care of it
    if(inp2<0)
    {
        return add(--inp1, ++inp2);
    }
    else 
    {
        return add(++inp1,--inp2); 
    }
}

//Recursive subtraction method
int sub(int inp1, int inp2)
{
    if(inp2 == 0) return inp1;
    
    //If the second argument is negative integer, this case takes care of it
    if(inp2<0)
    {
        return sub(++inp1, ++inp2);
    }
    else 
    {
        return sub(--inp1,--inp2); 
    }
    
}


//Recursive multiplication method
int multi(int inp1, int inp2)
{
    if(inp2==0) return 0;
    if(inp1==0) return 0;
    
    //If the second argument is negative integer, this case takes care of it    
    if(inp2<0)
    {
        return add(-inp1,multi(inp1, ++inp2));

    }
    return add(inp1,multi(inp1, --inp2));
    
}


//Recursive division Method
int divs(int inp1, int inp2)
{
    //If denominator is zer,t hen flag eror
    if(inp2==0)
    {
        cout<<"Division by zero error\n" ;
        return 0;
    };
    
    //If numerator is zero retrun zero.
    //If absolute value of numerator and denominator, produce fraciton,then reteun zero
    if(inp1==0 || abs(inp1)<abs(inp2)) return 0;
    
    //Handle the case where numerator is  negative integer
    if(inp1<0)
    {
        if(inp2<0)
        {
            return 1+divs(inp1-inp2, inp2);
        }
        else 
        {
            return -1+divs(inp1+inp2, inp2);
        }
    }
    else if(inp2<0)//Case where denominator is negative integer
    {
        return -1+divs(inp1+inp2, inp2);
    }

    else 
    {
        return 1+divs(inp1-inp2, inp2);
    }
}


//Recursive exponentiaiton method
int expo(int base, int pow)
{
    //zero power zero is an invalid expression, so flag it
    if( base==0 && pow==0)
    {
        cout<< "Invalid expression \n";
        return 0;
    }
    //if base is zero, return zero
    if(base==0) return 0;
    //if exponent is zero, then retuen 1
    if(pow==0) return 1;
    // if exponent is negative, then also retuen zero as we do not handle fractions
    if(pow<0) return 0;
    
    return multi(base,expo(base, --pow));
    
}