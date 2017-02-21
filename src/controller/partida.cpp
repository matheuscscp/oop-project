/**	@ingroup	MOD_PARTIDA
 * 	@file		partida.cpp
 * 	@brief		Implementacoes dos metodos das classes de uma partida do jogo de Domino
 */

#define PARTIDA_SERVER
#include "../../include/controller/partida.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *				METODOS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int Partida::run ()
{
	int crash = 0;
	
	try
	{
		engine->init ();
		
		engine->mostrarLogo ( WELCOME, 0 );
		jogadores; // inicializa as inteligencias artificiais dos jogadores desta execucao
		engine->mostrarLogo ( WELCOME, 1 );
		
		Partida::_instance = new Partida ();
		while ( !engine->quit () )
			Partida::_instance->executarPartida ();
		
		engine->mostrarLogo ( GOODBYE, 4 );
		
		engine->close ();
	}
	catch (ExcecaoEngineCrash e)
	{
		crash = 1;
		std::cerr << e.erro << std::endl;
	}
	
	Peca::delete_instance ();
	Mesa::delete_instance ();
	Jogador::delete_instance ();
	Engine::delete_instance ();
	View::delete_instance ();
	delete ( Partida::_instance );
	
	return ( crash );
}

void Partida::executarPartida ()
{
	this->resetar ();
	engine->setLogMsg ("A partida comecou!");
	
	engine->atualizarTela ();
	
	while ( ( this->naoEncerrou () ) && ( !engine->quit () ) )
		this->executarRodada ();
	
	if ( !engine->quit () )
	{
		this->setLogMsgPartidaEncerrou ();
		
		while ( ( engine->imprimindoLogMsgs () ) && ( !engine->quit () ) )
			engine->atualizarTela ();
	}
}

void Partida::resetar ()
{
	this->nova_partida = true;
	
	for (int i = 0; i < 4; i++)
		jogadores[i].resetarPontuacao ();
	
	this->resetarRodada ();
	
	this->encontrarPrimeiroJogador ();
}

void Partida::resetarRodada ()
{
	this->nova_rodada = true;
	
	this->rodada_batida = false;
	
	engine->resetarSlots ();
	
	this->distribuirPecas ();
	
	mesa->resetar ();
}

void Partida::distribuirPecas ()
{
	for ( int i = 0; i < 4; i++ )
		jogadores[i].devolverPecas ();
	
	int* indices_pecas = this->getIndicesSorteados ();
	
	for ( int i = 0; i < 28; i++ )
		jogadores[ i % 4 ].pegarPeca ( indices_pecas[i] );
	
	delete[] (indices_pecas);
}

int* Partida::getIndicesSorteados ()
{
	int* indices_pecas = new int[28];
	int indice_aux, j;
	
	srand (time (NULL));
	
	for (int i = 0; i <= 27; i++)
	{
		do {
			//	Adicionar valor aleatorio entre 0 e 27
			indice_aux = rand () % 28;
			
			//	Verificando se existe numero repetido
			j = 0;
			while ( (j < i) && ( indices_pecas[j] != indice_aux ) )
				j++;
			
		} while (j < i);
		
		indices_pecas[i] = indice_aux;
	}
	
	return (indices_pecas);
}

void Partida::encontrarPrimeiroJogador ()
{
	this->jogador_turno = 0;
	while ( jogadores[ this->jogador_turno ].naoTemPelado () )
		this->jogador_turno++;
	
	jogadores[ this->jogador_turno ].mudarFlagJogando ();
}

void Partida::executarRodada ()
{
	while ( ( !this->rodada_batida ) && ( !engine->quit () ) )
	{
		engine->atualizarTela ();
		
		if ( ( !engine->imprimindoLogMsgs () ) && ( !engine->quit () ) )
			this->executarTurno ();
	}
	
	while ( ( engine->imprimindoLogMsgs () ) && ( !engine->quit () ) )
		engine->atualizarTela ();
	
	if ( ( this->naoEncerrou () ) && ( !engine->quit () ) )
	{
		engine->setLogMsg ( "A rodada encerrou! Comecando nova rodada..." );
		
		this->resetarRodada ();
	}
}

void Partida::avancarJogador ()
{
	jogadores[ this->jogador_turno ].mudarFlagJogando ();
	
	if (this->jogador_turno < 3)
		this->jogador_turno++;
	else
		this->jogador_turno = 0;
	
	jogadores[ this->jogador_turno ].mudarFlagJogando ();
}

void Partida::executarTurno ()
{
	if ( this->nova_rodada )
		this->executarPrimeiroTurno ();
	else if ( jogadores[ this->jogador_turno ].podeJogar () )
		this->executarTurnoGeral ();
	else
	{
		engine->setLogMsg ( jogadores[ this->jogador_turno ].getNick () + " passou!" );
		this->avancarJogador ();
	}
}

void Partida::executarPrimeiroTurno ()
{
	int indice_peca;
	
	this->nova_rodada = false;
	
	if ( !this->nova_partida )
		indice_peca = jogadores[ this->jogador_turno ].jogarPrimeiraPeca ();
	else
	{
		this->nova_partida = false;
		jogadores[ this->jogador_turno ].jogarPelado ();
		indice_peca = 0;
	}
	
	view->posicionarPrimeiraPeca ( indice_peca );
	engine->setLogMsg ( jogadores[ this->jogador_turno ].getNick () + " comecou com " + pecas[ indice_peca ].getNome () + "!" );
	this->avancarJogador ();
}

void Partida::executarTurnoGeral ()
{
	sJogada jogada = jogadores[ this->jogador_turno ].fazerJogada ();
	view->posicionarPeca ( jogada );
	
	if ( !this->encontrarBate () )
	{
		engine->setLogMsg ( jogadores[ this->jogador_turno ].getNick () + " encaixou " + pecas[ jogada.indice_peca ].getNome () + "." );
		this->avancarJogador ();
	}
	else
		this->encerrarRodada ();
}

void Partida::encerrarRodada ()
{
	engine->setLogMsg ( jogadores[ this->jogador_turno ].getNick () + " bateu!" );
	
	for ( int i = 0; i < 4; i++ )
		jogadores[i].acumularPontos ();
	
	this->rodada_batida = true;
}

bool Partida::encontrarBate ()
{
	if ( jogadores[ this->jogador_turno ].getTotalPecas () > 0 )
	{
		for ( int i = 0; i < 4; i++ )
		{
			if ( jogadores[i].podeJogar () )
				return ( false );
		}
	}
	
	return ( true );
}

bool Partida::naoEncerrou ()
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( jogadores[i].getPontuacao () >= 40 )
			return (false);
	}
	
	return (true);
}

void Partida::setLogMsgPartidaEncerrou ()
{
	std::string log_msg = "A partida encerrou! ";
	int max = jogadores[0].getPontuacao ();
	int max_i = 0;
	int min = jogadores[0].getPontuacao ();
	int min_i = 0;
	int aux;
	
	for ( int i = 1; i < 4; i++ )
	{
		aux = jogadores[i].getPontuacao ();
		
		if (aux > max)
		{
			max = aux;
			max_i = i;
		}
		else if (aux < min)
		{
			min = aux;
			min_i = i;
		}
	}
	
	log_msg = log_msg + ( jogadores[max_i].getNick () ).c_str () + " paga para " + ( jogadores[min_i].getNick () ).c_str () + "!";
	
	engine->setLogMsg (log_msg);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
