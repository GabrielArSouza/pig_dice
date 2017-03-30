#ifndef _DICE_H_
#define _DICE_H_

#include <random>   // std::default_random_engine, std::uniform_real_distribution.

namespace dice {

    ///  Dice face type.
    using FaceType = unsigned short;

    /// Type of seed: random, or fixed (defined by the client).
    enum seed_t { RANDOM=0, FIXED };

    // Prototypes

    /*!
     *  \brief Set the type of scheme for generating faces.
     *
     *  It is possible to define a complete (pseudo) random generation of
     *  faces OR to set a fixed seed.
     *  Setting a fixed seed mens that a sequence of calls to roll() will
     *  produce the exact same sequence of faces.
     *
     *  \param which_method_ Indicates whether we want a random of a fixed seed.
     *  \param seed_value_ The seed value we wish to use.
     */
    void set_seed( seed_t which_method_=RANDOM, std::random_device::result_type seed_val_=0 );

    /*!
     *  \brief Rolls n-faced dice.
     *  This function simulares a roll of n-faced dice.
     *  You might simulate a regular 6-sided dice  or a coin toss.
     *
     *
     *  \param n_faces_ Number of dice faces (a integer >0). Default is a 6-sided dice.
     *  \param seed_ Seed used to generate the random event. If nothing is informed, we assume (pseudo) random generation.
     *
     *  \note Providing the same `seed` means we got the same random numbers.
     *
     *  \return The value of one of the n faces, i.e. a value in {0, 1, 2, ..., n-1}.
     */
    FaceType roll( FaceType n_faces_=6 );
}

#endif
