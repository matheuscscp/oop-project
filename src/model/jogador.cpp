/**	@ingroup	MOD_JOGADOR
 * 	@file		jogador.cpp
 * 	@brief		Implementacoes dos metodos das classes dos jogadores do jogo de Domino
 */

#define JOGADOR_SERVER
#include "../../include/model/jogador.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					METODOS					
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int Burrice::jogarPrimeiraPeca (Jogador* jogador)
{
	int tmp = jogador->getIndicePecas ().front ();
	
	jogador->getIndicePecas ().pop_front ();
	
	mesa->inserePrimeiraPeca ( tmp );
	
	return ( tmp );
}

sJogada Burrice::fazerJogada (Jogador* jogador)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin ();
	sJogada				jogada;
	bool				keep = true;
	
	while ( keep )
	{
		keep = false;
		jogada.indice_peca = *it;
		
		if ( pecas[ *it ].getLadoA () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else if ( pecas[ *it ].getLadoA () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else if ( pecas[ *it ].getLadoB () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else if ( pecas[ *it ].getLadoB () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else
		{
			keep = true;
			it++;
		}
	}
	
	return ( jogada );
}

int InteligenciaNivel1::jogarPrimeiraPeca (Jogador* jogador)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin ();
	int				tmp = -1;
	bool				keep = true;
	
	while ( keep )
	{
		if ( it == jogador->getIndicePecas ().end () )
			keep = false;
		else if ( !pecas[ *it ].bucha () )
			it++;
		else
		{
			keep = false;
			tmp = *it;
		}
	}
	
	if ( tmp < 0 )
	{
		it = jogador->getIndicePecas ().begin ();
		tmp = *it;
	}
	
	jogador->getIndicePecas ().erase ( it );
	mesa->inserePrimeiraPeca ( tmp );
	
	return ( tmp );
}

sJogada InteligenciaNivel1::fazerJogada (Jogador* jogador)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin ();
	sJogada				jogada;
	bool				keep = true;
	
	while ( keep )
	{
		keep = false;
		jogada.indice_peca = *it;
		
		if ( pecas[ *it ].getLadoB () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else if ( pecas[ *it ].getLadoB () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else if ( pecas[ *it ].getLadoA () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else if ( pecas[ *it ].getLadoA () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else
		{
			keep = true;
			it++;
		}
	}
	
	return ( jogada );
}

int InteligenciaNivel2::jogarPrimeiraPeca (Jogador* jogador)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin (), aux;
	int				tmp = -1;
	bool				keep = true;
	bool				pegou_seca = false;
	
	while ( keep )
	{
		if ( it == jogador->getIndicePecas ().end () )
			keep = false;
		else if ( !pecas[ *it ].bucha () )
			it++;
		else if ( !this->buchaSeca ( jogador, *it ) )
		{
			keep = false;
			tmp = *it;
			if ( pegou_seca )
				pegou_seca = false;
		}
		else
		{
			if ( tmp < 0 )
			{
				pegou_seca = true;
				tmp = *it;
				aux = it;
			}
			it++;
		}
	}
	
	if ( tmp >= 0 )
	{
		if ( pegou_seca )
			it = aux;
	}
	else
	{
		it = jogador->getIndicePecas ().begin ();
		tmp = *it;
	}
	
	jogador->getIndicePecas ().erase ( it );
	mesa->inserePrimeiraPeca ( tmp );
	
	return ( tmp );
}

bool InteligenciaNivel2::buchaSeca (Jogador* jogador, int indice_peca)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin ();
	bool				keep = true;
	
	while ( keep )
	{
		if ( it == jogador->getIndicePecas ().end () )
			keep = false;
		else if (	( *it != indice_peca ) &&
				(	( pecas[ *it ].getLadoA () == pecas[ indice_peca ].getLadoA () ) ||
					( pecas[ *it ].getLadoB () == pecas[ indice_peca ].getLadoA () )	)	)
			return ( false );
		else
			it++;
	}
	
	return ( true );
}

sJogada InteligenciaNivel2::fazerJogada (Jogador* jogador)
{
	std::list<int>::iterator	it = jogador->getIndicePecas ().begin ();
	sJogada				jogada;
	bool				keep = true;
	
	while ( keep )
	{
		keep = false;
		jogada.indice_peca = *it;
		
		if ( pecas[ *it ].getLadoB () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else if ( pecas[ *it ].getLadoB () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'B';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else if ( pecas[ *it ].getLadoA () == mesa->getLadoComeco () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceComeco ();
			jogada.ponta = 'C';
			mesa->insereComeco ( jogada );
		}
		else if ( pecas[ *it ].getLadoA () == mesa->getLadoFim () )
		{
			jogador->getIndicePecas ().erase ( it );
			jogada.lado_peca = 'A';
			jogada.indice_mesa = mesa->getIndiceFim ();
			jogada.ponta = 'F';
			mesa->insereFim ( jogada );
		}
		else
		{
			keep = true;
			it++;
		}
	}
	
	return ( jogada );
}

Jogador* Jogador::instance () throw ()
{
	if ( !Jogador::_instance )
	{
		std::string buf ( "Jogador X" );
		
		Jogador::_instance = new Jogador[4];
		
		for ( int i = 0; i < 4; i++ )
		{
			buf[8] = '1' + i;
			Jogador::_instance[i].init ( buf );
		}
	}
	
	return ( Jogador::_instance );
}

void Jogador::delete_instance () throw ()
{
	if ( Jogador::_instance )
	{
		delete[] ( Jogador::_instance );
		Jogador::_instance = NULL;
	}
}

void Jogador::init (std::string nome) throw ()
{
	this->nome = nome;
	
	this->chance_alerta = new_rand ( 101 );
	
	switch ( new_rand ( 6 ) )
	{
		case 0:
		case 1:
		case 2:
			this->inteligencia = new Burrice ();
			break;
		case 3:
		case 4:
			this->inteligencia = new InteligenciaNivel1 ();
			break;
		case 5:
			this->inteligencia = new InteligenciaNivel2 ();
			break;
	}
}

void Jogador::melhorarInteligencia () throw ()
{
	switch ( this->inteligencia->getNivel () )
	{
		case 0:
			
			delete ( this->inteligencia );
			this->inteligencia = new InteligenciaNivel1 ();
			break;
			
		case 1:
			
			delete ( this->inteligencia );
			this->inteligencia = new InteligenciaNivel2 ();
			break;
			
		case INTELIGENCIA_MAX:
			
			break;
	}
}

void Jogador::pegarPeca (int indice_peca) throw ()
{
	std::list<int>::iterator	it = this->indice_pecas.begin ();
	bool				found = false;
	
	for ( int i = 0; ( i < (int) this->indice_pecas.size () ) && ( !found ); i++ )
	{
		if ( pecas[ *it ].getLadoA () + pecas[ *it ].getLadoB () > pecas[ indice_peca ].getLadoA () + pecas[ indice_peca ].getLadoB () )
			it++;
		else if ( pecas[ *it ].getLadoA () + pecas[ *it ].getLadoB () < pecas[ indice_peca ].getLadoA () + pecas[ indice_peca ].getLadoB () )
			found = true;
		else
		{
			for ( i = i; ( i < (int) this->indice_pecas.size () ) && ( !found ); i++ )
			{
				if ( pecas[ *it ].getLadoB () > pecas[ indice_peca ].getLadoB () )
					it++;
				else
					found = true;
			}
		}
	}
	
	this->indice_pecas.insert ( it, indice_peca );
}

void Jogador::jogarPelado () throw ()
{
	this->indice_pecas.pop_back ();
	
	mesa->inserePrimeiraPeca ( 0 );
}

void Jogador::resetarPontuacao () throw ()
{
        this->pontuacao = 0;
	this->_jogando = false;
}

bool Jogador::podeJogar () throw ()
{
	std::list<int>::iterator it = this->indice_pecas.begin ();
	
	for ( int i = 0; i < (int) this->indice_pecas.size (); i++ )
	{
		if (	( pecas[ *it ].getLadoA () == mesa->getLadoComeco () ) ||
			( pecas[ *it ].getLadoB () == mesa->getLadoComeco () ) ||
			( pecas[ *it ].getLadoA () == mesa->getLadoFim () ) ||
			( pecas[ *it ].getLadoB () == mesa->getLadoFim () )	)
			return ( true );
		
		it++;
	}
	
	return ( false );
}

void Jogador::acumularPontos () throw ()
{
	for ( std::list<int>::iterator it = this->indice_pecas.begin (); it != this->indice_pecas.end (); it++ )
		this->pontuacao += ( pecas[ *it ].getLadoA () + pecas[ *it ].getLadoB () );
	
	// melhora a inteligencia caso o jogador entre em alerta e seja possivel
	if ( ( this->pontuacao >= NIVEL_ALERTA ) && ( this->chance_alerta > 0 ) && ( this->inteligencia->getNivel () < INTELIGENCIA_MAX ) )
	{
		if ( ( rand () % 100 ) + 1 <= this->chance_alerta )
		{
			this->melhorarInteligencia ();
			this->chance_alerta = 0;
		}
	}
}

int new_rand (int mod)
{
	int return_value, tmp;
	
	srand ( time ( NULL ) );
	return_value = rand () % mod;
	
	tmp = time ( NULL ) + 1;
	while ( time ( NULL ) < tmp );
	
	return ( return_value );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
