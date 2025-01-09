#include "../Inc/MCTS.hpp"

int MCTS::RUN(Node *node, int iterations){
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
    int action = node->actions[randomMove];
    Game gameCopy = node->state;
    gameCopy.makeMove(action);
    node->actions.erase(node->actions.begin() + randomMove);
    Node *newNode = new Node(gameCopy, node, 0, action);
    node->children.push_back(newNode);
    return newNode;
}
int MCTS::SIMULATE(Node *node){

}
void MCTS::BACKPROPAGATE(Node *node, int score){
    while(node){
        node->visited++;
        node->score += score;
        node = node->Parent;
    }
}