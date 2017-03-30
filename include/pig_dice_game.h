#ifndef _PIG_DICE_GAME_H_
#define _PIG_DICE_GAME_H_

#include <iostream>   // std::cout, std::cin, std::endl
#include <string>     // std::string
#include <functional> // std::function
#include <iomanip>    // std::setw, std::setfill

#include "pig_dice_definitions.h"
#include "pig_dice_ia.h"


/*!
 * Ask user for the next action, which might be either ROLL or HOLD.
 * \param turn_total_ Number of points accumulated in the current turn.
 * \param my_pts_ Number of points of the current player (human).
 * \param opponent_pts_ Number of points of the opponent player.
 * \param n_my_turn_rolls_ Number of time the dice has been rolled in this turn.
 *
 * \return The next action, chosen by the player.
 */
action_t next_action_user( const TurnSnapshot & ts_ );

/*!
 * Prints a welcome msg on the standard output.
 * \param gst_ The game state.
 */
void render_welcome_msg( const GameState & gst_ );

/*!
 * Initalize the game state.
 * Reset all scores, and the random seed.
 * This method algo chooses who is going to start the game.
 *
 * \param gst_ The game state.
 */
void initialize_game( GameState &gst_ );

/*!
 * Checks in the game state if one of the player has won.
 * In that case, the game state stores the winner.
 *
 * \param gst_ The game state.
 * \return true if a player has won, false otherwise.
 */
bool game_over( GameState &gst_ );

/*!
 * Process the game events.
 * In this context, this means to ask the current player (either a
 * human or the AI) for the next action (either ROLL or HOLD).
 *
 * \param gst_ The game state.
 */
void process_events( GameState &gst_ );

/*!
 * Update the game.
 * In this context, the method process the action chosen by the
 * current player. This might add points to the current turn,
 * to the current player, or pass the turn to the opponent.
 *
 * \param gst_ The game state.
 */
void update( GameState & gst_ );

/*!
 * Print the game overal state on the standard output.
 *
 * \param gst_ The game state.
 */
void render( GameState & gst_ );

/*!
 * Render the log of turns for each player.
 *
 * \param gst_ The game state.
 */
void render_log ( const GameState & gst_ );

#endif
