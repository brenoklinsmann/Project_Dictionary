/*
 * Test aaplication for the Dictionary with Array Lits or DAL.
 *
 * Try to test as many DAL's methods in varying situations
 * as possible.
 *
 * */
#include <iostream>
#include <sstream>
#include <cmath>
#include <functional>

#include "dal.h"


class MyKeyComparator {
    public:
    int operator ()( int lhs , int rhs ) const {
        if ( lhs < rhs ) return -1;
        else if ( lhs == rhs ) return 0;
        else return 1; // lhs > rhs
    }
};

int main ( )
{
    int _y;   
    //#################- MY LIST -#################
    cout << "\n#################- MY LIST -#################" << endl;   
    DAL< int, std::string, MyKeyComparator  >  myList( 50 );// Lista de no máximo 50 elementos.

    std::cout << "\n>>> MyList: " << myList << std::endl;
    myList.insert( 15, "dado 1" );
    myList.insert( 2, "dado 2" );
    myList.insert( 8, "dado 3" );
    myList.insert( 0, "dado 0" );
    myList.insert( 8, "dado 3" );

    std::cout << "\n>>> MyList After Insertions: " << myList << std::endl;

    int codS =0 , codP = 0 ;
    myList.sucessor( codS , _y );
    myList.predecessor( codP, _y);

    codS =2 , codP = 2 ;
    myList.sucessor( codS , _y );
    myList.predecessor( codP, _y);

    codS =8 , codP = 8 ;
    myList.sucessor( codS , _y );
    myList.predecessor( codP, _y);

    codS =15 , codP = 15 ;
    myList.sucessor( codS , _y );
    myList.predecessor( codP, _y);

    myList.min();
    myList.max();

    myList.remove( 15, "dado 1");

    std::cout << "\n>>> MyList After Remotions: " << myList << std::endl;
    //#################- SORTED LIST -#################
    cout << "\n #################- SORTED LIST -#################" << endl; 
    DSAL< int, std::string, MyKeyComparator  >  SortedList( 50 ); // Lista de no máximo 50 elementos.

    std::cout << "\n>>> SortedList: " << SortedList << std::endl;
    SortedList.insert( 15, "dado 1" );
    SortedList.insert( 2, "dado 2" );
    SortedList.insert( 8, "dado 3" );
    SortedList.insert( 0, "dado 0" );
    SortedList.insert( 8, "dado 3" );

    std::cout << "\n>>> SortedList After Insertions: " << SortedList << std::endl;

    codS =0 , codP = 0 ;
    SortedList.sucessor( codS , _y );
    SortedList.predecessor( codP, _y);

    codS =2 , codP = 2 ;
    SortedList.sucessor( codS , _y );
    SortedList.predecessor( codP, _y);

    codS =8 , codP = 8 ;
    SortedList.sucessor( codS , _y );
    SortedList.predecessor( codP, _y);

    codS =15 , codP = 15 ;
    SortedList.sucessor( codS , _y );
    SortedList.predecessor( codP, _y);

    SortedList.min();
    SortedList.max();

    SortedList.remove( 15, "dado 1");

    std::cout << "\n>>> SortedList After Remotions: " << SortedList << std::endl;

    std::cout << "\n>>> Normal ending...\n\n";

    return EXIT_SUCCESS;
}



    /*try{
        myList.insert( 15, "dado 1" );
        myList.insert( 2, "dado 2" );
        myList.insert( 8, "dado 3" );
    }
    catch ( const length_error & e )
    {
        cout << ">>> Capturei uma exceção: " << e.what() <<endl;
    }*/

