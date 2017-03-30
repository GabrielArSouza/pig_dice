/*!
 *
 * Main program, which should contain the main game loop.
 *
 * \author
 * \date
 */

#include "../include/pig_dice_game.h"

int main( void )
{
    GameState state;

    initialize_game( state );

    // The Game Loop.
    while( not game_over( state ) )
    {
        process_events( state );
        update( state );
        render( state );
    }

    render_log( state );

    return EXIT_SUCCESS;
}
