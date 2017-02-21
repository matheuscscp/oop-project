/**	@defgroup MOD_JOGADOR "Jogador"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes dos jogadores do jogo de Domino
 * 	@}
 * 	@ingroup MOD_JOGADOR
 * 	@file	jogador.hpp
 * 	@brief	Declaracao dos defines, classes e metodos dos jogadores do jogo de Domino
 */

#ifndef JOGADOR_HPP
#define JOGADOR_HPP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cstdlib>

#include "./mesa.hpp"

/**	Define um macro para o numero de pontos necessarios para ativar o alerta de um jogador
 * 	@brief	Nivel de alerta de um jogador
 */
#define NIVEL_ALERTA		20

/**	Define um macro para dizer o nivel maximo de inteligencia implementado
 * 	@brief Inteligencia maxima
 */
#define INTELIGENCIA_MAX	2

/**	Define um macro para simplificar a chamada ao singleton de jogadores
 * 	@brief	Instancia dos jogadores
 */
#define jogadores		Jogador::instance ()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					CLASSES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class Jogador;

/**	Termos tecnicos do jogo Domino RAXASSAUM:
 * 		- RANDOM: Calouro. Faz escolhas aleatorias.
 * 		- POPS: Calouro depois de 5 minutos jogando. Joga as pecas com maior peso sem ver nada.
 * 		- Rachar: Jogar nas pontas com maior peso para impedir o proximo jogador de rolar suas buchas pesadas.
 * 		- Bucha: Peca com o mesmo numero dos dois lados.
 * 		- Rolar: Jogar uma bucha.
 * 	@brief Classe abstrata para representar a inteligencia de um jogador do jogo de Domino */
class Inteligencia
{
	protected:
		
		///		@brief Nivel de inteligencia do jogador
		unsigned int	nivel;
		
	public:
		
		///		@param jogador Ponteiro para o jogador que esta executando a jogada
		///		@return Indice da peca que foi jogada
		///		@brief Metodo abstrato que deve jogar a primeira peca da rodada
		virtual	int	jogarPrimeiraPeca (Jogador* jogador) = 0;
		
		///		@param jogador Ponteiro para o jogador que esta executando a jogada
		///		@return Jogada feita pela inteligencia artificial deste jogador
		///		@brief Metodo abstrato para fazer uma jogada para um turno qualquer
		virtual	sJogada	fazerJogada (Jogador* jogador) = 0;
		
		///		@return O nivel desta inteligencia
		unsigned int	getNivel () { return this->nivel; }
};

/**	@brief Implementacao do nivel de inteligencia artificial mais "burro" possivel para o jogo de Domino, vulgo RANDOM!! */
class Burrice : public Inteligencia
{
	public:
		
		///	@brief Construtor
			Burrice () { this->nivel = 0; }
		
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Indice da peca que foi jogada
		///	@brief Comeca com a primeira peca da mao do jogador
		int	jogarPrimeiraPeca (Jogador* jogador);
		
		///	Ordem das tentativas (uma peca depois da outra):
		///	pecaLadoA com comecoMesa
		///	pecaLadoA com fimMesa
		///	pecaLadoB com comecoMesa
		///	pecaLadoB com fimMesa
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Jogada feita pela inteligencia artificial deste jogador
		///	@brief Encaixa a primeira tentativa que der certo
		sJogada	fazerJogada (Jogador* jogador);
};

/**	@brief Implementacao do primeiro nivel de inteligencia artificial possivel para o jogo de Domino, vulgo POPS!! */
class InteligenciaNivel1 : public Inteligencia
{
	public:
		
		///	@brief Construtor
			InteligenciaNivel1 () { this->nivel = 1; }
		
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Indice da peca que foi jogada
		///	@brief Comeca com a primeira bucha da mao do jogador, ou com a primeira peca caso nao hajam buchas
		int	jogarPrimeiraPeca (Jogador* jogador);
		
		///	Ordem das tentativas (uma peca depois da outra):
		///	pecaLadoB com fimMesa
		///	pecaLadoB com comecoMesa
		///	pecaLadoA com fimMesa
		///	pecaLadoA com comecoMesa
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Jogada feita pela inteligencia artificial deste jogador
		///	@brief Encaixa a primeira tentativa POPS que der certo
		sJogada	fazerJogada (Jogador* jogador);
};

/**	@brief Implementacao do segundo nivel de inteligencia artificial possivel para o jogo de Domino, ainda e POPS, mas tenta rachar. */
class InteligenciaNivel2 : public Inteligencia
{
	private:
		
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@param indice_peca Indice da bucha que esta sendo verificada
		///	@return true se a bucha estiver seca, ou false em caso contrario
		///	@brief Verifica se uma dada bucha esta seca ou nao na mao do jogador passado como parametro
		bool	buchaSeca (Jogador* jogador, int indice_peca);
		
	public:
		
		///	@brief Construtor
			InteligenciaNivel2 () { this->nivel = INTELIGENCIA_MAX; }
		
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Indice da peca que foi jogada
		///	@brief Comeca com a primeira bucha nao seca, ou com a primeira bucha (caso todas sejam secas), ou com a primeira peca caso nao hajam buchas
		int	jogarPrimeiraPeca (Jogador* jogador);
		
		///	Ordem das tentativas (uma peca depois da outra):
		///	pecaLadoB com comecoMesa
		///	pecaLadoB com fimMesa
		///	pecaLadoA com comecoMesa
		///	pecaLadoA com fimMesa
		///	@param jogador Ponteiro para o jogador que esta executando a jogada
		///	@return Jogada feita pela inteligencia artificial deste jogador
		///	@brief Encaixa a primeira tentativa POPS mais inteligente que der certo
		sJogada	fazerJogada (Jogador* jogador);
};

/**     @brief Representa um jogador do jogo de Domino */
class Jogador
{
        private:
		
		/** 		@brief Ponteiro para o singleton de jogadores */
		static Jogador*	_instance;
		
		/**		@brief Lista de indices de pecas do jogador */
		std::list<int>	indice_pecas;
		
		/**		@brief Total de pontos de um jogador em uma partida */
		int		pontuacao;
		
		/**		@brief String do nome do jogador */
		std::string	nome;
		
		/**		@brief Flag para dizer ao componente "view" que esta na vez deste jogador escolher sua jogada */
		bool		_jogando;
		
		/** 		@brief Ponteiro para a instancia da inteligencia deste jogador */
		Inteligencia*	inteligencia;
		
		/**		@brief Chance do jogar ficar alerta ao atingir um numero de pontos maior ou igual a NIVEL_ALERTA */
		int		chance_alerta;
		
		/** 		@param nome String com o nome do jogador que esta sendo construido
		 *		@brief Atribui o parametro passado ao nome do jogador e gera sua inteligencia artificial */
		void		init (std::string nome) throw ();
		
		/**		@brief Melhora o nivel de inteligencia conforme a chance de alerta */
		void		melhorarInteligencia () throw ();
		
	public:
		
		/**		@brief Construtor singleton nao privado para possibilitar testes unitarios */
				Jogador () throw () {}
		
		/**		@brief Destrutor singleton nao privado para possibilitar testes unitarios */
				~Jogador () throw () {}
		
		/** 		@return Instancia do singleton dos jogadores
		 *		@brief Instancia ou apenas retorna o ponteiro da instancia do singleton de jogadores */
		static Jogador*	instance () throw ();
		
		/** 		@brief Libera a instancia do singleton de jogadores */
		static void	delete_instance () throw ();
		
		/**		@brief Reseta os pontos de um jogador */
		void		resetarPontuacao () throw ();
		
		/**		@brief Esvazia a lista de indices de pecas */
		void		devolverPecas () throw () { this->indice_pecas.clear (); }
		
		/** 		@param indice_peca Indice da peca que o jogador esta obtendo
		 *		@brief Adiciona um indice de peca a lista de indices */
		void		pegarPeca (int indice_peca) throw ();
		
		/**		@brief Elimina o pelado da lista de pecas */
		void		jogarPelado () throw ();
		
		/**		@return Indice da primeira peca deste jogador
		 * 		@brief Elimina o primeiro indice de peca deste jogador e retorna o indice */
		int		jogarPrimeiraPeca () throw () { return this->inteligencia->jogarPrimeiraPeca ( this ); }
		
		/**		@brief Atualiza a flag que diz se o jogandor esta jogando */
		void		mudarFlagJogando () throw () { this->_jogando = ( !this->_jogando ); }
		
		/**		@return true se o jogando estiver jogando naquele momento, ou false em caso contrario
		 * 		@brief Checa se o jogador esta jogando naquele momento */
		bool		jogando () throw () { return this->_jogando; }
		
		/** 		@return Valor logico indicando se o jogador tem ou nao o pelado
		 * 		@brief Retorna um valor logico para indicar se o jogando possui o pelado ou nao */
		bool		naoTemPelado () throw () { return ( this->indice_pecas.back () ); }
		
		/**		@return true se o jogador pode jogar, ou false em caso contrario
		 * 		@brief Verifica se um jogador pode jogar em um dado turno */
		bool		podeJogar () throw ();
		
		/**		@return Retorna uma jogada ja feita
		 * 		@brief Procura e faz uma jogada, eliminando o indice da peca da lista */
		sJogada		fazerJogada () throw () { return this->inteligencia->fazerJogada ( this ); }
		
		/**		@return Total de pecas do jogador
		 *		@brief Metodo de acesso */
		int		getTotalPecas () throw () { return this->indice_pecas.size (); }
		
		/**		@return Pontuacao do jogador na partida
		 *		@brief Metodo de acesso */
		int		getPontuacao () throw () { return this->pontuacao; }
		
		/**		@return A string do nick do jogador
		 *		@brief Metodo de acesso */
		std::string&	getNick () throw () { return this->nome; }
		
		/**		@brief Soma conta os pontos que sobraram na mao do jogador e acumula ao seu placar */
		void		acumularPontos () throw ();
		
		/**		@return Referencia para a lista de indices de pecas do jogador
		 * 		@brief Retorna uma referencia para a lista de indices de pecas deste jogador */
		std::list<int>&	getIndicePecas () throw () { return ( this->indice_pecas ); }
};

/// @param mod Tamanho do intervalo em que o numero aleatorio sera gerado
/// @return Um numero aleatorio no intervalo de 0 a mod - 1
/// @brief Utiliza a funcao rand () para gerar valores aleatorios e travar o programa durante um segundo
int new_rand (int mod);

// instanciando os membros estaticos do singleton de jogadores
#ifdef JOGADOR_SERVER
	Jogador* Jogador::_instance = NULL;
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM					
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif
