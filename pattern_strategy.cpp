//
//  pattern_strategy.cpp
//  RockPaperScissorsSI
//
//  Created by Piotr Imbierowicz on 22.06.2014.
//  Copyright (c) 2014 Piotr Imbierowicz. All rights reserved.
//

#include "rock_paper_scissors_si.h"
#include <cstdlib>
#include <string.h>

std::string reverse(std::string s) {
    std::string output = "";
    for(int i = s.length()-1; i>=0; i--) {
        output += s[i];
    }
    return output;
}

RockPaperScissorsSI::gesture RockPaperScissorsSI::PatternStrategy::get_selection() {
    find_patterns();
    RockPaperScissorsSI::Gesture *g = new RockPaperScissorsSI::Gesture(gest);
//    printf("Gest: %s, Prawdopodobieństwo: %f \n", g->to_string().c_str(), probability);
    if(gest != NULL)
        return gest;
    else
        return RockPaperScissorsSI::Rock;
}

std::string RockPaperScissorsSI::PatternStrategy::plays_to_string() {
    std::string output = "";
    for(int i = 0; i < plays.size(); i++) {
        output += plays[i].get_player()->to_code();
    }
    return output;
}

void RockPaperScissorsSI::PatternStrategy::find_patterns() {
    std::vector<int> *patterns = new std::vector<int>(plays.size());
    std::string code = reverse(plays_to_string());

    int guesses_count = 0;
    int guesses_summary = 0;
    std::vector<int> *results = new std::vector<int>(3);
    results->at(0) = results->at(1) = results->at(2) = 0;

    for(int i = 1; i < code.length(); i++) {
        int j = i;
        while(code.substr(j).find(code.substr(0, i)) != -1) {
//            int k = code.substr(j).find(code.substr(0, i))
            j += i;
            patterns->at(i) = patterns->at(i)+1;
        }
    }

//    printf("reversed: %s\n", code.c_str());
//
//    for(int i = 0; i<patterns->size(); i++) {
//        printf("%d ", patterns->at(i));
//    }

    if(code.length() > 3) {
        for(int i = 0; i<patterns->size(); i++) {
            if(patterns->at(i) > 0) {
                std::string code_to_find = code.substr(i);
//                printf("\n\ncode to find: %s", code_to_find.c_str());
//                printf("\n pattern at(%d)", i);
                std::string pattern = code.substr(0, i).c_str();
                int guess_position = code_to_find.find(pattern);
                std::string guess = code_to_find.substr(guess_position, i);
//                printf("\nguess position: %d", guess_position);
//                printf("\nguess: %s", guess.c_str());
                int guess_position_in_code = code.find(guess, 1);
//                printf("\nguess_position_in_code: %d", guess_position_in_code);
                if(guess_position_in_code > 0) {
                    guesses_count+=i;
                    switch(atoi(code.substr(guess_position_in_code-1,1).c_str()))
                    {
                        case 1:
                            results->at(0) = results->at(0)+i;
                            break;
                        case 2:
                            results->at(1) = results->at(1)+i;
                            break;
                        case 3:
                            results->at(2) = results->at(2)+i;
                            break;

                    }
//                    printf("\nguess character: %s", code.substr(guess_position_in_code-1,1).c_str());
                }
            }
        }
    }
    if(guesses_count > 0) {
        int max_v;
        max_v = std::max(results->at(0), results->at(1));
        max_v = std::max(max_v, results->at(2));
        if(max_v == results->at(0)) {
            this->gest = RockPaperScissorsSI::Rock;
        } else if(max_v == results->at(1)) {
            this->gest = RockPaperScissorsSI::Paper;
        } else {
            this->gest = RockPaperScissorsSI::Scissors;
        }
        this->probability = max_v;
        this->probability /= guesses_count;
    }
//    printf("\n");
}

float RockPaperScissorsSI::PatternStrategy::get_probability() {
    return probability;
}
