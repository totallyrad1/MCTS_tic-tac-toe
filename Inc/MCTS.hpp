#pragma once
#include "Game.hpp"
#include "Node.hpp"
struct MCTS{
    int RUN(Node *, int iterations);
    Node *SELECT(Node *);
    Node *EXPAND(Node *);
    float SIMULATE(Node *);
    void BACKPROPAGATE(Node *, int score);
    void printTree(Node* node, int level = 0);
    void printIndentation(int level);
};