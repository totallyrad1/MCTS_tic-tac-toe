#include "../Inc/MCTS.hpp"
#include <float.h>

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
    printTree(root, 0); 
    sleep(100);
    return result->currAction;
}

void MCTS::printIndentation(int level) {
    for (int i = 0; i < level; i++) {
        cout << "  ";  // Two spaces per level
    }
}

// Recursive function to print the MCTS tree
void MCTS::printTree(Node* node, int level) {
    if (!node) return;

    // Print the current node's details
    printIndentation(level);
    cout << "Action: " << node->currAction
         << ", Score: " << node->score
         << ", Visits: " << node->visited
         << ", UCB1: " << (!node->root ? node->UCB1() : 0)
         << ", Player: " << (node->state.currentPlayer == 1 ? "AI" : "Opponent")
         << ", MovesLeft: " << node->actions.size()
         << endl;

    // Recursively print child nodes
    for (Node* child : node->children) {
        printTree(child, level + 1);
    }
}

Node *MCTS::SELECT(Node *node){
    if(!node->actions.empty())
        return node;
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
    if(!result)
        return node;
    return SELECT(result);
}

Node *MCTS::EXPAND(Node *node){
    if(node->actions.empty())
        return node;
    int randomMove = rand() % node->actions.size();
    int action = node->actions[randomMove];
    swap(node->actions[randomMove], node->actions[node->actions.size() - 1]);
    node->actions.pop_back();
    Game gameCopy = node->state;
    if(gameCopy.makeMove(action))
        gameCopy.changePlayer();
    Node *newNode = new Node(gameCopy, node, 0, action);
    // vector<int> actionsLeft;
    // for(size_t i = 0; i < newNode->actions.size(); i++){
    //     if(newNode->actions[i] !=  action)
    //         actionsLeft.push_back(newNode->actions[i]);
    // }
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
        return 1;
    return 0;
}
void MCTS::BACKPROPAGATE(Node *node, int score){
    while(node){
        node->visited++;
        if(node->state.currentPlayer == 0)
            node->score += score;
        else
            node->score -= score;
        node = node->Parent;
    }
}