#include "artificialintelligence.h"
#include <cstdlib>
#include <string.h>

ArtificialIntelligence::ArtificialIntelligence()
{
    rps_si = new RockPaperScissorsSI();
}

int ArtificialIntelligence::play(int sign)
{
    RockPaperScissorsSI::Gesture g = *new RockPaperScissorsSI::Gesture(rps_si->get_selection());
    switch (sign) {
        case 1:
            rps_si->add_selection(RockPaperScissorsSI::Rock, g.get());
            break;
        case 2:
            rps_si->add_selection(RockPaperScissorsSI::Paper, g.get());
            break;
        case 3:
            rps_si->add_selection(RockPaperScissorsSI::Scissors, g.get());
            break;
        default:
            break;
    }
    return atoi( g.to_code().c_str() );
}
