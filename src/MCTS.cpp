#include "../Inc/MCTS.hpp"

int MCTS::RUN(Node *node, int iterations){
    srand(time(NULL));
    Node *root = node;
    while(iterations > 0){
        Node * selectedNode = SELECT(node);
        Node * expandedNode = EXPAND(selectedNode);
        float score = SIMULATE(expandedNode);
        BACKPROPAGATE(expandedNode, score);
        iterations--;
    }
    float biggestUCB = -1;
    Node *result = NULL;
    for(size_t i = 0; i < root->children.size(); i++){
        if(root->children[i]->UCB1() > biggestUCB){
            biggestUCB = root->children[i]->UCB1();
            result = root->children[i];
        }
    }
    return result->currAction;
}
Node *MCTS::SELECT(Node *node){
    if(!node)
        return NULL;
    if(node->children.empty())
        return node;
    for(size_t i = 0; i < node->children.size(); i++){
        if(!node->children[i]->actions.empty())
            return node->children[i];
    }
    float biggestUCB = -1;
    Node *result = NULL;
    for(size_t i = 0; i < node->children.size(); i++){
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
    if(node->actions.empty())
        return node;
    int randomMove = rand() % node->actions.size();
    int action = node->actions[randomMove];
    Game gameCopy = node->state;
    if(gameCopy.makeMove(action))
        gameCopy.changePlayer();
    Node *newNode = new Node(gameCopy, node, 0, action);
    vector<int> actionsLeft;
    for(size_t i = 0; i < newNode->actions.size(); i++){
        if(newNode->actions[i] !=  action)
            actionsLeft.push_back(newNode->actions[i]);
    }
    newNode->actions = actionsLeft;
    node->children.push_back(newNode);
    return newNode;
}

float MCTS::SIMULATE(Node *node){
    Node *temp = new Node(*node);
    while(temp->state.gameEnded() == -1){
        temp = EXPAND(temp);
    }
    int winner = temp->state.gameEnded();
    if(winner == 1)
        return winner;
    return 0;
}
void MCTS::BACKPROPAGATE(Node *node, int score){
    while(node){
        node->visited++;
        node->score += score;
        node = node->Parent;
    }
}