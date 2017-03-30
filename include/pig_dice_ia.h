#ifndef _PIG_DICE_IA_H_
#define _PIG_DICE_IA_H_

#include "pig_dice_definitions.h"

/*!
 *  Solicita a próxima ação para a Inteligência Artificial.
 *
 *  \param turn_total_ Pontos acumulados da rodada atual.
 *  \param my_pts_ Pontuação geral da IA acumulado até o presente.
 *  \param opponent_pts_ Pontuação geral do oponente acumulado até o presente.
 *  \param n_my_turn_rolls_ Quantidade de vezes que o dado foi lançado pela IA nesta rodada.
 */
action_t next_action_ia( const TurnSnapshot & ts_ );

#endif
