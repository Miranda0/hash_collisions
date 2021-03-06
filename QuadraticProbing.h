#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;



// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class QuadraticProbing
{
  public:
    
    explicit QuadraticProbing( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

	  
	int getCollisions(){
		return collisions;
	}
	
	void setHash(int hType)
	{
		hashType = hType;
	}
	
    bool isPrime( int n )
    {
        if( n == 2 || n == 3 )
            return true;

        if( n == 1 || n % 2 == 0 )
            return false;

        for( int i = 3; i * i <= n; i += 2 )
            if( n % i == 0 )
                return false;

        return true;
    }

    int nextPrime( int n )
    {
        if( n % 2 == 0 )
            ++n;

        for( ; !isPrime( n ); n += 2 );

        return n;
    }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for(auto & entry : array){
            entry.info = EMPTY;
        }
    }

    bool insert(const HashedObj &x)
    {
            // Insert x as active
        unsigned int currentPos = (unsigned int)findPos(x);
        if( isActive(currentPos))
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( HashedObj && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    unsigned int currentSize;
	int collisions;
	int hashType;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) 
    {
        int offset = 1;
		unsigned int currentPos;
		
		if (hashType == 0)
			currentPos = (unsigned int)myhash( x );
		else if (hashType == 1)
			currentPos = (unsigned int)simplehash( x );
		else if (hashType == 2)
			currentPos = (unsigned int)prefixhash( x );
		else if (hashType == 3)
			currentPos = (unsigned int)fullhash( x );
			
        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            collisions++;
			currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
	
	size_t simplehash( const HashedObj & x ) const 
	{
		int hashVal = 0;
		
		for ( char ch : x )
			hashVal += ch;
		
		return hashVal % array.size();
		
	}
	
	size_t prefixhash( const HashedObj & x ) const 
	{
		return (x[0]+27*x[1]+729*x[2])%array.size();
	}
	
	size_t fullhash( const HashedObj & x ) const
	{
		unsigned int hashVal = 0;
		for (char ch : x)
			hashVal = 37*hashVal+ch;
		
		return hashVal % array.size();
	}
	
};

#endif
