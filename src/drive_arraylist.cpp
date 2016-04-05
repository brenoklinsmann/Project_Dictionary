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




int main ( )
{
    DAL< int, std::string  >  myList( 50 ); // Lista de no máximo 50 elementos.

    std::cout << "\n>>> myList: " << myList << std::endl;

    myList.insert( 15, "dado 1" );
    myList.insert( 2, "dado 2" );
    myList.insert( 8, "dado 3" );
   
    std::cout << "\n>>> myList: " << myList << std::endl;
    
    myList.remove( 15, "dado 1");


    std::cout << "\n>>> myList: " << myList << std::endl;

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

