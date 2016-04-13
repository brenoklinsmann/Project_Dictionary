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

template <typename Key, typename Data, typename MyKeyComparator>
DAL<Key,Data, MyKeyComparator>::DAL ( int _iMaxSz ) :
    mi_Length( 0 ),         // Tamanho logico.
    mi_Capacity( _iMaxSz ), // Guardar capacidade atual.
    mpt_Data( nullptr )
{
    if ( _iMaxSz < 0 )          // Nao aceitamos lista com tamanho negativo.
        throw std::invalid_argument( "[DAL()]: Tamanho de lista invalido!" );
    mpt_Data = new NodeAL[ _iMaxSz ]; // Tamanho maximo.
}

template <typename Key, typename Data, typename KeyComparator>
int DAL<Key, Data, KeyComparator>::compare(Key _x, Key _y) const {
    KeyComparator comp;
    return comp(_x, _y);
}

template <typename Key, typename Data, typename MyKeyComparator>
int DAL< Key, Data, MyKeyComparator >::_search( Key _x ) const
{
	auto i(0);
	for (i = 0; compare(mpt_Data[i].id, _x) != 0 and i < mi_Length; i++);
	//for(/*Empty*/; mpt_Data[i].id != _x and i < mi_Length; i++)
	//	/*Empty*/;
	return i;

}

template <typename Key, typename Data, typename MyKeyComparator>
bool DAL< Key, Data, MyKeyComparator >::search( const Key & _x, Data & _result ) const
{
	auto idx = _search(_x);

	if ( compare(idx, mi_Length) ==0 ) return false;
	
	_result = mpt_Data[ idx ].info;

	return true;
}


template <typename Key, typename Data, typename MyKeyComparator>
bool DAL< Key, Data, MyKeyComparator >::insert(const Key & _novaId, const Data & _novaInfo)
{
	int idx = _search( _novaId );

	if ( compare(idx, mi_Length) ==0  ) {

		mpt_Data[mi_Length].id = _novaId;
		mpt_Data[mi_Length].info = _novaInfo;
		mi_Length++;
		cout << "\n>>> Chave " << _novaId <<" inserida!"<< endl;

		return true;
	}
	cout << "\n>>> Chave " << _novaId <<" já existe!"<< endl;
	return false;
}

template <typename Key, typename Data, typename MyKeyComparator>
bool DAL< Key, Data, MyKeyComparator >::remove( const Key & _x, const Data & _info )
{
	int idx = _search( _x );
	auto info = _info;
	if ( compare(idx, mi_Length) ==0 ) return false;
	mpt_Data[idx].id = mpt_Data[mi_Length-1].id;
	mpt_Data[idx].info = mpt_Data[mi_Length-1].info;
	/*for(int i = idx; i< mi_Length - 1; i++)
	{
		mpt_Data[i].id = mpt_Data[i+1].id;
		mpt_Data[i].info = mpt_Data[i+1].info; 
	}*/
	cout << "\n>>> Removendo a chave " << _x << endl;	
	mi_Length--;
	return true;
}

template <typename Key, typename Data, typename MyKeyComparator >
Key DAL< Key, Data, MyKeyComparator >::min() const
{	
	if( mi_Length > 0 )
	{
	
		Key menor = mpt_Data[0].id;
		for (int i = 1; compare(i, mi_Length) ==-1 ; i++)
		{
			if ( compare(mpt_Data[i].id, menor) == -1 )
					menor = mpt_Data[i].id;

		}
		std::cout << "\n>>> Mínimo: " << menor << std::endl;
		return menor;
	}
	throw std::invalid_argument( "[DAL()]: Vetor Vazio!" );
}

template <typename Key, typename Data, typename MyKeyComparator >
Key DAL< Key, Data, MyKeyComparator >::max() const
{
	if( mi_Length > 0 )
	{
		Key maior = mpt_Data[0].id;
		for (int i = 1; compare(i, mi_Length) ==-1; i++)
		{
			if ( compare(mpt_Data[i].id, maior) == 1 )
				maior = mpt_Data[i].id;

		}
		std::cout << "\n>>> Máximo: " << maior << std::endl;
		return maior;
	}
	throw std::invalid_argument( "[DAL()]: Vetor Vazio!" );

}

template <typename Key, typename Data, typename MyKeyComparator >
bool DAL< Key, Data, MyKeyComparator >::sucessor ( const Key & _x , Key & _y ) const
{
	int idx = _search( _x );
	if ( compare(idx, mi_Length) == 0 ) return false;
	if ( compare(idx, mi_Length -1) == 0) {
		_y = -1;
		cout << "\n>>> Sucessor de "<< _x <<" não existe!" <<endl;
	}else{ 
		_y = mpt_Data[idx+1].id;
		cout << "\n>>> Sucessor de "<< _x <<" : " << _y <<endl;
	}	
	return true;	
}

template <typename Key, typename Data, typename MyKeyComparator >
bool DAL< Key, Data, MyKeyComparator >::predecessor ( const Key & _x , Key & _y ) const
{
	int idx = _search( _x );
	if ( compare(idx, mi_Length) == 0 ) return false;
	if ( idx == 0){ 
		_y = -1;
		cout << "\n>>> Predecessor de "<< _x <<" não existe!" <<endl;
	}else{
	 	_y = mpt_Data[idx-1].id;
	 	cout << "\n>>> Predecessor de "<< _x <<" : " << _y <<endl;
		
	}
	return true;
}


/**
 * ---------------------------------------------------------------------------
 * Common methods from DSAL.
 * ---------------------------------------------------------------------------
 */ 

template <typename Key, typename Data, typename MyKeyComparator >
int DSAL< Key, Data, MyKeyComparator >::_search ( const Key & _x) const
{
	auto &Data_DSAL = DAL< Key, Data, MyKeyComparator >::mpt_Data;
	
	int left = 0, rigth = DAL< Key, Data, MyKeyComparator >::mi_Length;
	
	if ( DAL< Key, Data, MyKeyComparator >::mi_Length == DAL< Key, Data, MyKeyComparator >::mi_Capacity)
		throw std::invalid_argument( "[DSAL()]: Vetor Cheio" );
	
	while ( left <= rigth )
	{
		int media = ( left + rigth )/2;	
		if ( DAL< Key, Data, MyKeyComparator >::compare(Data_DSAL[media].id, _x) == 0 ) return media;
		if ( DAL< Key, Data, MyKeyComparator >::compare(Data_DSAL[media].id, _x) == 1 ) rigth = media -1;
		if ( DAL< Key, Data, MyKeyComparator >::compare(Data_DSAL[media].id, _x) == -1 ) left = media + 1;
	}
	return DAL< Key, Data, MyKeyComparator >::mi_Length;
}

template <typename Key, typename Data, typename MyKeyComparator >
bool DSAL< Key, Data, MyKeyComparator >::insert( const Key & _novaId, const Data & _novaInfo )
{
	auto &Data_DSAL = DAL< Key, Data, MyKeyComparator >::mpt_Data;
	auto &Length = DAL< Key, Data, MyKeyComparator >::mi_Length;
	int idx = _search( _novaId );
	if ( idx != Length ){ 
		cout << "\n>>> Chave " << _novaId <<" já existe!"<< endl;
		return false;
	}
	if (Length == 0 ){
		DAL< Key, Data, MyKeyComparator >::mpt_Data[0].id = _novaId;
		Data_DSAL[0].info = _novaInfo;
		Length++;
		cout << "\n>>> Chave " << _novaId <<" inserida!"<< endl;
		return true;
	}

	for (int i=0;i < Length ; i++)
	{
		if ( DAL< Key, Data, MyKeyComparator >::compare(Data_DSAL[i].id, _novaId) == 1 )
		{
			for (int j= Length;j>i; j--)
			{
				Data_DSAL[j] = Data_DSAL[j-1];
				//Data_DSAL[j].info = Data_DSAL[j-1].info;
			}
			Data_DSAL[i].id = _novaId;
			Data_DSAL[i].info = _novaInfo;
			Length++;
			cout << "\n>>> Chave " << _novaId <<" inserida!"<< endl;
			return true;
		}
	}
}

template <typename Key, typename Data, typename MyKeyComparator >
bool DSAL< Key, Data, MyKeyComparator >::remove( const Key & _x, const Data & _info )
{
	auto &Data_DSAL = DAL< Key, Data, MyKeyComparator >::mpt_Data;
	auto &Length = DAL< Key, Data, MyKeyComparator >::mi_Length;
	int idx = _search( _x );
	if ( idx == Length ) return false;
	for(int i = idx; DAL< Key, Data, MyKeyComparator >::compare(i, Length - 1) == -1; i++)
	{
		Data_DSAL[i].id = Data_DSAL[i+1].id;
		Data_DSAL[i].info = Data_DSAL[i+1].info; 
	}
	cout << "\n>>> Removendo a chave " << _x << endl;
	Length--;
	return true;
}

template <typename Key, typename Data, typename MyKeyComparator>
Key DSAL< Key, Data, MyKeyComparator >::max() const
{
	auto &Length = DAL< Key, Data, MyKeyComparator >::mi_Length;
	if ( Length == 0 )
		throw std::invalid_argument( "[DSAL()]: Vetor Vazio!" );

	std::cout << "\n>>> Máximo: " << DAL< Key, Data, MyKeyComparator >::mpt_Data[Length-1].id << std::endl;
	return DAL< Key, Data, MyKeyComparator >::mpt_Data[Length-1].id;

}

template <typename Key, typename Data, typename MyKeyComparator >
Key DSAL< Key, Data, MyKeyComparator >::min() const
{
	if ( DAL< Key, Data, MyKeyComparator >::mi_Length == 0)
		throw std::invalid_argument( "[DSAL()]: Vetor Vazio!" );

	std::cout << "\n>>> Mínimo: " << DAL< Key, Data, MyKeyComparator >::mpt_Data[0].id << std::endl;

	return DAL< Key, Data, MyKeyComparator >::mpt_Data[0].id;
}

template <typename Key, typename Data, typename MyKeyComparator >
bool DSAL< Key, Data, MyKeyComparator >::sucessor ( const Key & _x , Key & _y ) const
{
	auto Length = DAL< Key, Data, MyKeyComparator >::mi_Length;
	int idx = _search( _x );
	if ( DAL< Key, Data, MyKeyComparator >::compare(idx, Length) == 0 ) return false;
	if ( DAL< Key, Data, MyKeyComparator >::compare(idx, Length -1) ==0 ){
		_y = -1;
		cout << "\n>>> Sucessor de "<< _x <<" não existe!" <<endl;
	}else {
		_y = DAL< Key, Data, MyKeyComparator >::mpt_Data[idx+1].id;
		cout << "\n>>> Sucessor de "<< _x <<" : " << _y <<endl;
	}
	return true;	
}

template <typename Key, typename Data, typename MyKeyComparator >
bool DSAL< Key, Data, MyKeyComparator >::predecessor ( const Key & _x , Key & _y ) const
{
	int idx = _search( _x );
	auto &Length = DAL< Key, Data, MyKeyComparator >::mi_Length;
	if ( DAL< Key, Data, MyKeyComparator >::compare(idx, Length) ==0 ) return false;
	if ( idx == 0)
	{
		_y = -1;
		cout << "\n>>> Predecessor de "<< _x <<" não existe!" <<endl;
	
	}else{ 
	
		_y = DAL< Key, Data, MyKeyComparator >::mpt_Data[idx-1].id;
		std::cout << "\n>>> Predecessor de "<< _x <<" : " << _y <<endl;
	}	
	return true;
}




