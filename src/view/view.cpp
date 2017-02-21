/**	@ingroup	MOD_VIEW
 * 	@file		view.cpp
 * 	@brief		Implementacoes dos metodos das classes do principal gerenciador de interface com o usuario
 */

#define VIEW_SERVER
#include "../../include/view/view.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					 METODOS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

View::View () throw ()
{
	this->regiao_comeco = NULL;
	this->regiao_fim = NULL;
}

View::~View () throw ()
{
	if ( this->regiao_comeco )
		delete ( this->regiao_comeco );
	if ( this->regiao_fim )
		delete ( this->regiao_fim );
}

View* View::instance () throw ()
{
	if ( !View::_instance )
		View::_instance = new View ();
	
	return ( View::_instance );
}

void View::delete_instance () throw ()
{
	if ( View::_instance )
	{
		delete ( View::_instance );
		View::_instance = NULL;
	}
}

void View::posicionarPrimeiraPeca (int indice_peca) throw ()
{
	engine->insereSlotComeco ( SlotPeca (	( ( pecas[ indice_peca ].bucha () ) ? VERTICAL : HORIZONTAL ),
						2 * ESCALA_TELA - engine->getLarguraPeca () / 2,
						1.5 * ESCALA_TELA - engine->getAlturaPeca () / 2	) );
	
	if ( this->regiao_comeco )
		delete ( this->regiao_comeco );
	this->regiao_comeco = new Regiao1Comeco ();
	if ( this->regiao_fim )
		delete ( this->regiao_fim );
	this->regiao_fim = new Regiao1Fim ();
}

void View::posicionarPeca (const sJogada& jogada) throw ()
{
	if ( jogada.ponta == 'C' )
		this->posicionarPecaComeco ( jogada );
	else
		this->posicionarPecaFim ( jogada );
}

void View::posicionarPecaComeco (const sJogada& jogada) throw ()
{
	Regiao* nova_regiao;
	
	nova_regiao = this->regiao_comeco->setEstadoXY ( jogada, engine->getSlotPecas ().front () );
	if ( nova_regiao != this->regiao_comeco )
	{
		delete ( this->regiao_comeco );
		this->regiao_comeco = nova_regiao;
	}
}

void View::posicionarPecaFim (const sJogada& jogada) throw ()
{
	Regiao* nova_regiao;
	
	nova_regiao = this->regiao_fim->setEstadoXY ( jogada, engine->getSlotPecas ().back () );
	if ( nova_regiao != this->regiao_fim )
	{
		delete ( this->regiao_fim );
		this->regiao_fim = nova_regiao;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *					CLASSES DAS REGIOES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Regiao* Regiao1Comeco::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	int		largura_restante;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		largura_restante = slot_mesa.getX () - engine->getLarguraMaoOponentes () + 0.25 * engine->getLarguraPeca ();
		
		if ( largura_restante >= engine->getLarguraPeca () )
		{
			estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
			
			x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
			y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
			
			nova_regiao = this;
		}
		else
		{
			estado = ( (jogada.lado_peca == 'B') ? VERTICAL : VERTICAL_INVERTIDA );
			
			x = ( slot_mesa.getX () );
			y = ( slot_mesa.getY () - engine->getAlturaPeca () );
			
			nova_regiao = new Regiao2Comeco ();
		}
	}
	
	engine->insereSlotComeco ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao1Comeco::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = slot_mesa.getX () - engine->getLarguraMaoOponentes ();
	
	if ( !pecas [ jogada.indice_peca ].bucha () )
		this->mesaNaoBuchaNovaNaoBucha ( jogada, slot_mesa, nova_regiao, estado, x, y, largura_restante );
	else
	{
		estado = ( VERTICAL );
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
			y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
			
			*nova_regiao = this;
		}
		else
		{
			x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
			
			*nova_regiao = new Regiao2Comeco ();
		}
	}
}

void Regiao1Comeco::mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante)
{
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		
		x = ( slot_mesa.getX () - engine->getLarguraPeca () );
		y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL : VERTICAL_INVERTIDA );
		
		*nova_regiao = new Regiao2Comeco ();
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.25 * engine->getAlturaPeca () );
		}
		else
		{
			x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
		}
	}
}

Regiao* Regiao2Comeco::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		
		x = ( slot_mesa.getX () + engine->getLarguraPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 1 : 0.75 ) );
		y = ( slot_mesa.getY () - engine->getAlturaPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 0 : 0.25 ) );
		
		nova_regiao = new Regiao3Comeco ();
	}
	
	engine->insereSlotComeco ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao2Comeco::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	if ( pecas [ jogada.indice_peca ].bucha () )
	{
		estado = ( HORIZONTAL );
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		*nova_regiao = new Regiao3Comeco ();
	}
	
	if ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () == 1.5 * ESCALA_TELA )
	{
		x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
	}
	else
	{
		x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () - 0.25 * engine->getAlturaPeca () );
	}
}

Regiao* Regiao3Comeco::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		if ( slot_mesa.getEstado () != HORIZONTAL )
			this->mesaBuchaNaoHorizontal ( jogada, slot_mesa, &nova_regiao, estado, x, y );
		else
		{
			estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
			
			x = ( slot_mesa.getX () + engine->getLarguraPeca () );
			y = ( slot_mesa.getY () );
			
			nova_regiao = this;
		}
	}
	
	engine->insereSlotComeco ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao3Comeco::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = 4 * ESCALA_TELA - slot_mesa.getX () - engine->getLarguraMaoOponentes () - engine->getLarguraPeca ();
	
	if ( !pecas [ jogada.indice_peca ].bucha () )
		this->mesaNaoBuchaNovaNaoBucha ( jogada, slot_mesa, nova_regiao, estado, x, y, largura_restante );
	else
	{
		estado = ( VERTICAL );
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () );
			
			*nova_regiao = this;
		}
		else
		{
			x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
			
			*nova_regiao = new Regiao4Comeco ();
		}
	}
}

void Regiao3Comeco::mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante)
{
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		
		x = ( slot_mesa.getX () + engine->getLarguraPeca () );
		y = ( slot_mesa.getY () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL : VERTICAL_INVERTIDA );
		
		*nova_regiao = new Regiao4Comeco ();
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.25 * engine->getAlturaPeca () );
		}
		else
		{
			x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
		}
	}
}

void Regiao3Comeco::mesaBuchaNaoHorizontal (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = 4 * ESCALA_TELA - slot_mesa.getX () - engine->getLarguraMaoOponentes () - 0.75 * engine->getLarguraPeca ();
	
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		
		x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL : VERTICAL_INVERTIDA );
		
		x = ( slot_mesa.getX () );
		y = ( slot_mesa.getY () - engine->getAlturaPeca () );
		
		*nova_regiao = new Regiao4Comeco ();
	}
}

Regiao* Regiao4Comeco::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		
		x = ( slot_mesa.getX () - engine->getLarguraPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 1 : 0.75 ) );
		y = ( slot_mesa.getY () - engine->getAlturaPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 0 : 0.25 ) );
		
		nova_regiao = new Regiao5Comeco ();
	}
	
	engine->insereSlotComeco ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao4Comeco::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	if ( pecas [ jogada.indice_peca ].bucha () )
	{
		estado = ( HORIZONTAL );
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		*nova_regiao = new Regiao5Comeco ();
	}
	
	std::list<SlotPeca>::iterator it = engine->getSlotPecas ().begin ();
	it++;
	if ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () == it->getY () )
	{
		x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () - 0.75 * engine->getAlturaPeca () );
	}
	else
	{
		x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () - 0.25 * engine->getAlturaPeca () );
	}
}

Regiao* Regiao5Comeco::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( pecas [ jogada.indice_peca ].bucha () )
		estado = ( VERTICAL );
	else
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
	
	if (	( pecas [ jogada.indice_peca ].bucha () ) ||
		( ( pecas [ jogada.indice_mesa ].bucha () ) && ( slot_mesa.getEstado () == VERTICAL ) )	)
		x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
	else
		x = ( slot_mesa.getX () - engine->getLarguraPeca () );
	y = ( slot_mesa.getY () );
	
	nova_regiao = this;
	
	engine->insereSlotComeco ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

Regiao* Regiao1Fim::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	int		largura_restante;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		largura_restante = 4 * ESCALA_TELA - slot_mesa.getX () - engine->getLarguraMaoOponentes () - 0.75 * engine->getLarguraPeca ();
		
		if ( largura_restante >= engine->getLarguraPeca () )
		{
			estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
			
			x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
			y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
			
			nova_regiao = this;
		}
		else
		{
			estado = ( (jogada.lado_peca == 'B') ? VERTICAL_INVERTIDA : VERTICAL );
			
			x = ( slot_mesa.getX () );
			y = ( slot_mesa.getY () + engine->getAlturaPeca () );
			
			nova_regiao = new Regiao2Fim ();
		}
	}
	
	engine->insereSlotFim ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao1Fim::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = 4 * ESCALA_TELA - slot_mesa.getX () - engine->getLarguraMaoOponentes () - engine->getLarguraPeca ();
	
	if ( !pecas [ jogada.indice_peca ].bucha () )
		this->mesaNaoBuchaNovaNaoBucha ( jogada, slot_mesa, nova_regiao, estado, x, y, largura_restante );
	else
	{
		estado = ( VERTICAL );
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
			y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
			
			*nova_regiao = this;
		}
		else
		{
			x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
			
			*nova_regiao = new Regiao2Fim ();
		}
	}
}

void Regiao1Fim::mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante)
{
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		
		x = ( slot_mesa.getX () + engine->getLarguraPeca () );
		y = ( 1.5 * ESCALA_TELA - 0.5 * engine->getAlturaPeca () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL_INVERTIDA : VERTICAL );
		
		*nova_regiao = new Regiao2Fim ();
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () );
		}
		else
		{
			x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
		}
	}
}

Regiao* Regiao2Fim::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		
		x = ( slot_mesa.getX () - engine->getLarguraPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 1 : 0.75 ) );
		y = ( slot_mesa.getY () + engine->getAlturaPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 0 : 0.25 ) );
		
		nova_regiao = new Regiao3Fim ();
	}
	
	engine->insereSlotFim ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao2Fim::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	if ( pecas [ jogada.indice_peca ].bucha () )
	{
		estado = ( HORIZONTAL );
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		*nova_regiao = new Regiao3Fim ();
	}
	
	if ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () == 1.5 * ESCALA_TELA )
	{
		x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
	}
	else
	{
		x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () );
	}
}

Regiao* Regiao3Fim::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		if ( slot_mesa.getEstado () != HORIZONTAL )
			this->mesaBuchaNaoHorizontal ( jogada, slot_mesa, &nova_regiao, estado, x, y );
		else
		{
			estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
			
			x = ( slot_mesa.getX () - engine->getLarguraPeca () );
			y = ( slot_mesa.getY () );
			
			nova_regiao = this;
		}
	}
	
	engine->insereSlotFim ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao3Fim::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = slot_mesa.getX () - engine->getLarguraMaoOponentes ();
	
	if ( !pecas [ jogada.indice_peca ].bucha () )
		this->mesaNaoBuchaNovaNaoBucha ( jogada, slot_mesa, nova_regiao, estado, x, y, largura_restante );
	else
	{
		estado = ( VERTICAL );
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () );
			
			*nova_regiao = this;
		}
		else
		{
			x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
			
			*nova_regiao = new Regiao4Fim ();
		}
	}
}

void Regiao3Fim::mesaNaoBuchaNovaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y, int largura_restante)
{
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		
		x = ( slot_mesa.getX () - engine->getLarguraPeca () );
		y = ( slot_mesa.getY () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL_INVERTIDA : VERTICAL );
		
		*nova_regiao = new Regiao4Fim ();
		
		if ( largura_restante >= 0.5 * engine->getLarguraPeca () )
		{
			x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () );
		}
		else
		{
			x = ( slot_mesa.getX () - 0.25 * engine->getLarguraPeca () );
			y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
		}
	}
}

void Regiao3Fim::mesaBuchaNaoHorizontal (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	int largura_restante = slot_mesa.getX () - engine->getLarguraMaoOponentes () + 0.25 * engine->getLarguraPeca ();
	
	if ( largura_restante >= engine->getLarguraPeca () )
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL : HORIZONTAL_INVERTIDA );
		
		x = ( slot_mesa.getX () - 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () );
		
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? VERTICAL_INVERTIDA : VERTICAL );
		
		x = ( slot_mesa.getX () );
		y = ( slot_mesa.getY () + engine->getAlturaPeca () );
		
		*nova_regiao = new Regiao4Fim ();
	}
}

Regiao* Regiao4Fim::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( !pecas[ jogada.indice_mesa ].bucha () )
		this->mesaNaoBucha ( jogada, slot_mesa, &nova_regiao, estado, x, y );
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		
		x = ( slot_mesa.getX () + engine->getLarguraPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 1 : 0.75 ) );
		y = ( slot_mesa.getY () + engine->getAlturaPeca () * ( ( slot_mesa.getEstado () == HORIZONTAL ) ? 0 : 0.25 ) );
		
		nova_regiao = new Regiao5Fim ();
	}
	
	engine->insereSlotFim ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

void Regiao4Fim::mesaNaoBucha (const sJogada& jogada, const SlotPeca& slot_mesa, Regiao** nova_regiao, tEstadoSlot& estado, int& x, int& y)
{
	if ( pecas [ jogada.indice_peca ].bucha () )
	{
		estado = ( HORIZONTAL );
		*nova_regiao = this;
	}
	else
	{
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
		*nova_regiao = new Regiao5Fim ();
	}
	
	std::list<SlotPeca>::iterator it = engine->getSlotPecas ().end ();
	it--;
	it--;
	if ( slot_mesa.getY () - 0.25 * engine->getAlturaPeca () == it->getY () )
	{
		x = ( slot_mesa.getX () + 0.25 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () + 0.75 * engine->getAlturaPeca () );
	}
	else
	{
		x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
		y = ( slot_mesa.getY () + 0.25 * engine->getAlturaPeca () );
	}
}

Regiao* Regiao5Fim::setEstadoXY (const sJogada& jogada, const SlotPeca& slot_mesa)
{
	Regiao*		nova_regiao;
	tEstadoSlot	estado;
	int		x, y;
	
	if ( pecas [ jogada.indice_peca ].bucha () )
		estado = ( VERTICAL );
	else
		estado = ( (jogada.lado_peca == 'B') ? HORIZONTAL_INVERTIDA : HORIZONTAL );
	
	if (	( pecas [ jogada.indice_peca ].bucha () ) ||
		( ( pecas [ jogada.indice_mesa ].bucha () ) && ( slot_mesa.getEstado () == VERTICAL ) )	)
		x = ( slot_mesa.getX () + 0.75 * engine->getLarguraPeca () );
	else
		x = ( slot_mesa.getX () + engine->getLarguraPeca () );
	y = ( slot_mesa.getY () );
	
	nova_regiao = this;
	
	engine->insereSlotFim ( SlotPeca ( estado, x, y ) );
	
	return ( nova_regiao );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *					FIM
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
