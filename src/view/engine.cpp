/**	@ingroup	MOD_ENGINE
 * 	@file		engine.cpp
 * 	@brief		Implementacoes dos metodos das classes da engine grafica
 */

#define ENGINE_SERVER
#include "../../include/view/engine.hpp"

/*==============================================================================
 * Implementacoes dos metodos da classe Engine
 *==============================================================================
 */

Engine* Engine::instance () throw ()
{
	if ( !Engine::_instance )
		Engine::_instance = new Engine ();
	
	return ( Engine::_instance );
}

void Engine::delete_instance () throw ()
{
	if ( Engine::_instance )
	{
		delete ( Engine::_instance );
		Engine::_instance = NULL;
	}
}

void Engine::init () throw (ExcecaoEngineCrash)
{
	if ( !this->is_init )
	{
		try
		{
			this->inicializarSDL ();
			this->inicializarTTF ();
			this->inicializarLogMsgs ();
			this->inicializarImagens ();
			this->tab_apertado = false;
			SDL_BlitSurface (this->sdl.p_fundo, NULL, this->sdl.p_tela, NULL);
			this->is_init = true;
		}
		catch (ExcecaoEngineCrash e)
		{
			throw ( e );
		}
	}
}

void Engine::close () throw ()
{
	if ( this->is_init )
	{
		delete (this->jogo.p_imagem_pecas);
		delete (this->jogo.p_imagem_maos);
		delete (this->logo.p_imagem_tela);
		delete (this->logo.p_imagem_mensagens);
		this->fecharLogMsgs ();
		TTF_CloseFont (this->texto_config.p_fonte);
		TTF_Quit ();
		SDL_FreeSurface (this->sdl.p_fundo);
		SDL_FreeSurface (this->sdl.p_icone);
		SDL_Quit ();
		this->is_init = false;
	}
}

void Engine::inicializarSDL () throw (ExcecaoEngineCrash)
{
	// inicializando a SDL
	if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
		throw (ExcecaoEngineCrash ("Erro ao inicializar a SDL"));
	
	// settando o titulo da janela
	SDL_WM_SetCaption(TITULO_JANELA, TITULO_JANELA);
	
	// abrindo e settando o icone da janela
	if ((this->sdl.p_icone = IMG_Load ("./img/icone.png")) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar icone"));
	SDL_WM_SetIcon (this->sdl.p_icone, NULL);
	
	// abrindo a janela
	if ((this->sdl.p_tela = SDL_SetVideoMode (4 * ESCALA_TELA, 3 * ESCALA_TELA, 16, SDL_SWSURFACE)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao abrir uma janela"));
	
	// criando o fundo da tela
	this->sdl.p_fundo = SDL_CreateRGBSurface (SDL_SWSURFACE, 4 * ESCALA_TELA, 3 * ESCALA_TELA, 16, 0, 0, 0, 0);
}

void Engine::inicializarTTF () throw (ExcecaoEngineCrash)
{
	// inicializando o pacote TTF
	TTF_Init ();
	
	// abrindo e settando a fonte padrao
	if ((this->texto_config.p_fonte = TTF_OpenFont ("./ttf/Ubuntu-R.ttf", 10)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar a fonte"));
	TTF_SetFontStyle (this->texto_config.p_fonte, TTF_STYLE_NORMAL);
	
	// settando as cores padrao
	this->texto_config.cor_letra.r = 255;
	this->texto_config.cor_letra.g = 255;
	this->texto_config.cor_letra.b = 255;
	this->texto_config.cor_letra_jogando.r = 236;
	this->texto_config.cor_letra_jogando.g = 217;
	this->texto_config.cor_letra_jogando.b = 0;
	this->texto_config.cor_fundo.r = 0;
	this->texto_config.cor_fundo.g = 0;
	this->texto_config.cor_fundo.b = 0;
}

void Engine::inicializarImagens () throw (ExcecaoEngineCrash)
{
	// abrindo a tela de fundo e a imagem das mensagens
	if ((this->logo.p_imagem_tela = new Imagem (this->sdl.p_tela, "./img/logo.png", 1, 1)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar a imagem da logo"));
	if ((this->logo.p_imagem_mensagens = new Imagem (this->sdl.p_tela, "./img/logo_mensagens.png", 2, 1)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar a imagem das mensagens da logo"));
	
	// abrindo as imagens
	if ((this->jogo.p_imagem_pecas = new Imagem (this->sdl.p_tela, "./img/pecas.png", 28, 4)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar a imagem das pecas"));
	if ((this->jogo.p_imagem_maos = new Imagem (this->sdl.p_tela, "./img/maos.png", 1, 5)) == NULL)
		throw (ExcecaoEngineCrash ("Erro ao carregar a imagem das maos dos oponentes"));
}

void Engine::controlarFPS (void) throw ()
{
	static unsigned int t = 0;		// tempo da ultima chamada desde metodo
	unsigned int dt;			// tempo que passou desde a ultima chamada deste metodo
	unsigned int quadro = 1000 / FPS;	// tempo ideal a ser gasto para a execucao de um quadro
	
	dt = SDL_GetTicks () - t;
	
	if (dt < quadro)
		SDL_Delay (quadro - dt);
	else
		std::cerr << "Um quadro foi maior do que deveria." << std::endl;
	
	t = SDL_GetTicks ();
}

void Engine::atualizarTela () throw ()
{
	this->receberEventos ();
	
	// imprimindo as maos dos jogadores
	for (int i = 1; i < 4; i++)
		this->imprimirMaoOponentes ( i );
	this->imprimirMaoUsuario ();
	
	this->imprimirPecas ();
	
	// imprimindo as mensagens de log
	for (int i = 0; i < 3; i++)
		SDL_BlitSurface (this->log_msg[i].p_imagem, NULL, this->sdl.p_tela, &(this->log_msg[i].posicao));
	
	// imprimindo os scores
	if ( this->tab_apertado )
		this->imprimirPontuacoes ();
	
	// atualiza a tela literalmente
	SDL_Flip (this->sdl.p_tela);
	SDL_BlitSurface (this->sdl.p_fundo, NULL, this->sdl.p_tela, NULL);
	
	this->controlarFPS ();
}

void Engine::receberEventos (void) throw ()
{
	SDL_Event event;
	
	while ( SDL_PollEvent (&event) )
	{
		switch ( event.type )
		{
			case SDL_QUIT:
				this->_quit = true;
				break;
				
			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == '\t' )
					this->tab_apertado = true;
				else if ( ( event.key.keysym.sym == 'q' ) || ( event.key.keysym.sym == 'Q' ) || ( event.key.keysym.sym == SDLK_ESCAPE ) )
					this->_quit = true;
				break;
				
			case SDL_KEYUP:
				if ( event.key.keysym.sym == '\t' )
					this->tab_apertado = false;
				break;
		}
	}
}

void Engine::inicializarLogMsgs (void) throw ()
{
	for (int i = 0; i < 3; i++)
	{
		this->log_msg[i].p_imagem = NULL;
		this->log_msg[i].atraso = 0;
		this->log_msg[i].posicao.x = 0;
	}
}

void Engine::fecharLogMsgs (void) throw ()
{
	for (int i = 0; i < 3; i++)
	{
		if ( this->log_msg[i].p_imagem )
			SDL_FreeSurface (this->log_msg[i].p_imagem);
	}
}

void Engine::setPosicoesNovaLogMsg () throw ()
{
	if ( this->log_msg[1].p_imagem == NULL )
		this->log_msg[2].posicao.y = 0;
	else if ( this->log_msg[0].p_imagem == NULL )
	{
		this->log_msg[1].posicao.y = 0;
		this->log_msg[2].posicao.y = this->log_msg[1].p_imagem->h;
	}
	else
	{
		this->log_msg[0].posicao.y = 0;
		this->log_msg[1].posicao.y = this->log_msg[0].p_imagem->h;
		this->log_msg[2].posicao.y = this->log_msg[0].p_imagem->h + this->log_msg[1].p_imagem->h;
	}
}

void Engine::setLogMsg (std::string mensagem) throw ()
{
	if ( this->log_msg[0].p_imagem != NULL )
		SDL_FreeSurface (this->log_msg[0].p_imagem);
	
	this->log_msg[0] = this->log_msg[1];
	this->log_msg[1] = this->log_msg[2];
	
	this->log_msg[2].mensagem = mensagem;
	
	this->log_msg[2].p_imagem = TTF_RenderText_Shaded (	this->texto_config.p_fonte,
								this->log_msg[2].mensagem.c_str (),
								this->texto_config.cor_letra,
								this->texto_config.cor_fundo	);
	
	this->setPosicoesNovaLogMsg ();
	
	this->log_msg[2].atraso = SDL_GetTicks () + LOG_MSG_DELAY;
}

void Engine::mostrarLogo (int mensagem, int delay) throw ()
{
	int x_tela = 2 * ESCALA_TELA - this->logo.p_imagem_tela->getLargura () / 2;
	int y_tela = 1.5 * ESCALA_TELA - this->logo.p_imagem_tela->getAltura () / 2;
	int x_msg = 3 * ESCALA_TELA - this->logo.p_imagem_mensagens->getLargura () / 2;
	int y_msg = 2.25 * ESCALA_TELA - this->logo.p_imagem_mensagens->getAltura () / 2;
	
	this->logo.p_imagem_tela->imprimir (0, 0, x_tela, y_tela);
	this->logo.p_imagem_mensagens->imprimir (mensagem, 0, x_msg, y_msg);
	
	SDL_Flip (this->sdl.p_tela);
	SDL_BlitSurface (this->sdl.p_fundo, NULL, this->sdl.p_tela, NULL);
	
	if ( mensagem == GOODBYE )
		this->_quit = false;
	
	this->esperar ( delay );
}

bool Engine::esperar (unsigned int segundos) throw ()
{
	unsigned int atraso;
	
	atraso = SDL_GetTicks () + 1000 * segundos;
	
	while (atraso > SDL_GetTicks ())
	{
		this->receberEventos ();
		
		if (this->_quit == true)
			return (false);
	}
	
	return (true);
}

void Engine::imprimirMaoUsuario () throw ()
{
	int	total_pecas = jogadores[0].getTotalPecas ();
	int	x;
	int	y = 3 * ESCALA_TELA - this->jogo.p_imagem_pecas->getAltura ();
	int	j = 0;
	int	largura = this->jogo.p_imagem_pecas->getLargura ();
	
	for ( std::list<int>::iterator it = jogadores[0].getIndicePecas ().begin (); it != jogadores[0].getIndicePecas ().end (); it++ )
	{
		x = 2 * ESCALA_TELA - 0.25 * largura * ( 1 + total_pecas - 2 * j );
		this->jogo.p_imagem_pecas->imprimir (*it, VERTICAL, x, y);
		j++;
	}
}

void Engine::imprimirMaoOponentes (int indice_jogador) throw ()
{
	int x, y;
	int largura = this->jogo.p_imagem_maos->getLargura ();
	int altura = this->jogo.p_imagem_maos->getAltura ();
	int total_pecas = jogadores[ indice_jogador ].getTotalPecas ();
	
	for (int i = 0; i < total_pecas; i++)
	{
		x = 0;
		y = 1.5 * ESCALA_TELA + 0.25 * altura * ( 2 * i - total_pecas - 1 );
		
		if (indice_jogador == 1)
			x += 4 * ESCALA_TELA - largura;
		else if (indice_jogador == 2)
		{
			x += 2 * ESCALA_TELA - 0.5 * largura * ( total_pecas - 2 * i );
			y = 0;
		}
		
		if ( (i < total_pecas - 1) || (indice_jogador == 2) )
			this->jogo.p_imagem_maos->imprimir (0, indice_jogador - 1, x, y);
	}
	
	if (total_pecas > 0)
	{
		if (indice_jogador == 1)
			this->jogo.p_imagem_maos->imprimir (0, 3, x, y);
		else if (indice_jogador == 3)
			this->jogo.p_imagem_maos->imprimir (0, 4, x, y);
	}
}

SDL_Surface** Engine::desenharPontuacoes (int& max_w, int& max_h) throw ()
{
	SDL_Surface**	pontuacoes = new SDL_Surface*[4];
	TTF_Font*	p_fonte = TTF_OpenFont ("./ttf/Ubuntu-R.ttf", 25);
	std::string	texto;
	char		pontos[3];
	
	texto = jogadores[0].getNick () + ": " + getPontosString ( pontos,
								    jogadores[0].getPontuacao () );
	pontuacoes[0] = TTF_RenderText_Shaded (	p_fonte,
						texto.c_str (),
						( jogadores[0].jogando () ) ? this->texto_config.cor_letra_jogando : this->texto_config.cor_letra,
						this->texto_config.cor_fundo	);
	
	max_w = pontuacoes[0]->w;
	max_h = pontuacoes[0]->h;
	
	for (int i = 1; i < 4; i++)
	{
		texto = jogadores[i].getNick () + ": " + getPontosString ( pontos,
									    jogadores[i].getPontuacao () );
		pontuacoes[i] = TTF_RenderText_Shaded (	p_fonte,
							texto.c_str (),
							( jogadores[i].jogando () ) ? this->texto_config.cor_letra_jogando : this->texto_config.cor_letra,
							this->texto_config.cor_fundo);
		if (max_w < pontuacoes[i]->w)
			max_w = pontuacoes[i]->w;
		max_h += pontuacoes[i]->h;
	}
	
	TTF_CloseFont (p_fonte);
	
	return ( pontuacoes );
}

char* Engine::getPontosString (char* buf, int pontos) throw ()
{
	if (pontos >= 10)
	{
		buf[0] = '0' + ( ( pontos - ( pontos % 10 ) ) / 10 );
		buf[1] = '0' + ( pontos % 10 );
		buf[2] = '\0';
	}
	else
	{
		buf[0] = '0' + pontos;
		buf[1] = '\0';
	}
	
	return (buf);
}

void Engine::imprimirPontuacoes () throw ()
{
	SDL_Rect	posicao;
	SDL_Surface**	pontuacoes;
	SDL_Surface*	p_fundo;
	int		max_w, max_h;
	
	pontuacoes = this->desenharPontuacoes ( max_w, max_h );
	
	p_fundo = SDL_CreateRGBSurface (SDL_SWSURFACE, max_w, max_h, 16, 0, 0, 0, 0);
	
	posicao.x = 2 * ESCALA_TELA - 0.5 * max_w;
	posicao.y = 1.5 * ESCALA_TELA - 0.5 * max_h;
	
	SDL_BlitSurface (p_fundo, NULL, this->sdl.p_tela, &posicao);
	
	SDL_BlitSurface (pontuacoes[0], NULL, this->sdl.p_tela, &posicao);
	
	for (int i = 1; i < 4; i++)
	{
		posicao.y += pontuacoes[i - 1]->h;
		SDL_BlitSurface (pontuacoes[i], NULL, this->sdl.p_tela, &posicao);
	}
	
	SDL_FreeSurface (p_fundo);
	
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface (pontuacoes[i]);
	delete[] ( pontuacoes );
}

void Engine::imprimirPecas () throw ()
{
	std::list<int>::iterator	it1 = mesa->getIndicePecas ().begin ();
	std::list<SlotPeca>::iterator	it2 = this->jogo.slot_pecas.begin ();
	
	while ( it2 != this->jogo.slot_pecas.end () )
	{
		this->jogo.p_imagem_pecas->imprimir ( *it1, it2->getEstado (), it2->getX (), it2->getY () );
		
		it1++;
		it2++;
	}
}

/*==============================================================================
 * FIM
 *==============================================================================
 */
