/**	@defgroup MOD_IMAGEM "Imagem"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes das imagens da engine
 * 	@}
 * 	@ingroup MOD_IMAGEM
 * 	@file	imagem.hpp
 * 	@brief	Declaracao dos defines, classes e metodos das imagens da engine
 */

#ifndef IMAGEM_HPP
#define IMAGEM_HPP

#include <string>

#include "../SDL/SDL_image.h"

/**	@brief Excecao para um algum erro critico (o programa sera encerrado imediatamente) */
class ExcecaoEngineCrash
{
	public:
		/// @brief String que diz qual foi o erro ocorrido
		std::string erro;
		
		/** @param erro String que diz qual foi o erro ocorrido
		 *  @brief Construtor para armazenar o erro ocorrido */
		ExcecaoEngineCrash (std::string erro) throw () { this->erro = erro; }
};

/**
 * @brief Definicoes da classe que lida com imagens
 */
class Imagem
{
	private:
		
		/// @brief	Ponteiro para a supercifie da tela
		SDL_Surface*	p_tela;
		
		/// @brief	Ponteiro para a supercifie da imagem
		SDL_Surface*	p_imagem;
		
		/// @brief	Tamanho da largura em pixels de uma celula da matriz dividida imagem
		int		largura;
		
		/// @brief	Tamanho da altura em pixels de uma celula da matriz dividida imagem
		int		altura;
		
	public:
		
		/// @param	p_tela			Ponteiro para a supercifie da tela
		/// @param	arquivo			String do diretorio do arquivo da imagem
		/// @param	linhas			Numero de linhas da divisao em matriz
		/// @param	colunas			Numero de colunas da divisao em matriz
		/// @throw	ExcecaoEngineCrash	Para o caso do ponteiro da tela ser NULL ou nao ser possivel carregar uma imagem
		/// @brief	Construtor
		Imagem (SDL_Surface* p_tela, std::string arquivo, int linhas, int colunas) throw (ExcecaoEngineCrash);
		
		/// @brief	Destrutor
		~Imagem (void) throw () { SDL_FreeSurface (this->p_imagem); }
		
		/// @param	linha	Indice da linha da celula da matriz
		/// @param	coluna	Indice da coluna da celula da matriz
		/// @param	x	Coordenada origem x da impressao na tela da janela da SDL
		/// @param	y	Coordenada origem y da impressao na tela da janela da SDL
		/// @brief	Imprime uma celula da matriz dividida da imagem
		void imprimir (int linha, int coluna, int x, int y) throw ();
		
		/// @return	Retorna a largura em pixels de uma celular da matriz dividida
		/// @brief	Metodo de acesso para a largura de uma celula
		int getLargura (void) throw () { return (this->largura); }
		
		/// @return	Retorna a altura em pixels de uma celular da matriz dividida
		/// @brief	Metodo de acesso para a altura de uma celula
		int getAltura (void) throw () { return (this->altura); }
};

#endif
