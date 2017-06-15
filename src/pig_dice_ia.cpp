#include "../include/pig_dice_ia.h"
#include "../include/pig_dice_definitions.h"
#include "../include/dice.h"

action_t next_action_ia( const TurnSnapshot & ts_ )
{

    ScoreType my_pts=0;
    ScoreType op_pts=0;
    // TODO: Put your IA code here.
    std::cout << "+" << std::setfill('-') << std::setw(50) << "" << "+\n";
    std::cout << "[AI data]: current turn pts: " << ts_.curr_turn->pts << '\n';
    std::cout << "[AI data]: current # rolls: "  << ts_.curr_turn->n_rolls << '\n';

    std::cout << "[AI data]: my log:\n";
    for ( auto it( ts_.log_my_pts->begin() ) ; it != ts_.log_my_pts->end() ; ++it )
    {
        std::cout << "           <Pts:"  << it->pts << " , Rolls:"<< it->n_rolls << ">\n";
        my_pts += it->pts;
    }

    //auto my_pts = it->pts;

    std::cout << "[AI data]: Human log:\n";
    for ( auto it( ts_.log_opponents_pts->begin() ) ; it != ts_.log_opponents_pts->end() ; ++it )
    {
        std::cout << "           <Pts:"  << it->pts << " , Rolls:"<< it->n_rolls << ">\n";
        op_pts += it->pts;
    }
    //auto op_pts = it->pts;
    std::cout << "+" << std::setfill('-') << std::setw(50) << "" << "+\n";

    // Make sure the computer does not hold with zero points.
    if ( ts_.curr_turn->n_rolls == 0 ) return action_t::ROLL;

    // Dumb AI, just a random choice
    //return ( dice::roll(2) ?  action_t::ROLL : action_t::HOLD );
    
    int diff;
    ScoreType pts_at = ts_.curr_turn->pts;
    ScoreType rod = ts_.curr_turn->n_rolls;

    diff = my_pts - op_pts;
    if ( (diff < -10) and (rod < 7)){
    	return action_t::ROLL;
    } else  
    if (rod < 3) {

        if ((my_pts + pts_at) >= 100 || ((my_pts >= 90) && pts_at >= 4 && diff >= 6 )){
            return action_t::HOLD;
        }else if (diff >= 20 && my_pts >= 80 && pts_at >= 4){
            return action_t::HOLD;
        }else if (diff >= 15 && pts_at >= 6){
            return action_t::HOLD;
        }else if (pts_at >= 10){
            return action_t::HOLD;
        }else if (diff >= 10 && pts_at >= 8){
            return action_t::HOLD;
        }else if (diff >= 5 && rod == 1 && pts_at == 6){
            return action_t::HOLD;
        }else if (diff >= 5 && pts_at >= 9){
            return action_t::HOLD;
        }else return action_t::ROLL;

    }else return action_t::HOLD;
}
