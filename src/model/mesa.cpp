/**	@ingroup	MOD_MESA
 * 	@file		mesa.cpp
 * 	@brief		Implementacoes dos metodos das classes da mesa do jogo de Domino
 */

#define MESA_SERVER
#include "../../include/model/mesa.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					 METODOS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Mesa* Mesa::instance () throw ()
{
	if ( !Mesa::_instance )
		Mesa::_instance = new Mesa ();
	
	return ( Mesa::_instance );
}

void Mesa::delete_instance () throw ()
{
	if ( Mesa::_instance )
	{
		delete ( Mesa::_instance );
		Mesa::_instance = NULL;
	}
}

void Mesa::inserePrimeiraPeca (int indice_peca) throw ()
{
	this->lado_comeco = pecas[ indice_peca ].getLadoA ();
	this->lado_fim = pecas[ indice_peca ].getLadoB ();
	
	this->indice_pecas.push_back ( indice_peca );
}

void Mesa::insereComeco (const sJogada& jogada) throw ()
{
	if ( jogada.lado_peca == 'B' )
		this->lado_comeco = pecas[ jogada.indice_peca ].getLadoA ();
	else
		this->lado_comeco = pecas[ jogada.indice_peca ].getLadoB ();
	
	this->indice_pecas.push_front ( jogada.indice_peca );
}

void Mesa::insereFim (const sJogada& jogada) throw ()
{
	if ( jogada.lado_peca == 'B' )
		this->lado_fim = pecas[ jogada.indice_peca ].getLadoA ();
	else
		this->lado_fim = pecas[ jogada.indice_peca ].getLadoB ();
	
	this->indice_pecas.push_back ( jogada.indice_peca );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
