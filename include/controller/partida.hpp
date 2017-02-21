/**	@defgroup MOD_PARTIDA "Partida"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes de uma partida do jogo de Domino
 * 	@}
 * 	@ingroup MOD_PARTIDA
 * 	@file	partida.hpp
 * 	@brief	Declaracao dos defines, classes e metodos de uma partida do jogo de Domino
 */

#ifndef PARTIDA_HPP
#define PARTIDA_HPP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../view/view.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					CLASSES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**     @brief Todos os mecanismos do jogo em si estao aqui */
class Partida
{
	public:
		
		/// @return	Valor nao-nulo caso ocorra um erro que impeca a execucao do jogo, ou zero em caso contrario
		/// @brief	Faz o programa entrar no loop principal
		static int	run ();
		
	private:
		
		/// @brief	Aporta para a instancia unica do singleton de partida
		static Partida*	_instance;
		
		/// @brief	Valor inteiro entre 0 e 3 que diz qual jogador joga naquele turno
		int		jogador_turno;
		
		/// @brief	Flag que indica nova partida
		bool		nova_partida;
		
		/// @brief	Flag que indica nova rodada
		bool		nova_rodada;
		
		/// @brief	Flag que indica que a rodada foi batida
		bool		rodada_batida;
		
		/// @brief	Construtor
				Partida () {}
		
		/// @brief	Destrutor
				~Partida () {}
		
		/// @brief	Reseta a partida
		void		resetar ();
		
		/// @brief	Executa uma partida inteira do jogo de Domino
		void		executarPartida ();
		
		/// @brief	Executa uma rodada inteira do jogo de Domino
		void		executarRodada ();
		
		/// @brief	Muda o indice de jogador para o que ira jogar no proximo turno
		void		avancarJogador ();
		
		/// @brief	Embaralha os indices das pecas em um vetor e divide entre os quatro jogadores
		void		distribuirPecas ();
		
		/// @return	Vetor de indices sorteados alocados dinamicamente
		/// @warning	Este metodo retorna um vetor de int alocado dinamicamente. Lembre-se de usar "delete[] ...;"
		/// @brief	Aloca um vetor de int para colocar valores entre 0 e 27, inclusive, aleatoriamente e retornar este armazem
		int*		getIndicesSorteados ();
		
		/// @brief	Chama todos os metodos necessarios para que uma rodada possa ser iniciada
		void		resetarRodada ();
		
		/// @brief	Determina o primeiro jogador da partida
		void		encontrarPrimeiroJogador ();
		
		/// @return	true se a partida nao encerrou, ou false em caso contrario
		/// @brief	Verifica se a partida encerrou checando os pontos dos jogadores
		bool		naoEncerrou ();
		
		/// @brief	Execucao de um turno do jogo de Domino
		void		executarTurno ();
		
		/// @brief	Instrucoes especificas para o primeiro turno de uma rodada qualquer
		void		executarPrimeiroTurno ();
		
		/// @brief	Instrucoes para qualquer turno apos o primeiro
		void		executarTurnoGeral ();
		
		/// @return	true se alguem bateu a rodada, ou false em caso contrario
		/// @brief	Metodo para verificar se alguem bateu a rodada
		bool		encontrarBate ();
		
		/// @brief	Executa as acoes necessarias para encerrar uma rodada qualquer
		void		encerrarRodada ();
		
		/// @brief	Determina a mensagem de log para o final de uma partida
		void		setLogMsgPartidaEncerrou ();
};

// instanciando os membros estaticos do singleton da partida
#ifdef PARTIDA_SERVER
	Partida* Partida::_instance = NULL;
#endif

#endif
