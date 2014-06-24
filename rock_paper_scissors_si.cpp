//
//  rock_paper_scissors_si.cpp
//  RockPaperScissorsSI
//
//  Created by Piotr Imbierowicz on 14.06.2014.
//  Copyright (c) 2014 Piotr Imbierowicz. All rights reserved.
//

#include "rock_paper_scissors_si.h"

int RockPaperScissorsSI::DeffensiveStrategy::loses_count = 0;

RockPaperScissorsSI::RockPaperScissorsSI() {
    frequently_used_gestures = *new std::vector<gesture>(3);
    frequently_used_gestures_count = *new std::vector<int>(3);
    frequently_used_gestures_count[0] = frequently_used_gestures_count[1] = frequently_used_gestures_count[2] = 0;
    doublets = 0;
}

void RockPaperScissorsSI::add_selection(gesture player, gesture computer) {
    Play *p = new Play(new Gesture(player), new Gesture(computer));
    plays.push_back(*p);
    update_usage_stats();
    update_doublets_stats();
}

void RockPaperScissorsSI::update_usage_stats() {
    int rock_count = 0, paper_count = 0, scissors_count = 0;
    for(int i = 0; i<plays.size(); i++ ) {
        switch (plays[i].get_player()->get()) {
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
            frequently_used_gestures[0] = Rock;
            if(paper_count > scissors_count) {
                frequently_used_gestures[1] = Paper;
                frequently_used_gestures[2] = Scissors;
            } else {
                frequently_used_gestures[1] = Scissors;
                frequently_used_gestures[2] = Paper;
            }
        } else {
            frequently_used_gestures[0] = Scissors;
            frequently_used_gestures[1] = Rock;
            frequently_used_gestures[2] = Paper;
        }
    } else {
        if(paper_count > scissors_count) {
            frequently_used_gestures[0] = Paper;
            if(rock_count > scissors_count) {
                frequently_used_gestures[1] = Rock;
                frequently_used_gestures[2] = Scissors;
            } else {
                frequently_used_gestures[1] = Scissors;
                frequently_used_gestures[2] = Rock;
            }
        } else {
            frequently_used_gestures[0] = Scissors;
            frequently_used_gestures[1] = Paper;
            frequently_used_gestures[2] = Rock;
        }
    }
    if(frequently_used_gestures[0] == Paper) frequently_used_gestures_count[0] = paper_count;
    if(frequently_used_gestures[1] == Paper) frequently_used_gestures_count[1] = paper_count;
    if(frequently_used_gestures[2] == Paper) frequently_used_gestures_count[2] = paper_count;
    if(frequently_used_gestures[0] == Rock) frequently_used_gestures_count[0] = rock_count;
    if(frequently_used_gestures[1] == Rock) frequently_used_gestures_count[1] = rock_count;
    if(frequently_used_gestures[2] == Rock) frequently_used_gestures_count[2] = rock_count;
    if(frequently_used_gestures[0] == Scissors) frequently_used_gestures_count[0] = scissors_count;
    if(frequently_used_gestures[1] == Scissors) frequently_used_gestures_count[1] = scissors_count;
    if(frequently_used_gestures[2] == Scissors) frequently_used_gestures_count[2] = scissors_count;
}

void RockPaperScissorsSI::update_doublets_stats() {
    doublets = 0;
    for(int i = 0; i<plays.size()-1; i++ ) {
        if(plays[i].get_player()->get() == plays[i+1].get_player()->get()) doublets++;
    }
}

RockPaperScissorsSI::Gesture RockPaperScissorsSI::get_selection_object() {
    return *new Gesture(get_selection());
}


void RockPaperScissorsSI::find_patterns() {
}

RockPaperScissorsSI::gesture RockPaperScissorsSI::get_selection() {
    DeffensiveStrategy ds = *new DeffensiveStrategy(plays);
    PatternStrategy ps = *new PatternStrategy(plays);
    Gesture pg = ps.get_selection();

    if(ps.get_probability() == 1.0) {
        return pg.win();
    } else {
        Gesture g = *new Gesture(ds.get_selection());
        return g.win();
    }

//    if(!ds.change_strategy()) {
//        Gesture g = *new Gesture(ds.get_selection());
//        return g.win();
//    } else {
//        Gesture g = *new Gesture(ds.get_selection());
//        return g.win();
//    }
}

std::string RockPaperScissorsSI::to_string() {
    std::string output = "";
    char buff[256];
    output += "Przebieg gry: \n";
    for(int i = 0; i<plays.size(); i++) {
        output += plays[i].to_string();
        output += "\n";
    }
    sprintf(buff, "Liczba dubletów: %d \n", doublets);
    output += std::string(buff);
    Gesture g1 = *new Gesture(frequently_used_gestures[0]);
    Gesture g2 = *new Gesture(frequently_used_gestures[1]);
    Gesture g3 = *new Gesture(frequently_used_gestures[2]);
    sprintf(buff, "Statystyki rzutów: %s: %d, %s: %d, %s: %d \n", g1.to_string().c_str(), frequently_used_gestures_count[0], g2.to_string().c_str(), frequently_used_gestures_count[1], g3.to_string().c_str(), frequently_used_gestures_count[2]);
    output += std::string(buff);
    sprintf(buff, "Wynik: %d \n", get_result());
    output += std::string(buff);
    return output;
}

int RockPaperScissorsSI::get_result() {
    int result = 0;
    for(int i = 0; i<plays.size(); i++) {
        result += plays[i].get_result();
    }
    return result;
}

std::string RockPaperScissorsSI::last_game_to_string() {
    return plays.back().to_string();
}
