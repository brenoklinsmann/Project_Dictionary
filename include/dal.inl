/**
 * DAL class implementation.
 *
 */

#include "dal.h"

/**
 * ---------------------------------------------------------------------------
 * Common methods from DAL.
 * ---------------------------------------------------------------------------
 */

// Construtor inicializa TAD.
template < typename Key, typename Data >
DAL<Key,Data>::DAL ( int _iMaxSz ) :
    mi_Length( 0 ),         // Tamanho logico.
    mi_Capacity( _iMaxSz ), // Guardar capacidade atual.
    mpt_Data( nullptr )
{
    if ( _iMaxSz < 0 )          // Nao aceitamos lista com tamanho negativo.
        throw std::invalid_argument( "[DAL()]: Tamanho de lista invalido!" );
    mpt_Data = new NodeAL[ _iMaxSz ]; // Tamanho maximo.
}

template < typename Key, typename Data >
int DAL<Key, Data>::_search( Key _x ) const
{
	auto i(0);
	for(/*Empty*/; mpt_Data[i].id != _x and i < mi_Length; i++)
		/*Empty*/;
	return i;

}

template < typename Key, typename Data >
bool DAL<Key, Data>::search( const Key & _x, Data & _result ) const
{
	auto idx = _search(_x);

	if ( idx == mi_Length ) return false;
	
	_result = mpt_Data[ idx ].info;

	return true;
}


template < typename Key, typename Data >
bool DAL<Key, Data>::insert(const Key & _novaId, const Data & _novaInfo)
{
	int idx = _search( _novaId );

	if ( idx == mi_Length  ) {

		mpt_Data[mi_Length].id = _novaId;
		mpt_Data[mi_Length].info = _novaInfo;
		mi_Length++;

		return true;
	}else return false;
}

template < typename Key, typename Data >
bool DAL<Key, Data>::remove( const Key & _x, const Data & _info )
{
	int idx = _search( _x );
	auto info = _info;
	if (idx == mi_Length) return false;
	for(int i = idx; i< mi_Length - 1; i++)
	{
		mpt_Data[i].id = mpt_Data[i+1].id;
		mpt_Data[i].info = mpt_Data[i+1].info; 
	}
	mi_Length--;
	return true;
}



