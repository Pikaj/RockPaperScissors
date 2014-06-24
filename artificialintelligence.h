#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include <iostream>
#include "rock_paper_scissors_si.h"

class ArtificialIntelligence
{
public:
    ArtificialIntelligence();
    RockPaperScissorsSI *rps_si;
    int play(int sign);
};

#endif // ARTIFICIALINTELLIGENCE_H
