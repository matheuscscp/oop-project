/**	@defgroup MOD_ENGINE "Engine"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes da engine grafica
 * 	@}
 * 	@ingroup MOD_ENGINE
 * 	@file	engine.hpp
 * 	@brief	Declaracao dos defines, classes e metodos da engine grafica
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *					INCLUDES					
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>

#include "../SDL/SDL_ttf.h"

#include "./imagem.hpp"

#include "../model/jogador.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *					DEFINES						
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**	@brief Define o FPS (Frames Per Second) do jogo */
#define FPS		20

/**	@brief O titulo da janela */
#define TITULO_JANELA	"Dominó RAXASSAUM"

/**	@warning O valor padrao deste macro e 200. Outros valores podem bugar a tela.
 * 	@brief Define o fator (em pixels) de escala da janela, que sempre sera 4x3 */
#define ESCALA_TELA	200

/**	@warning O valor padrao deste macro e 3000.
 * 	@brief Define o tempo de espera em milissegundos para se mostrar um aviso */
#define LOG_MSG_DELAY	3000

/**	@brief Define um macro para a mensagem de boas-vindas para o metodo mostrarLogo () */
#define WELCOME		0

/**	@brief Define um macro para a mensagem de ate-logo para o metodo mostrarLogo () */
#define GOODBYE		1

/**	Define um macro para simplificar a chamada ao singleton da engine
 * 	@brief	Instancia da engine
 */
#define engine		Engine::instance ()

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *					ENUMS						
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**     @brief  Indica se aquele slot esta ocupado ou nao. Se estiver, diz a posicao em que a peca foi jogada.*/
enum tEstadoSlot
{
	/// Posicao vertical (para cima)
	VERTICAL = 0,
	
	/// Posicao vertical invertida (para baixo)
	VERTICAL_INVERTIDA,
	
	/// Posicao horizontal (deitada)
	HORIZONTAL,
	
	/// Posicao horizontal invertida (deitada invertida)
	HORIZONTAL_INVERTIDA
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *					CLASSES						
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** @brief Estrutura de uma posicao da mesa para se encaixar uma peca */
class SlotPeca
{
	private:
		
		/** 		@brief Diz o estado do slot em relacao a sua peca */
		tEstadoSlot	estado;
		
		/**		@brief Posicao x da peca na tela */
		int		x;
		
		/**		@brief Posicao y da peca na tela */
		int		y;
		
	public:
		
		/** 		@param estado Estado da peca encaixada neste slot
		 * 		@param x Posicao x da peca na tela
		 * 		@param y Posicao y da peca na tela
		 *		@brief Construtor de um slot de peca */
				SlotPeca (tEstadoSlot estado, int x, int y) throw ()
				{
					this->estado = estado;
					this->x = x;
					this->y = y;
				}
		
		/**		@return Valor para indicar a posicao da imagem da peca na tela
		 * 		@brief Metodo de acesso */
		tEstadoSlot	getEstado () const throw () { return this->estado; }
		
		/**		@return Posicao x da peca deste slot na tela
		 * 		@brief Metodo de acesso */
		int		getX () const throw () { return this->x; }
		
		/**		@return Posicao y da peca deste slot na tela
		 * 		@brief Metodo de acesso */
		int		getY () const throw () { return this->y; }
};

/**	@brief		Estrutura para armazenar os ponteiros da instancia da SDL */
struct sEstruturaSDL
{
	/// @brief	Ponteiro para supercifie do icone da janela
	SDL_Surface*	p_icone;
	
	/// @brief	Ponteiro para a supercifie da tela
	SDL_Surface*	p_tela;
	
	/// @brief	Ponteiro para supercifie do fundo da janela
	SDL_Surface*	p_fundo;
};

/**	@brief Estrutura para armazenar a formatacao padrao de um texto */
struct sTextoConfig
{
	/// @brief	Ponteiro para fonte padrao
	TTF_Font*	p_fonte;
	
	/// @brief	Cor padrao da letra
	SDL_Color	cor_letra;
	
	/// @brief	Cor padrao da letra
	SDL_Color	cor_letra_jogando;
	
	/// @brief	Cor padrao do fundo da imagem
	SDL_Color	cor_fundo;
};

/**	@brief Estrutura para armazenar os atributos das mensagens de log (mensagens explicativas ao usuario) */
struct sLogMsg
{
	/// @brief	String da ultima mensagem de log
	std::string	mensagem;
	
	/// @brief	Ponteiro para a supercifie da imagem do texto
	SDL_Surface*	p_imagem;
	
	/// @brief	Retangulo para posicionar a imagem na tela
	SDL_Rect	posicao;
	
	/// @brief	Flag para controlar o tempo sem acoes apos uma mensagem de log entrar na fila
	unsigned int	atraso;
};

/**	@brief Estrutura para armazenar os atributos da tela de boas-vindas/ate-logo */
struct sLogo
{
	/// @brief	Ponteiro para a imagem da tela
	Imagem*		p_imagem_tela;
	
	/// @brief	Ponteiro para a imagem das mensagens
	Imagem*		p_imagem_mensagens;
};

/**	@brief Estrutura para armazenar as imagens do jogo de Domino */
struct sJogo
{
	/// @brief		Ponteiro para as imagens de todas as pecas de Domino
	Imagem*			p_imagem_pecas;
	
	/// @brief		Ponteiro para as imagens das pecas nas maos dos oponentes
	Imagem*			p_imagem_maos;
	
	/// @brief		Lista de slots que estao alocados para as pecas em determinado instante
	std::list<SlotPeca>	slot_pecas;
};

/**
 * @brief Definicoes da classe que lida com a interface do programa
 */
class Engine
{
	private:
		
		/// @brief	Ponteiros da SDL
		sEstruturaSDL	sdl;
		
		/// @brief	Ponteiro da fonte e cores
		sTextoConfig	texto_config;
		
		/// @brief	Ultima mensagem de log
		sLogMsg		log_msg[3];
		
		/// @brief	Tela de boas-vindas/ate-logo
		sLogo		logo;
		
		/// @brief	Imagens do jogo
		sJogo		jogo;
		
		/// @brief	Para mostrar as pontuacoes
		bool		tab_apertado;
		
		/// @brief	Flag para encerrar o programa
		bool		_quit;
		
		/// @brief	Diz se a instancia da engine esta inicializada
		bool		is_init;
		
		/// @brief	Instancia unica do singleton da engine
		static Engine*	_instance;
		
		/// @throw	ExcecaoEngineCrash Excecoes como falha ao carregar ou instanciar uma supercifie/fonte
		/// @brief	Inicializa toda a engine de interface grafica
				Engine () throw () { this->is_init = false; }
		
		/// @brief	Fecha toda a engine de interface grafica
				~Engine () throw () {}
		
		/// @brief	Inicializa uma tela da SDL
		void		inicializarSDL () throw (ExcecaoEngineCrash);
		
		/// @brief	Inicializa a estrutura de textos da SDL
		void		inicializarTTF () throw (ExcecaoEngineCrash);
		
		/// @brief	Inicializa as imagens do jogo de Domino
		void		inicializarImagens () throw (ExcecaoEngineCrash);
		
		/// @brief	Controla a taxa de FPS para quadros que terminam de ser processados antes do tempo
		void controlarFPS (void) throw ();
		
		/// @brief	Atualiza os estados das flags que controlam o input do jogo
		void receberEventos (void) throw ();
		
		/// @brief	Inicializa os ponteiro e atrasos das mensagens de log
		void inicializarLogMsgs (void) throw ();
		
		/// @brief	Libera a memoria das imagens das mensagens de log
		void fecharLogMsgs (void) throw ();
		
		/// @brief	Ajusta a posicao y das mensagens de log ao se inserir uma nova
		void setPosicoesNovaLogMsg () throw ();
		
		/// @param	segundos Tempo em segundos do atraso que sera gerado
		/// @return	Retorna true se o usuario esperou o atraso do programa ou false se o usuario clicou no botao "X"
		/// @brief	Gera um atraso com um loop sensivel ao botao "X" da janela da SDL
		bool esperar (unsigned int segundos) throw ();
		
		/// @brief	Imprime na tela a mao que o usuario enxerga
		void imprimirMaoUsuario () throw ();
		
		/// @param	jogador Indice da celular na matriz da imagem das maos dos oponentes
		/// @brief	Imprime na tela todas as pecas restantes de um oponente do jogador que o usuario ve/controla
		void imprimirMaoOponentes (int indice_jogador) throw ();
		
		/// @param	max_w Maior largura das supercifies resultantes
		/// @param	max_h Maior altura das supercifies resultantes
		/// @return	Vetor de ponteiros para supercifies com as pontuacoes desenhadas
		/// @brief	Imprime todas as mensagens de log da fila
		SDL_Surface** desenharPontuacoes (int& max_w, int& max_h) throw ();
		
		/// @param	buf Armazem para a string resultante deste metodo
		/// @param	pontos Numero de pontos do jogador cuja string esta sendo gerada
		/// @return	O proprio ponteiro do armazem recebido para colocar a string resultante
		/// @warning	O tamanho minimo do armazem deve ser char[3]
		/// @brief	Recebe um armazem de C string e a quantidade de pontos e retorna o armazem com a pontuacao ja formatada
		char* getPontosString (char* buf, int pontos) throw ();
		
		/// @brief	Imprime na tela a pontuacao de um jogador da partida
		void imprimirPontuacoes () throw ();
		
		/// @brief	Imprime as pecas que ja estao na mesa
		void imprimirPecas () throw ();
		
	public:
		
		/// @return	Retorna o ponteiro da instancia unica do singleton da engine
		/// @brief	Metodo para instanciar ou apenas retornar o ponteiro do singleton da engine
		static Engine* instance () throw ();
		
		/// @brief	Metodo para liberar a instancia unica do singleton da engine
		static void delete_instance () throw ();
		
		/// @brief	Inicializa todas as imagens fontes e variaveis de controle da engine
		void init () throw (ExcecaoEngineCrash);
		
		/// @brief	Libera toda a memoria ocupada pelas imagens e fontes da engine
		void close () throw ();
		
		/// @return	true se o usuario solicitou a saida do programa, ou false em caso contrario
		/// @brief	Checa se o usuario solicitou a saida do programa
		bool quit () throw () { return this->_quit; }
		
		/// @brief	Imprime na tela todos os objetos de uma partida do jogo de Domino
		void atualizarTela () throw ();
		
		/// @param	log_msg String da mensagem que sera mostrada
		/// @brief	Lanca uma nova mensagem de log
		void setLogMsg (std::string log_msg) throw ();
		
		/// @return	true se estiver imprimindo uma mensagem de log, false em caso contrario
		/// @brief	Verifica o estado da impressao das mensagens de log
		bool imprimindoLogMsgs (void) throw () { return ( this->log_msg[2].atraso >= SDL_GetTicks () ); }
		
		/// @param	mensagem Linha da matriz da imagem que contem as duas mensagens
		/// @param	delay Tempo em segundos a esperar mostrando a logo do jogo
		/// @brief	Mostra um quadro com a mensagem de boas-vindas/ate-logo
		void mostrarLogo (int mensagem, int delay) throw ();
		
		/// @return	Altura em pixels de uma peca
		/// @brief	Metodo de acesso
		int getAlturaPeca (void) throw () { return ( this->jogo.p_imagem_pecas->getAltura () ); }
		
		/// @return	Largura em pixels de uma peca
		/// @brief	Metodo de acesso
		int getLarguraPeca (void) throw () { return ( this->jogo.p_imagem_pecas->getLargura () ); }
		
		/// @return	Largura em pixels de uma peca na mao dos oponentes
		/// @brief	Metodo de acesso
		int getLarguraMaoOponentes (void) throw () { return ( this->jogo.p_imagem_maos->getLargura () ); }
		
		/// @param slot Slot de peca na mesa a ser inserido no comeco da lista para exibicao na tela
		/// @brief Insere um slot de peca na lista para exibicao na tela
		void insereSlotComeco (SlotPeca slot) throw () { this->jogo.slot_pecas.push_front ( slot ); }
		
		/// @param slot Slot de peca na mesa a ser inserido no fim da lista para exibicao na tela
		/// @brief Insere um slot de peca na lista para exibicao na tela
		void insereSlotFim (SlotPeca slot) throw () { this->jogo.slot_pecas.push_back ( slot ); }
		
		/// @brief Esvazia a lista de slots de pecas
		void resetarSlots () throw () { this->jogo.slot_pecas.clear (); }
		
		/// @return Referencia para a lista de slots de pecas
		/// @brief Este metodo retorna uma referencia para a lista de slots de pecas
		std::list<SlotPeca>& getSlotPecas () throw () { return this->jogo.slot_pecas; }
};

// instancia os membros static do singleton da engine
#ifdef ENGINE_SERVER
	Engine* Engine::_instance = NULL;
#endif

#endif
