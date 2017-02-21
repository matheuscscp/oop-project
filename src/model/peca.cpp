/**	@ingroup	MOD_PECA
 * 	@file		peca.cpp
 * 	@brief		Implementacoes dos metodos das classes relacionadas a uma peca do jogo de Domino
 */

#define PECA_SERVER
#include "../../include/model/peca.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					 METODOS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Peca* Peca::instance () throw ()
{
	if ( !Peca::_instance )
	{
		Peca::_instance = new Peca[28];
		
		for ( int k = 0, i = 0; i <= 6; i++ )
		{
			for ( int j = i; j <= 6; j++ )
				Peca::_instance[ k++ ].set ( i, j );
		}
	}
	
	return ( Peca::_instance );
}

void Peca::delete_instance () throw ()
{
	if ( Peca::_instance )
	{
		delete[] ( Peca::_instance );
		Peca::_instance = NULL;
	}
}

void Peca::set (int ladoA, int ladoB) throw ()
{
	this->ladoA = ladoA;
	this->ladoB = ladoB;
	this->_bucha = ( ladoA == ladoB );
	this->setNome ();
}

void Peca::setNome () throw ()
{
	switch ( this->ladoA )
	{
		case 0:	this->nome = "PELADO";	break;
		case 1:	this->nome = "AS";	break;
		case 2:	this->nome = "DUQUE";	break;
		case 3:	this->nome = "TERNO";	break;
		case 4:	this->nome = "QUADRA";	break;
		case 5:	this->nome = "QUINA";	break;
		case 6:	this->nome = "SENA";	break;
	}
	
	if ( !this->_bucha )
	{
		switch (this->ladoB)
		{
			case 0:	this->nome += " e PELADO";	break;
			case 1:	this->nome += " e AS";		break;
			case 2:	this->nome += " e DUQUE";	break;
			case 3:	this->nome += " e TERNO";	break;
			case 4:	this->nome += " e QUADRA";	break;
			case 5:	this->nome += " e QUINA";	break;
			case 6:	this->nome += " e SENA";	break;
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
