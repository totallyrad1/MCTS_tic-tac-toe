#pragma once
#include "Game.hpp"
#include "Node.hpp"
struct MCTS{
    int RUN();
    Node *SELECT(Node *);
    Node *EXPAND(Node *);
    int SIMULATE(Node *);
    void BACKPROPAGATE(Node *);
};