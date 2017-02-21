/**	@ingroup	MOD_IMAGEM
 * 	@file		imagem.cpp
 * 	@brief		Implementacoes dos metodos das classes das imagens da engine
 */

#include "../../include/view/imagem.hpp"

Imagem::Imagem (SDL_Surface* p_tela, std::string arquivo, int linhas, int colunas) throw (ExcecaoEngineCrash)
{
	if (p_tela == NULL)
		throw (ExcecaoEngineCrash ("Ponteiro invalido de tela ao instanciar uma imagem"));
	
	this->p_tela = p_tela;
	
	if ( !( this->p_imagem = IMG_Load ( arquivo.c_str () ) ) )
		throw (ExcecaoEngineCrash ("Erro ao carregar uma imagem "+arquivo));
	
	this->largura = this->p_imagem->w / colunas;
	this->altura = this->p_imagem->h / linhas;
}

void Imagem::imprimir (int linha, int coluna, int x, int y) throw ()
{
	SDL_Rect celula, posicao;
	
	celula.x = this->largura * coluna;
	celula.y = this->altura * linha;
	celula.w = this->largura;
	celula.h = this->altura;
	
	posicao.x = x;
	posicao.y = y;
	
	SDL_BlitSurface (this->p_imagem, &celula, this->p_tela, &posicao);
}
