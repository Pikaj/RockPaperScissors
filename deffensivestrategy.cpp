//
//  DeffensiveStrategy.cpp
//  RockPaperScissorsSI
//
//  Created by Piotr Imbierowicz on 14.06.2014.
//  Copyright (c) 2014 Piotr Imbierowicz. All rights reserved.
//

#include "rock_paper_scissors_si.h"
#include <vector>

void RockPaperScissorsSI::DeffensiveStrategy::apply_frequency_points() {
    int scissors_count = 0, rock_count = 0, paper_count = 0;
    for(int i = plays.size(); i>0 && i>plays.size()-5; i--) {
        switch(plays[i-1].get_player()->get()) {
            case Scissors:
                scissors_count++;
                break;
            case Rock:
                rock_count++;
                break;
            case Paper:
                paper_count++;
                break;
            default:
                break;
        }
    }
    if(rock_count > paper_count) {
        if(rock_count > scissors_count) {
            rock_points+=2;
            if(paper_count > scissors_count) {
                paper_points+=1;
            } else {
                scissors_points+=1;
            }
        } else {
            scissors_points+=2;
            rock_points+=1;
        }
    } else {
        if(paper_count > scissors_count) {
            paper_points+=2;
            if(rock_count > scissors_count) {
                rock_points+=1;
            } else {
                scissors_points+=1;
            }
        } else {
            scissors_points+=2;
            paper_points+=1;
        }
    }
}

void RockPaperScissorsSI::DeffensiveStrategy::apply_doublet_points() {
    if(plays.empty()) return;
    int doublets = 0;
    int doublet_factor;
    for(int i = plays.size()-2; i>0 && i>plays.size()-5; i--) {
        if(plays[i].get_player()->get() == plays[i+1].get_player()->get()) doublets++;
    }
    if(doublets > 2) {
        doublet_factor = 3;
    } else {
        doublet_factor = 1;
    }
    switch (plays.back().get_player()->get()) {
        case Rock:
            rock_points+=doublet_factor;
            break;
        case Scissors:
            scissors_points+=doublet_factor;
            break;
        case Paper:
            paper_points+=doublet_factor;
            break;
        default:
            break;
    }
}

RockPaperScissorsSI::gesture RockPaperScissorsSI::DeffensiveStrategy::get_selection() {
    //printf("Rock: %d, Paper: %d, Scissors: %d \n", rock_points, paper_points, scissors_points);
    if(rock_points == paper_points == scissors_points) {
        return Rock; // change to random
    }

    if(rock_points >= paper_points && rock_points >= scissors_points) {
        return Rock;
    } else if(paper_points >= rock_points && paper_points >= scissors_points) {
        return Paper;
    }
    return Scissors;
}

bool RockPaperScissorsSI::DeffensiveStrategy::change_strategy() {
    if(RockPaperScissorsSI::DeffensiveStrategy::loses_count >= 3) {
        RockPaperScissorsSI::DeffensiveStrategy::loses_count = 0;
        return true;
    }
    if(plays.size() > 0 && plays.back().get_result() != 1) {
        RockPaperScissorsSI::DeffensiveStrategy::loses_count++;
    } else {
        RockPaperScissorsSI::DeffensiveStrategy::loses_count = 0;
    }
    return false;
}
