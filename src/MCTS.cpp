#include "../Inc/MCTS.hpp"

int MCTS::RUN(Node *node){
    srand(time(NULL));
    // while true
        // select node
        // expand from node
        // simulate
        // backpropagate
}
Node *MCTS::SELECT(Node *node){
    if(!node)
        return NULL;
    for(int i = 0; node->children.size(); i++){
        if(!node->children[i]->actions.empty())
            return node->children[i];
    }
    float biggestUCB = -1;
    Node *result = NULL;
    for(int i = 0; node->children.size(); i++){
        if(node->children[i]->UCB1() > biggestUCB){
            biggestUCB = node->children[i]->UCB1();
            result = node->children[i];
        }
    }
    return result;
}

Node *MCTS::EXPAND(Node *node){
    if(!node)
        return NULL;
    int randomMove = rand() % node->actions.size();
    Game gameCopy = node->state;
    gameCopy.makeMove(randomMove);
    Node *newNode = new Node(gameCopy, node, 0);
    node->children.push_back(newNode);
    return newNode;
}
int MCTS::SIMULATE(Node *node){

}
void MCTS::BACKPROPAGATE(Node *node){
    while(node){
        Node *parent = node->Parent;
        if(!parent)
            return ;
        parent->visited++;
        parent->score = node->score;
        node = parent;
    }
}