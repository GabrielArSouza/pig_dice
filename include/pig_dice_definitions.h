#ifndef _PIG_DICE_DEFINITIONS_H_
#define _PIG_DICE_DEFINITIONS_H_

#include <iostream>   // std::cout, std::cin, std::endl
#include <string>     // std::string
#include <functional> // std::function
#include <iomanip>    // std::setw, std::setfill
#include <vector>     // std::vector
#include <utility>    // std::pair, std::get<>()

#include "dice.h"

/// Enumaration for each dice face.
enum dice_face_t { FACE_1=0, FACE_2, FACE_3, FACE_4, FACE_5, FACE_6, N_FACES };

/// Type associated with scores in this game.
using ScoreType = std::size_t;

/*!
 * A turn item is a pair that associates a score (pts) and the number
 * of times the dice was rolled to produce the score.
 * For instance: < 21, 4 > means that the player got 21 pts after
 * rolling the fice 4 times.
 */
struct TurnItem {
    ScoreType pts;
    std::size_t n_rolls;
};

/// Enumaration for the player's action type.
enum class action_t { ROLL=0, HOLD };

/// How many players?
const short N_PLAYERS = 2;          // # of players in a match.
const ScoreType WINING_SCORE = 100; // Minimum score to win.

// Forward declarations: to avoid circular definition deadlocks.
struct Player;
struct TurnSnapshot;
struct GameState;

/// Representing a single player.
struct Player {
    std::string name; //<! The player's name
    std::vector< TurnItem > log_turns; //<! Log of turns played.
    std::function< action_t ( const TurnSnapshot & ) > action; //!< Function that requests the player action.
};

/// The overall game state that we must keep updated.
struct GameState {
    ScoreType score_players[ N_PLAYERS ]; //!< The score of each player.
    Player players[ N_PLAYERS ]; //!< List of players
    size_t curr_player; //!< Index of the current player. 
    dice::FaceType curr_face; //!< Current dice face.
    action_t curr_action; //!< Action chosen by the current player.
    TurnItem curr_turn;   //!< Current turn status <pts, # of times dice has been rolled>/
    size_t winner; //!< Index of the winner.
};

/// Snapshot of a turn, passed on to the AI/player so that it can decide the next action.
struct TurnSnapshot {
    const TurnItem *curr_turn;                      //!< Turn in progress: < pts, # of times dice was rolled so far >
    const std::vector<TurnItem> *log_my_pts;        //!< Current player's log of pts acquired during the game.
    const std::vector<TurnItem> *log_opponents_pts; //!< Opponent player's log of pts acquired during the game.
};
// Note #1: to determine the current overall score of a player we need to
//          sum up the points in his/her/its log.


#endif
