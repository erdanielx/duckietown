/*
    City graph configuration function to be called from programs using this graph
*/

//Note: this code hasn't been tested yet

#ifndef GRAPH_SETUP_H
#define GRAPH_SETUP_H

#include "duckietown_graph.h"

duckieGraph* getGraph() {
    duckieGraph *graph = new duckieGraph();
    graph->addNode(8);
    graph->addNode(13);
    graph->addNode(14);
    graph->addNode(15);
    graph->addNode(58);
    graph->addNode(59);
    graph->addNode(62);
    graph->addNode(63);
    graph->addNode(66);
    graph->addNode(67);
    graph->addEdge(8, 66, T_LEFT, 2);
    graph->addEdge(8, 59, T_RIGHT, 6);
    graph->addEdge(8, 62, T_FWD, 6);
    graph->addEdge(13, 62, T_LEFT, 6);
    graph->addEdge(13, 67, T_RIGHT, 2);
    graph->addEdge(13, 59, T_FWD, 6);
    graph->addEdge(14, 66, T_FWD, 2);
    graph->addEdge(14, 62, T_RIGHT, 6);
    graph->addEdge(14, 67, T_LEFT, 2);
    graph->addEdge(15, 59, T_LEFT, 6);
    graph->addEdge(15, 66, T_RIGHT, 2);
    graph->addEdge(15, 67, T_FWD, 2);
    graph->addEdge(58, 13, T_RIGHT, 2);
    graph->addEdge(58, 15, T_FWD, 6);
    graph->addEdge(59, 58, T_FWD, 4);
    graph->addEdge(59, 8, T_RIGHT, 2);
    graph->addEdge(62, 63, T_FWD, 4);
    graph->addEdge(62, 13, T_LEFT, 2);
    graph->addEdge(63, 14, T_FWD, 6);
    graph->addEdge(63, 8, T_LEFT, 2);
    graph->addEdge(66, 63, T_LEFT, 4);
    graph->addEdge(66, 15, T_RIGHT, 6);
    graph->addEdge(67, 14, T_LEFT, 6);
    graph->addEdge(67, 58, T_RIGHT, 4);
    return graph;
}

#endif // GRAPH_SETUP_H
