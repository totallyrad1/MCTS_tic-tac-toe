#pragma once
#include "Game.hpp"
struct Node{
    public:
        Game state;
        vector<int> actions;
        vector<Node *> children;
        int root;
        float score;
        int visited;

        float UCB1();
};