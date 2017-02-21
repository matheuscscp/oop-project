/**	@defgroup MOD_MAIN "Main"
 * 	@{
 * 		@brief Modulo com todas as definicoes e implementacoes das rotinas principais
 * 	@}
 * 	
 * 	@ingroup	MOD_MAIN
 * 	@file		main.cpp
 * 	@brief		Declaracao dos defines e funcoes das rotinas principais
 * 	
 * 	@mainpage	Domino RAXASSAUM
 * 	Domino RAXASSAUM e um jogo de Domino que segue as regras utilizadas no @n
 * 	Centro Academico da Matematica da Universidade de Brasilia, feito com o @n
 * 	objetivo de quebrar a necessidade de reunir as pessoas caso elas @n
 * 	queiram jogar neste estilo particular do jogo de Domino.
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                      INCLUDES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <fstream>

#include "../../include/controller/partida.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                      FUNCOES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** @return Valor nao nulo se houver algum erro critico
 *  @brief Main. */
int main (void)
{
	int crash = 0;
	
	// redireciona a saida padrao de erros para um arquivo
	std::ofstream ferr ( "cerr.txt" );
	std::streambuf* backup = std::cerr.rdbuf ();
	std::cerr.rdbuf ( ferr.rdbuf () );
	
	crash = Partida::run ();
	
	// reseta a saida padrao de erros e fecha o arquivo
	std::cerr.rdbuf ( backup );
	ferr.close ();
	
	return ( crash );
}
