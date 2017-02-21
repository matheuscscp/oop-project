/**	@defgroup MOD_MESA "Mesa"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes da mesa do jogo de Domino
 * 	@}
 * 	@ingroup MOD_MESA
 * 	@file	mesa.hpp
 * 	@brief	Declaracao dos defines, classes e metodos da mesa do jogo de Domino
 */

#ifndef MESA_HPP
#define MESA_HPP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <list>

#include "./peca.hpp"

/**	Define um macro para simplificar a chamada ao singleton da mesa
 * 	@brief	Instancia da mesa
 */
#define mesa	Mesa::instance ()

/** @brief Estrutura para procurar e executar jogadas */
struct sJogada
{
	///	@brief Guarda o indice da peca movida
	int	indice_peca;
	
	///	@brief Char que indica qual lado encaixa da nova peca
	char	lado_peca;
	
	///	@brief Guarda o indice da peca na ponta da mesa
	int	indice_mesa;
	
	///	@brief Char que indica a ponta ('C' para comeco, 'F' para fim) em que jogada esta sendo feita
	char	ponta;
};

/**     @brief  Representa a mesa do jogo. */
class Mesa
{
	private:
		
		/**		@brief Instancia singleton da mesa */
		static Mesa*	_instance;
		
		/**		@brief Vetor de indices para alocar as pecas na mesa */
		std::list<int>	indice_pecas;
		
		/**		@brief Valor inteiro do lado aberto da peca no comeco da mesa */
		int		lado_comeco;
		
		/**		@brief Valor inteiro do lado aberto da peca no fim da mesa */
		int		lado_fim;
		
		/**	@brief	Construtor padrao da mesa */
		Mesa () throw () {}
		
		/**	@brief	Destroi a mesa esvaziando os indices */
		~Mesa () throw () {}
		
	public:
		
		/** 	@return Instancia do singleton da mesa
		 *	@brief Instancia ou apenas retorna o ponteiro da instancia do singleton da mesa */
		static Mesa* instance () throw ();
		
		/** 	@brief Destroi a instancia do singleton da mesa */
		static void delete_instance () throw ();
		
		/**	@brief	Esvazia os indices */
		void resetar () throw () { this->indice_pecas.clear (); }
		
		/** 	@param indice_peca Indice da peca que esta sendo inserida
		*	@brief Insere uma peca no centro da mesa */
		void inserePrimeiraPeca (int indice_peca) throw ();
		
		/** 	@param jogada Estrutura contendo as informacoes necessarias para inserir a peca no comeco da mesa
		 *	@brief Insere uma peca no comeco da mesa */
		void insereComeco (const sJogada& jogada) throw ();
		
		/**	@return Valor inteiro do lado aberto da peca que esta no comeco da mesa
		 * 	@brief Metodo de acesso */
		int getLadoComeco () throw () { return this->lado_comeco; }
		
		/**	@return Indice da peca na ponta de cima da mesa
		 * 	@brief Retorna o indice da peca na ponta de cima da mesa */
		int getIndiceComeco () throw () { return this->indice_pecas.front (); }
		
		/** 	@param jogada Estrutura contendo as informacoes necessarias para inserir a peca no fim da mesa
		 *	@brief Insere uma peca no fim da mesa */
		void insereFim (const sJogada& jogada) throw ();
		
		/**	@return Valor inteiro do lado aberto da peca que esta no fim da mesa
		 * 	@brief Metodo de acesso */
		int getLadoFim () throw () { return this->lado_fim; }
		
		/**	@return Indice da peca na ponta de baixo da mesa
		 * 	@brief Retorna o indice da peca na ponta de baixo da mesa */
		int getIndiceFim () throw () { return this->indice_pecas.back (); }
		
		/**	@return Referencia para a lista de indices de pecas da mesa
		 * 	@brief Retorna uma referencia para a lista de indices de pecas da mesa */
		std::list<int>& getIndicePecas () throw () { return this->indice_pecas; }
};

// instancia os membros static do singleton da mesa
#ifdef MESA_SERVER
	Mesa* Mesa::_instance = NULL;
#endif

#endif
