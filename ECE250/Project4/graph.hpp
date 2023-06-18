#include <vector>
#include <iostream>
using namespace std;

/*
binary search tree to store all vertices
Prims algorithm to find MST

each node in the binary search tree which is a vertex
- has a Vector which holds all edges related to that node, just insert the additional edgeinto the vector
- use Prims method, and a priority queue implemented with a heap.


deletion of a node triggers the deletion of all vertices in other nodes that contains this vertex
- use a queue


a is influencing b




when inserting a new node/edge,

after inserting a, we search for b, if b is not found, we need to new a b, and add this address to the vector of edges
*/
class Edge;
class VertexNode;
class BinaryTreeGraph;
class EdgesPQ;

class Edge
{
public:
    int a;
    int b;
    VertexNode *b_address;
    double weight;
    Edge(VertexNode *root_p, int a_p, int b_p, double weight_p, int &size);

private:
};

class VertexNode
{
    // influenced by:17569      researcher: 2629   influence weight:0.045455
public:
    int researcherNo;
    vector<Edge> edges{};
    VertexNode *left;
    VertexNode *right;

    VertexNode(int researcherNo_p);
    VertexNode *insertNewVertexOrEdge(VertexNode *baseRoot, VertexNode *root_p, int a_p, int b_p, double weight_p, int &size);
    VertexNode *insertNewVertexOrEdge_print(VertexNode *baseRoot, VertexNode *root_p, int a_p, int b_p, double weight_p, int &size);
    VertexNode *insertNew_Just_Node(VertexNode *root_p, int b_p, int &size);

    void addEdge(VertexNode *baseRoot, VertexNode *root_p, int b_p, double weight_p, int &size);
    void addEdge_print(VertexNode *baseRoot, VertexNode *root_p, int b, double weight, int &size);
    void removeEdge(int b_p);
    VertexNode *findVertex(VertexNode *root_p, int researcherNo_p);
    VertexNode *deleteVertex(VertexNode *root_p, int researcherNo_p, int &size);
    void clear(VertexNode *root_p);
    VertexNode *minValueNode(VertexNode *root_p);
    void deleteEdgesFromWholeTree(VertexNode *root_p, int researcherNo_p);
    bool findEdge(int a_p, int b_p, double weight_p);
    void inOrderPrint(VertexNode *root_p);

private:
};

class BinaryTreeGraph
{
public:
    int size;
    VertexNode *root;

    BinaryTreeGraph();
    void insertNewEdge(int a_p, int b_p, double weight_p);
    VertexNode *insertNewVertexOrEdge(int a_p, int b_p, double weight_p);
    VertexNode *insertNewVertexOrEdge_print(int a_p, int b_p, double weight_p);
    VertexNode *findVertex(int parent_p);
    void printAdjacenciesOfVertex(int parent_p);
    void deleteVertex(int researcherNo_p);
    void mst(int parent_p);
    void clear();
    void printSize();

private:
};

class EdgesPQ
{
public:
    vector<Edge> heap;
    EdgesPQ();
    bool empty();
    void Heapify(int i);
    void insert(Edge newEdge_p);
    Edge extractMax();
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void swap(int a, int b);

private:
};

class illegal_exception
{
public:
    illegal_exception();
    void check_weight(double weight) const;
    void check_ResearcherNo(int researcherNo_p) const;
};
