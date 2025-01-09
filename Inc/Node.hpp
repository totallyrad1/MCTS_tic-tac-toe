#pragma once
#include "Game.hpp"
struct Node{
    public:
        Node *Parent;
        Game state;
        vector<int> actions;
        vector<Node *> children;
        int root;
        float score;
        int visited;
        Node(){
            Parent = NULL;
        }
        Node(Game state, Node* parent, int root){
            this->state = state;
            this->score = 0;
            this->visited = 0;
            this->root = root;
            this->Parent = parent;
            this->actions = state.generatePossibleMoves();
        }
        float UCB1();
};