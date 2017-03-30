/*!
 *   This module implements a random number generator, which simulates a n-faced dice.
 *
 *   It is possible to generate (pseudo) random numbers OR to generate the same
 *   sequence of faces (fixed seed).
 *   Module description goes here...
 */

#include "../include/dice.h"

namespace dice {
    /// A mersenne twister engine
    static std::mt19937 gen;

    void set_seed ( seed_t which_method_, std::random_device::result_type seed_val_ )
    {
        if ( which_method_ == RANDOM )
        {
            std::random_device rd; // Use the default random engine.
            gen.seed( rd() );      // Generate a random seed.
        }
        else
        {
            gen.seed( seed_val_ ); // Fixed seed.
        }
    }

    FaceType roll( FaceType n_faces_ )
    {
        std::uniform_int_distribution<FaceType> dis(0, n_faces_-1);

        return dis( dice::gen );
    }
}
