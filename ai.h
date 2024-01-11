#ifndef AI_H
#define AI_H

#include "GameState.h"
#include "Graph.h"

int getReward(Vertex<GameState>* start, int player){
    if (start->neighbors.size() == 0){
        int currPlayer = start->data.currentTurn;
        if (start->data.hasWon(player)){
            return 100;
        }
        else if (start->data.hasWon(!player)){
            return -100;
        }
        else{
            return 50;
        }
    }
    else{
        int reward = getReward(start->neighbors[0]->location, player);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player);
            if (start->data.currentTurn == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else{
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }
}

Vec findBestMove(GameState game){
    Graph<GameState> stateSpace;
    Vertex<GameState>* start = new Vertex<GameState>(game);

    stateSpace.addVertex(start);

    Queue<Vertex<GameState>*> frontier;
    frontier.enqueue(start);

    const int MaxExpansions = 10000;
    int expansions;

    while (!frontier.isEmpty() && expansions < MaxExpansions){
        Vertex<GameState>* curr = frontier.dequeue();
        if (!curr->data.done){
            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (curr->data.grid[i][j] == -1) {
                        GameState next = curr->data;
                        next.play(i, j);
                        Vertex<GameState>* successor = new Vertex<GameState>(next);
                        stateSpace.addVertex(successor);
                        stateSpace.addDirectedEdge(curr, successor);
                        if (!successor->data.done){
                            frontier.enqueue(successor);
                        }
                    }
                }
            }
        }
        expansions++;
    }

    // for every successor of start, call getReward(successor, player1)

    ArrayList<Neighbor<GameState>*> neighbors = start->neighbors;

    int max = -100;
    Vertex<GameState>* best = start;

    int draws = 0;

    for (int i = 0; i < neighbors.size(); i++) {
        Vertex<GameState>* current = neighbors[i]->location;
        int reward = getReward(current, game.currentTurn);

        if (reward > max) {
            max = reward;
            best = current;
        }

        if (reward == 50) {
            draws++;
        }
    }
    
    // choose random spot if couldn't get a useful reward
    if (draws == neighbors.size()) {
        srand(time(nullptr));
        Vec randomMove;

        do {
            randomMove = Vec(rand() % game.size, rand() % game.size);
        } while (game.grid[randomMove.x][randomMove.y] != -1);

        return randomMove;
    }
    else {
        return best->data.lastMove;
    }
}

Vec validMove(GameState game){
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(0,0);
}

#endif