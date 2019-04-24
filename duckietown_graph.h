/*

    Data structure for a connected, directed graph to be used as the map of the Duckietown city.
    Each node contains the ID of an April Tag, which is the one opposite to and in front of the tile in which the robot is located.
    Edges are roads between intersections in the city.
    Each edge contains:
        -Weight: number of tiles in-between two positions (one for the intersection which must be traveled, one for the arrival tile which faces a new April Tag, plus those in-between).
        -Action: numerical representation of the action needed to take at the intersection in order to traverse the road corresponding to the current edge. These are:
            .T_LEFT: Turn left.
            .T_RIGHT: Turn right.
            .T_FWD: Go forward.
            .NO_ACTION: Unrecognized action (probably a bug while creating the graph).

*/

//Note: this code hasn't been tested yet

#ifndef DUCKIEGRAPH_H
#define DUCKIEGRAPH_H

#define T_LEFT 0
#define T_RIGHT 1
#define T_FWD 2
#define NO_ACTION -1

#include <tuple>
#include "doubly_linked_list.h"
#include "list_set.h"

class duckieGraphNode;

class duckieGraphEdge {
    private:
        int action;
        int weight;
        duckieGraphNode *node;
    public:
        duckieGraphEdge();
        duckieGraphEdge(const duckieGraphEdge&);
        duckieGraphEdge(int, int, duckieGraphNode*);
        ~duckieGraphEdge(){};
        void setAction(int);
        void setWeight(int);
        void setNode(duckieGraphNode*);
        int getAction();
        int getWeight();
        duckieGraphNode* getNode();
};

duckieGraphEdge::duckieGraphEdge() {
    this->action = NO_ACTION;
    this->weight = -1;
    this->node = NULL;
}

duckieGraphEdge::duckieGraphEdge(const duckieGraphEdge &dge) {
    this->setAction(dge.action);
    this->setWeight(dge.weight);
    this->node = dge.node;
}

duckieGraphEdge::duckieGraphEdge(int action, int weight, duckiegraphNode *node) {
    this->setAction(action);
    this->setWeight(weight);
    this->node = node;
}

void duckieGraphEdge::setAction(int action) {
    if(action == T_LEFT || action == T_RIGHT || action == T_FWD) {
        this->action = action;
    } else {
        this->action = NO_ACTION;
    }
}

void duckieGraphEdge::setWeight(int weight) {
    if(weight >= 0) {
        this->weight = weight;
    } else {
        this->weight = -1;
    }
}

void duckieGraphEdge::setNode(duckieGraphNode *node) {
    this->node = node;
}

int duckieGraphEdge::getAction() {
    return this->action;
}

int duckieGraphEdge::getWeight() {
    return this->weight;
}

duckieGraphNode* duckieGraphEdge::getNode() {
    return this->node;
}

class duckieGraphNode {
    private:
        int id;
        DLinkedList<duckieGraphEdge* > *adjacent;
    public:
        duckieGraphNode();
        duckieGraphNode(const duckieGraphNode&);
        duckieGraphNode(int);
        duckieGraphNode(int, DLinkedList<duckieGraphEdge* >*);
        ~duckieGraphNode();
        void setId(int);
        void setAdjacent(DLinkedList<duckieGraphEdge* >*);
        int getId();
        DLinkedList<duckieGraphEdge* >* getAdjacent();
        void addEdge(int, int, duckieGraphNode*);
};

duckieGraphNode::duckieGraphNode() {
    this->id = -1;
    this->adjacent = new DLinkedList<duckieGraphEdge* >();
}

duckieGraphNode::duckieGraphNode(const duckieGraphNode &dgn) {
    this->id = dgn;
    this->adjacent = new DLinkedList<duckieGraphEdge* >();
}

duckieGraphNode::duckieGraphNode(int id) {
    this->id = id;
    this->adjacent = new DLinkedList<duckieGraphEdge* >();
}

duckieGraphNode::duckieGraphNode(int id, DLinkedList<duckieGraphEdge* > *lst) {
    this->id = id;
    this->adjacent = lst;
}

duckieGraphNode::~duckieGraphNode() {
    DLL_Iterator<duckieGraphEdge* > it(this->adjacent);
    duckieGraphEdge *edge;
    while(it.hasNext()) {
        edge = it.getNext();
        delete edge;
    }
    delete this->adjacent;
}

void duckieGraphNode::setId(int id) {
    this->id = id;
}

void duckieGraphNode::setAdjacent(DLinkedList<duckieGraphEdge *> *lst) {
    if(this->adjacent != NULL) {
        DLL_Iterator<duckieGraphEdge* > it(this->adjacent);
        duckieGraphEdge *edge;
        while(it.hasNext()) {
            edge = it.getNext();
            delete edge;
        }
        delete this->adjacent;
    }
    this->adjacent = lst;
}

int duckieGraphNode::getId() {
    return this->id;
}

DLinkedList<duckieGraphEdge* >* duckieGraphNode::getAdjacent() {
    return this->adjacent;
}

void duckieGraphNode::addEdge(int action, int weight, duckieGraphNode *node) {
    if(node == NULL) {
        return;
    }
    duckieGraphEdge *edge = new duckieGraphEdge(action, weight, node);
    if(this->adjacent == NULL) {
        this->adjacent = new DLinkedList<duckieGraphEdge* >();
    }
    this->adjacent->prepend(edge);
}

class duckieGraph {
    private:
        listSet<duckieGraphNode* > *nodeSet;
    public:
        duckieGraph();
        duckieGraph(listSet<duckieGraphNode* >*);
        ~duckieGraph();
        void addNode(int);
        duckieGraphNode* getNode(int);
        void addEdge(int, int, int, int);
        void addEdge(duckieGraphNode*, duckieGraphNode*, int, int);
        DLinkedList<duckieGraphEdge* >* getAdjacent(int);
};

duckieGraph::duckieGraph() {
    this->nodeSet = new listSet<duckieGraphNode* >();
}

duckieGraph::duckieGraph(listSet<duckieGraphNode* > *ns) {
    this->nodeSet = ns;
}

duckieGraph::~duckieGraph() {
    DLL_Iterator<duckieGraphNode* > it(this->nodeSet);
    duckieGraphNode *nd;
    while(it->hasNext()) {
        nd = it->getNext();
        delete nd;
    }
    delete this->nodeSet;
}

void duckieGraph::addNode(int id) {
    duckieGraphNode *nd = new duckieGraphNode(id);
    if(this->nodeSet == NULL) {
        this->nodeSet = new listSet<duckieGraphNode* >();
    }
    this->nodeSet->insrt(nd);
}

duckieGraphNode* duckieGraph::getNode(int id) {
    DLL_Iterator<duckieGraphNode* > it(this->nodeSet);
    duckieGraphNode *nd;
    while(it->hasNext()) {
        nd = it->getNext();
        if(nd->getId() == id) {
            return nd;
        }
    }
    return NULL;
}

void duckieGraph::addEdge(int id1, int id2, int action, int weight) {
    duckieGraphNode *nd1 = this->getNode(id1);
    if(nd1 == NULL) {
        return;
    }
    duckieGraphNode *nd2;
    if(id1 == id2) {
        nd2 = nd1;
    }
    else {
        nd2 = this->getNode(id2);
        if(nd2 == NULL) {
            return;
        }
    }
    nd1->addEdge(action, weight, nd2);
}

void duckieGraph::addEdge(duckieGraphNode *nd1, duckieGraphNode *nd2, int action, int weight) {
    if(nd1 == NULL || nd2 == NULL) {
        return;
    }
    nd1->addEdge(action, weight, nd2);
}

#endif // DUCKIEGRAPH_H
