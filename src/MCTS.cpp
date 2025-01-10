#include "../Inc/MCTS.hpp"
#include <float.h>
#include <random>

int MCTS::RUN(Node *node, int iterations){
    Node *root = node;
    while(iterations > 0){
        Node * selectedNode = SELECT(node);
        Node * expandedNode = selectedNode;
        if(selectedNode->actions.size())
            expandedNode = EXPAND(selectedNode); 
        float score = SIMULATE(expandedNode);
        BACKPROPAGATE(expandedNode, score);
        iterations--;
    }
    float maxVisits = -1;
    Node *result = NULL;
    for(size_t i = 0; i < root->children.size(); i++){
        if(root->children[i]->visited > maxVisits){
            maxVisits = root->children[i]->visited;
            result = root->children[i];
        }
    }
    // cout << "BESTMOVE " << result->currAction << endl;
    // printTree(root, 0); 
    // sleep(100);
    return result->currAction;
}

void MCTS::printIndentation(int level) {
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
}

void MCTS::printTree(Node* node, int level) {
    if (!node) return;

    printIndentation(level);
    cout << "Action: " << node->currAction
         << ", Score: " << node->score
         << ", Visits: " << node->visited
         << ", UCB1: " << (!node->root ? node->UCB1() : 0)
         << ", Player: " << (node->state.currentPlayer == 1 ? "AI" : "Opponent")
         << ", MovesLeft: " << node->actions.size()
         << endl;

    for (Node* child : node->children) {
        printTree(child, level + 1);
    }
}

Node *MCTS::SELECT(Node *node){
    if(!node->actions.empty() || (node->state.gameEnded() != -1) || (node->requiredAction == 0))
        return node;
    for(size_t i = 0; i < node->children.size(); i++){
        if(!node->children[i]->actions.empty())
            return SELECT(node->children[i]);
    }
    float bestUCB = (node->state.currentPlayer == 1) ? -FLT_MAX : FLT_MAX;;
    Node *result = NULL;
    for(size_t i = 0; i < node->children.size(); i++){
        Node*Children = node->children[i];
        float UCBvalue = Children->UCB1();
        int player = node->state.currentPlayer;
        if((player && UCBvalue > bestUCB) || (!player && UCBvalue < bestUCB)){
            bestUCB = UCBvalue;
            result = Children;
        }
    }
    return SELECT(result);
}

Node *MCTS::EXPAND(Node *node){
    int randomMove = rand() % node->actions.size();
    int action = node->actions[randomMove];
    swap(node->actions[randomMove], node->actions[node->actions.size() - 1]);
    node->actions.pop_back();
    Game gameCopy = node->state;
    if(gameCopy.makeMove(action))
        gameCopy.changePlayer();
    Node *newNode = new Node(gameCopy, node, 0, action);
    node->children.push_back(newNode);
    return newNode;
}

float MCTS::SIMULATE(Node *node){
    Game gameCopy = node->state;
    while(gameCopy.gameEnded() == -1){
        auto actions = gameCopy.generatePossibleMoves();
        int randomMove = rand() % actions.size();
        gameCopy.makeMove(actions[randomMove]);
        gameCopy.changePlayer();
    }
    int winner = gameCopy.gameEnded();
    return (winner == 1) ? 1.0F : 0.0F;
}
void MCTS::BACKPROPAGATE(Node *node, int score){
    while(node){
        node->visited++;
        node->score += score;
        node = node->Parent;
    }
}