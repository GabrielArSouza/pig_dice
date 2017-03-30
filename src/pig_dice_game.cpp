/*!
 *
 * Main program, which should contain the main game loop.
 *
 * \author
 * \date
 */

#include "../include/pig_dice_game.h"

action_t next_action_user( const TurnSnapshot & ts_ )
{
    std::cout << ">>> Press enter to ROLL, or type anything then press enter to HOLD\n";
    std::string input = "";
    getline( std::cin, input );
    return ( input == "" ) ? action_t::ROLL : action_t::HOLD ;
}

void render_welcome_msg( const GameState & gst_ )
{
    std::cout << "\n ---> Welcome to the Pig Dice game <---\n\n";

    std::cout << ">>> The players of the game are:\n";
    for ( auto i(0) ; i < N_PLAYERS ; ++i )
        std::cout << i+1 << ". \"" << gst_.players[i].name << "\"\n";

    std::cout << std::endl;
}

void initialize_game( GameState &gst_ )
{
    // Escolhendo se o dado eh randomico ou não.
    //dice::set_seed( dice::seed_t::FIXED, 1 ); // Semente fixada em 1.
    dice::set_seed( dice::seed_t::RANDOM ); // Semente fixada em 1.

    // Reset the players' score.
    for( auto & e : gst_.score_players )
        e = 0;

    // Reset turn data.
    gst_.curr_turn.pts= 0; // Score
    gst_.curr_turn.n_rolls = 0; // Number of times the dice has been rolled during the current turn.
    // Set player fields
    gst_.players[0].name = "Computer";
    gst_.players[0].action = next_action_ia;
    gst_.players[0].log_turns.clear();
    gst_.players[1].name = "Human";
    gst_.players[1].action = next_action_user;
    gst_.players[1].log_turns.clear();
    // Decide the starting player.
    gst_.curr_player = dice::roll(2); // heads or tails?
    // Set current face.
    gst_.curr_face = N_FACES; // Not a valid face.
    // set current action.
    gst_.curr_action = action_t::ROLL;
    // No winner yet.
    gst_.winner = -1;

    // Display welcoming screen.
    render_welcome_msg( gst_ );
}

bool game_over( GameState &gst_ )
{
    bool over( false );

    // Check the score of the players.
    for( auto i(0) ; i < N_PLAYERS ; ++i )
    {
        // How many points for this player?
        if ( gst_.score_players[i] >= WINING_SCORE )
        {
            over = true; // It's over.
            gst_.winner = i; // Save the winner index for later.
        }
    }

   return over;
}

void process_events( GameState &gst_ )
{
    // Determine the index of the opponent player.
    auto opponent = (gst_.curr_player+1) % N_PLAYERS;

    // Show whose turn is it now.
    std::cout << "\n>>> The current player is \""
              << gst_.players[gst_.curr_player].name
              << "\"\n";

    // set up a turn snapshot.
    TurnSnapshot ts;
    ts.curr_turn         = & gst_.curr_turn;
    ts.log_my_pts        = & gst_.players[gst_.curr_player].log_turns;
    ts.log_opponents_pts = & gst_.players[opponent].log_turns;

    // Ask the current player for his/her action.
    gst_.curr_action = gst_.players[gst_.curr_player].action( ts );
}

void update( GameState & gst_ )
{
    // Determine the index of the opponent player.
    auto opponent = (gst_.curr_player+1) % N_PLAYERS;

    if ( gst_.curr_action == action_t::ROLL ) // ROLL action
    {
        gst_.curr_face = dice::roll(); // Roll the dice and...
        gst_.curr_turn.n_rolls++;      // ... increase number of dice rolls so far.

        // Which face we got?
        if ( gst_.curr_face == FACE_1 ) // face = pig!
        {
            gst_.curr_turn.pts = 0; // Sorry, lost everything. Reset the turn pts
        }
        else // Face must be one of: 2, 3, 4, 5, 6.
        {
            gst_.curr_turn.pts += gst_.curr_face+1; // Accumulate score.
        }
    }
    else  // HOLD action.
    {
        // Accumulate the turn total into the current player's score.
        gst_.score_players[ gst_.curr_player ] += gst_.curr_turn.pts;
    }

    // Do we need to reset the turn data and switch players?
    // Don't forget to save the log for this turn!
    if ( gst_.curr_action == action_t::HOLD or gst_.curr_face == FACE_1 )
    {
        // Update the player's log of turns. This might be usefull for the AI!!
        gst_.players[gst_.curr_player].log_turns.emplace_back( std::move( gst_.curr_turn ) );
        // Switch players
        gst_.curr_player = opponent;
        // Reset the turn data: pts and # of dice rolls.
        gst_.curr_turn.pts = gst_.curr_turn.n_rolls = 0;
    }
}

void render( GameState & gst_ )
{
    /// String representation for the dice's faces (Unicode).
    const std::string dice_faces[] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };

    // Show the action chosen by the current player.
    if ( gst_.curr_action == action_t::ROLL )
        std::cout << "Roll: " << dice_faces[ gst_.curr_face ] << std::endl;
    else
        std::cout << "Hold!\n";

    std::cout << "\n>>> The turn total is: " << gst_.curr_turn.pts  << std::endl;


    //********* LET US PRINT A SCORE BOARD TABLE ***********//

    auto table_len(31); // Table length, including the borders.
    auto single_cell_len( table_len-2 ); // Excluding the border characters.
    auto double_cell_len( (table_len-3)/2 ); // Excluding 3 border characters.
    std::string table_label = "Score Board";
    auto label_pos = single_cell_len/2 + ( table_label.size()/2 ); // center the label
    std::cout << "+" << std::setw(single_cell_len) << std::setfill( '=' ) << "" << "+" << std::endl;
    std::cout << "|" << std::setw(label_pos) << std::setfill(' ') << "Score Board"
              << std::setw(single_cell_len-label_pos) << std::setfill(' ') << "" << "|\n";
    std::cout << "+" << std::setw(double_cell_len) << std::setfill( '=' ) << ""
              << "+" << std::setw(double_cell_len) << "" << "+\n";

    // Print a line per player.
    for( auto i(0) ; i < N_PLAYERS ; ++i )
    {
        std::cout << "|"
                  << std::setw(double_cell_len) << std::setfill(' ')
                  << gst_.players[ i ].name
                  << "|"
                  << std::setw(double_cell_len)
                  << gst_.score_players[ i ]
                  << "|\n";
    }
    std::cout << "+" << std::setw(single_cell_len) << std::setfill( '=' ) << "" << "+" << std::endl;

    //********* END OF SCORE BOARD TABLE ***********//

    // Do we have a winner?
    if ( game_over( gst_ ) )
    {
        std::cout << "\a\n\n>>> \""
                  << gst_.players[ gst_.winner ].name
                  << "\" wins!\n\n";
    }
}

void render_log ( const GameState & gst_ )
{
    std::cout << "*** LOG of ACTIONS during the game ***\n";
    for( const auto & p : gst_.players )
    {
        std::cout << "\nDecisions taken by player \"" << p.name << "\":\n";
        for ( const auto & t : p.log_turns )
            std::cout << t.n_rolls << " dice rolls produced " << t.pts << std::endl;
    }
}
