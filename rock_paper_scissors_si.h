//
//  rock_paper_scissors_si.h
//  RockPaperScissorsSI
//
//  Created by Piotr Imbierowicz on 14.06.2014.
//  Copyright (c) 2014 Piotr Imbierowicz. All rights reserved.
//

#ifndef __RockPaperScissorsSI__rock_paper_scissors_si__
#define __RockPaperScissorsSI__rock_paper_scissors_si__

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>

class RockPaperScissorsSI {
public:


    enum gesture {
        Rock,
        Paper,
        Scissors
    };

    class Gesture {

    private:
        gesture gest;
    public:
        Gesture(gesture g): gest(g) {}
        gesture win() {
            if(gest == Paper) return Scissors;
            if(gest == Scissors) return Rock;
            else return Paper;
        }
        gesture lose() {
            if(gest == Paper) return Rock;
            if(gest == Scissors) return Paper;
            else return Scissors;
        }
        gesture draw() {
            return gest;
        }
        gesture get() {
            return gest;
        }
        std::string to_string() {
            if(gest == Rock) return "Rock";
            if(gest == Paper) return "Paper";
            else return "Scissors";
        }
        std::string to_code() {
            if(gest == Rock) return "1";
            if(gest == Paper) return "2";
            else return "3";
        }
    };

    class Play {
        Gesture *player;
        Gesture *computer;
    public:
        Play(Gesture *p, Gesture *c): player(p), computer(c) {}
        Gesture* get_player() {
            return player;
        }
        Gesture* get_computer() {
            return computer;
        }
        int get_result() {
            if(get_player()->win() == computer->get()) {
                return -1;
            }
            if(get_player()->lose() == computer->get()) {
                return 1;
            }
            return 0;
        }
        std::string to_string() {
            char buff[256];
            sprintf(buff, "(P: %s, C: %s), wynik: %d", player->to_string().c_str(), computer->to_string().c_str(), get_result());

            return std::string(buff);
        }

    };

    class PatternStrategy {
        static const int strategy_id = 2;
        std::vector<Play> plays;
        float probability;
        gesture gest;
    public:
        PatternStrategy(std::vector<Play> plays): plays(plays) {}
        gesture get_selection();
        float get_probability();
        std::string plays_to_string();
        void find_patterns();
    };

    class DeffensiveStrategy {

        static int strategy_id;
        std::vector<Play> plays;
        int rock_points;
        int paper_points;
        int scissors_points;

        void apply_frequency_points();
        void apply_doublet_points();

    public:

        DeffensiveStrategy(std::vector<Play> plays): plays(plays) {
            rock_points = paper_points = scissors_points = 0;
            apply_frequency_points();
            apply_doublet_points();
        }

        static int loses_count;
        gesture get_selection();
        bool change_strategy();

    };

    std::vector<Play> plays;
    std::vector<gesture> frequently_used_gestures;
    std::vector<int> frequently_used_gestures_count;
    int doublets;
public:
    gesture get_selection();
    Gesture get_selection_object();
    void add_selection(gesture, gesture);
    void update_usage_stats();
    void update_doublets_stats();
    RockPaperScissorsSI();
    std::string to_string();
    std::string last_game_to_string();
    int get_result();
    void find_patterns();
};

#endif /* defined(__RockPaperScissorsSI__rock_paper_scissors_si__) */
