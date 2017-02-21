/**	@defgroup MOD_VIEW "View"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes do principal gerenciador de interface com o usuario
 * 	@}
 * 	@ingroup MOD_VIEW
 * 	@file	view.hpp
 * 	@brief	Declaracao dos defines, classes e metodos do principal gerenciador de interface com o usuario
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include "./engine.hpp"

/**	Define um macro para simplificar a chamada ao singleton da classe View
 * 	@brief	Instancia do visualizador
 */
#define view	View::instance ()

/** @brief Classe abstrata para determinar a regiao da nova peca que esta sendo encaixada na mesa, seu estado e sua posicao na tela */
class Regiao
{
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo polimorfico abstrato que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		virtual Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa) = 0;
};

/** @brief Especializacao de uma regiao para a regiao 1 do comeco da mesa */
class Regiao1Comeco : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 2 do comeco da mesa */
class Regiao2Comeco : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 3 do comeco da mesa */
class Regiao3Comeco : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaBuchaNaoHorizontal (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 4 do comeco da mesa */
class Regiao4Comeco : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 5 do comeco da mesa */
class Regiao5Comeco : public Regiao
{
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 1 do comeco da mesa */
class Regiao1Fim : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 2 do comeco da mesa */
class Regiao2Fim : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 3 do comeco da mesa */
class Regiao3Fim : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante);
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaBuchaNaoHorizontal (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 4 do comeco da mesa */
class Regiao4Fim : public Regiao
{
	private:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @param nova_regiao Ponteiro para o ponteiro da regiao que a nova peca ira ocupar
		 *  @param estado Referencia para a variavel de estado do novo slot
		 *  @param x Referencia para a posicao x do novo slot
		 *  @param y Referencia para a posicao y do novo slot
		 *  @brief Determina a nova regiao, o estado, x e y */
		void mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y);
		
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/** @brief Especializacao de uma regiao para a regiao 5 do comeco da mesa */
class Regiao5Fim : public Regiao
{
	public:
		
		/** @param jogada Referencia para uma jogada constante que determina os outros parametros
		 *  @param slot_mesa Referencia do slot da ponta da mesa cuja jogada foi feita
		 *  @return Ponteiro para a regiao em que a nova peca estara encaixada
		 *  @brief Metodo concreto que deve encontrar a regiao, o estado e a posicao da nova peca que esta sendo encaixada na mesa */
		Regiao* setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa);
};

/// @brief Classe para gerenciar a interface com o usuario
class View
{
	private:
		
		/// @brief	Ponteiro para o singleton desta classe
		static View*	_instance;
		
		/// @brief	Atributo para manter a estrategia a ser usando naquela etapa de inclusao de pecas na tela para o comeco da mesa
		Regiao*		regiao_comeco;
		
		/// @brief	Atributo para manter a estrategia a ser usando naquela etapa de inclusao de pecas na tela para o fim da mesa
		Regiao*		regiao_fim;
		
		/// @brief Construtor
		View () throw ();
		
		/// @brief Destrutor
		~View () throw ();
		
		/// @param jogada Detalhes da jogada que esta sendo feita pelo controlador
		/// @brief Posiciona uma peca no comeco da mesa para que ela seja exibida na tela
		void posicionarPecaComeco (const sJogada& jogada) throw ();
		
		/// @param jogada Detalhes da jogada que esta sendo feita pelo controlador
		/// @brief Posiciona uma peca no fim da mesa para que ela seja exibida na tela
		void posicionarPecaFim (const sJogada& jogada) throw ();
		
	public:
		
		/// @return Ponteiro para o singleton desta classe
		/// @brief Instancia ou apenas retorna o ponteiro para o singleton desta classe
		static View* instance () throw ();
		
		/// @brief Libera o singleton desta classe chamando o destrutor privado
		static void delete_instance () throw ();
		
		/// @param indice_peca Indice da peca que esta sendo posicionada no meio da mesa
		/// @brief Posiciona uma peca no meio da mesa para que ela seja exibida na tela
		void posicionarPrimeiraPeca (int indice_peca) throw ();
		
		/// @param jogada Detalhes da jogada que esta sendo feita pelo controlador
		/// @brief Posiciona uma peca no lugar correto da mesa para que ela seja exibida na tela
		void posicionarPeca (const sJogada& jogada) throw ();
};

// instanciando os membros estaticos do singleton da classe View
#ifdef VIEW_SERVER
	View* View::_instance = NULL;
#endif

#endif
