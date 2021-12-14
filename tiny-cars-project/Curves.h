//
// Created by husse on 1/19/2021.
//

#ifndef EX56_CURVES_H
#define EX56_CURVES_H


#include "Vector2D.h"
#include <vector>
#include <iostream>
using namespace std;

class Curves {

public:
    int srcId;
    int index = 0;
    int curveNum = 0;
    double angle;
    Vector2D* startingPoint;
    Vector2D* orientation;
    Vector2D* endingPoint;
    vector<pair<Vector2D*, double>> gates;
    vector<int> polygonsIds;
    vector <Vector2D*> AllPoints;
    vector <vector <Vector2DD>> NewCurves;
    vector<vector<pair<Vector2D*, double>>> connectionGraphWithPositions;

    Curves(vector<vector<pair<Vector2D*, double>>> connectionGraphWithPositions, int srcId, Vector2D* startingPoint){
        this->connectionGraphWithPositions = connectionGraphWithPositions;
        this->srcId = srcId;
        this->startingPoint = startingPoint;
//        this->angle = angle;
//        orientation->x = startingPoint->x + (50 * sin(angle));
//        orientation->y = startingPoint->y + (50 * cos(angle));
    }

    int minDistance(vector<int> dist, vector<bool> sptSet, int V)
    {
        int min = 100000, min_index;

        for (int v = 0; v < V; v++)
            if (sptSet[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    void printPath(vector<int> parent, int j)
    {
        if (parent[j] == - 1)
            return;
        printPath(parent, parent[j]);
//        cout << j << " ";
        cout<<"dijkstra.................."<<connectionGraphWithPositions[parent[j]][j].first->x << " x, " << connectionGraphWithPositions[parent[j]][j].first->y << " y " << endl;
        gates.push_back(connectionGraphWithPositions[parent[j]][j]);
        polygonsIds.push_back(j);
    }

    int printSolution(vector<int> dist, int V, vector<int> parent, int destination)
    {
        int src = 0;
//        cout<< "Vertex\t Distance\tPath" <<endl;
//        for (int i = 1; i < V; i++)
//        {
//            cout << src << " -> " << destination << "\t\t" << dist[destination] << "\t\t" << src << endl;
            printPath(parent, destination);
//        }
    }

    void dijkstra(vector<vector<int>> graph, int destination)
    {
        vector<int> dist;
        vector<bool> sptSet;
        vector<int> parent;

        for (int i = 0; i < graph.size(); i++)
        {
            parent.push_back(-1);
            dist.push_back(100000);
            sptSet.push_back(false);
        }

        dist[srcId] = 0;

        for (int count = 0; count < graph.size() - 1; count++)
        {
            int u = minDistance(dist, sptSet, graph.size());

            sptSet[u] = true;

            for (int v = 0; v < graph.size(); v++)
                if (!sptSet[v] && graph[u][v] &&
                    dist[u] + graph[u][v] < dist[v])
                {
                    parent[v] = u;
                    dist[v] = dist[u] + graph[u][v];
                }
        }
        printSolution(dist, graph.size(), parent, destination);
    }
};


#endif //EX56_CURVES_H
