/**	@defgroup MOD_PECA "Peca"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes relacionadas a uma peca do jogo de Domino
 * 	@}
 * 	@ingroup MOD_PECA
 * 	@file	peca.hpp
 * 	@brief	Declaracao dos defines, classes e metodos relacionadas a uma peca do jogo de Domino
 */

#ifndef PECA_HPP
#define PECA_HPP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>

/**	Define um macro para simplificar a chamada ao singleton das pecas
 * 	@brief	Instancia das pecas
 */
#define pecas	Peca::instance ()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					CLASSES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**     @brief Representa as pecas do jogo */
class Peca
{
	private:
		
		///		@brief Vetor de pecas singleton
		static Peca*	_instance;
		
		/**		@brief Valor inteiro do primeiro lado da peca */
		int		ladoA;
		
		/**		@brief Valor inteiro do segundo lado da peca */
		int		ladoB;
		
		/**		@brief Flag para indicar se o lado A e igual ao lado B */
		bool		_bucha;
		
		/**		@brief Nome literal da peca */
		std::string	nome;
		
		/**		@brief Construtor padrao da peca */
				Peca () throw () {}
		
		/**		@brief Destrutor padrao da peca */
				~Peca () throw () {}
		
		/**		@param ladoA Valor inteiro do primeiro lado da pedra
		 * 		@param ladoB Valor inteiro do segundo lado da pedra
		 * 		@brief Caracteriza a instancia de peca corrente conforme os parametros passados */
		void		set (int ladoA, int ladoB) throw ();
		
		/**		@brief Metodo para determinar o nome da peca do jogo de Domino quando ela e instanciada */
		void		setNome () throw ();
		
        public:
		
		/**		@return Copia de uma peca indicada pelo parametro passado
		 * 		@brief Instancia o singleton das pecas ou apenas retorna uma copia da peca indicada pelo parametro passado */
		static Peca*	instance () throw ();
		
		/**		@brief Libera as pecas do singleton */
		static void	delete_instance () throw ();
		
		/**		@return Valor inteiro do lado A da peca
		 * 		@brief Metodo de acesso */
		int		getLadoA ()	{ return this->ladoA; }
		
		/**		@return Valor inteiro do lado B da peca
		 * 		@brief Metodo de acesso */
		int		getLadoB ()	{ return this->ladoB; }
		
		/**		@return true se o lado A e igual ao lado B, ou false em caso contrario
		 * 		@brief Metodo de acesso */
		bool		bucha ()	{ return this->_bucha; }
		
		/**		@return Retorna o nome da peca
		 * 		@brief Metodo de acesso */
		std::string	getNome () 	{ return this->nome; }
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// instancia os membros static do singleton das pecas
#ifdef PECA_SERVER
	Peca* Peca::_instance = NULL;
#endif

#endif
