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
        int currAction;
        int requiredAction;
        Node(){
            Parent = NULL;
        }
        Node(Game state, Node* parent, int root, int action){
            this->state = state;
            this->score = 0;
            this->visited = 0;
            this->root = root;
            this->Parent = parent;
            this->actions = state.generatePossibleMoves();
            this->requiredAction = this->actions.size();
            this->currAction = action;
        }
        float UCB1();
};