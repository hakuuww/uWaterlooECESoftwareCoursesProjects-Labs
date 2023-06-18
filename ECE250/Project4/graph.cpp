#include "graph.hpp"
using namespace std;

BinaryTreeGraph ::BinaryTreeGraph()
{
    root = nullptr;
    size = 0;
}

void BinaryTreeGraph::printAdjacenciesOfVertex(int a_p)
{
    VertexNode *temp = this->findVertex(a_p);
    if (temp == nullptr)
    {
        cout << '\n';
    }
    else
    {
        for (auto i : temp->edges)
        {
            // access by value, the type of i is int
            cout << i.b << ' ';
        }
        cout << '\n';
    }
}

void BinaryTreeGraph::deleteVertex(int researcherNo_p)
{
    root->deleteEdgesFromWholeTree(root, researcherNo_p);
    root->deleteVertex(root, researcherNo_p, this->size);
    return;
}

void VertexNode::inOrderPrint(VertexNode *root_p)
{
    if (root_p == nullptr)
    {
        return;
    }
    root_p->left->inOrderPrint(root_p->left);
    cout << root_p->researcherNo << ' ';
    root_p->left->inOrderPrint(root_p->right);
}

/*
starting node, insert all edges into the priority queue

repeat:
    extract the max weight, pick the edge a b w with the most weight, print it
    insert all edges of b into the priority queue


*/
void BinaryTreeGraph::mst(int a_p)
{
    VertexNode *startingNode = findVertex(a_p);
    EdgesPQ priorityQueue;

    if (startingNode == nullptr)
    {
        cout << "failure\n";
        return;
    }

    int MST_size{0};
    int j{0};

    for (auto i : startingNode->edges)
    {
        priorityQueue.insert(startingNode->edges[j]);
        j++;
    }

    while (!priorityQueue.empty())
    {

        int k{0};
        VertexNode *bNode = priorityQueue.extractMax().b_address;

        for (auto i : bNode->edges)
        {
            priorityQueue.insert(bNode->edges[k]);
            k++;
        }
        MST_size++;
    }

    cout << MST_size << '\n';
}

void BinaryTreeGraph::clear()
{
    root->clear(root);
}

void BinaryTreeGraph::printSize()
{
    cout << size << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexNode::deleteEdgesFromWholeTree(VertexNode *root, int researcherNo_p)
{
    if (root == nullptr)
    {
        return;
    }

    root->removeEdge(researcherNo_p);
    root->left->deleteEdgesFromWholeTree(root->left, researcherNo_p);
    root->right->deleteEdgesFromWholeTree(root->right, researcherNo_p);
    return;
}

VertexNode *BinaryTreeGraph::findVertex(int a_p)
{
    return root->findVertex(root, a_p);
}

VertexNode::VertexNode(int researcherNo_p)
{
    researcherNo = researcherNo_p;
    left = nullptr;
    right = nullptr;
}

VertexNode *VertexNode::insertNew_Just_Node(VertexNode *root_p, int b_p, int &size)
{
    if (root_p == nullptr)
    {
        root_p = new VertexNode(b_p);
        size++;
        return root_p;
    }

    if (root_p->researcherNo == b_p)
    {
        return root_p;
    }

    if (root_p->researcherNo > b_p)
    {
         root_p->left = insertNew_Just_Node(root_p->left, b_p, size);
    }
    else if (root_p->researcherNo < b_p)
    {
         root_p->right = insertNew_Just_Node(root_p->right, b_p, size);
    }

    return root_p;
}

void VertexNode::clear(VertexNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

bool VertexNode::findEdge(int a_p, int b_p, double weight_p)
{
    for (auto i : edges)
    {
        // access by value, the type of i is int
        if ((i.a == a_p) && (i.b == b_p) && (i.weight == weight_p))
        {
            return true;
        }
    }

    return false;
}
void VertexNode::addEdge(VertexNode *baseRoot, VertexNode *root, int b, double weight, int &size)
{
    if (root->findEdge(this->researcherNo, b, weight))
    {
        return;
    }

    Edge tempEdge = Edge(baseRoot, this->researcherNo, b, weight, size);
    this->edges.push_back(tempEdge);
}

void VertexNode::addEdge_print(VertexNode *baseRoot, VertexNode *root, int b, double weight, int &size)
{
    if (root->findEdge(this->researcherNo, b, weight))
    {
        cout << "failure\n";
        return;
    }
    Edge tempEdge = Edge(baseRoot, this->researcherNo, b, weight, size);
    this->edges.push_back(tempEdge);

    cout << "success\n";
}

VertexNode *VertexNode::findVertex(VertexNode *root, int researcherNo_p)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->researcherNo == researcherNo_p)
    {
        return root;
    }

    if (root->researcherNo > researcherNo_p)
    {
        return this->findVertex(root->left, researcherNo_p);
    }

    if (root->researcherNo < researcherNo_p)
    {
        return this->findVertex(root->right, researcherNo_p);
    }

    return nullptr;
}

VertexNode *VertexNode::deleteVertex(VertexNode *root, int researcherNo_p, int &size)
{
    if (root == nullptr)
    {
        cout << "failure\n";
        return root;
    }

    if (root->researcherNo > researcherNo_p)
    {
        root->left = this->deleteVertex(root->left, researcherNo_p, size);
    }
    else if (root->researcherNo < researcherNo_p)
    {
        root->right = this->deleteVertex(root->right, researcherNo_p, size);
    }
    else if (root->researcherNo == researcherNo_p)
    {
        cout << "success\n";
        if (root->left == nullptr && root->right == nullptr)
        {
            size--;
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            size--;
            VertexNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            size--;
            VertexNode *temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            VertexNode *temp2 = minValueNode(root->right);
            root->researcherNo = temp2->researcherNo;
            root->right = deleteVertex(root->right, temp2->researcherNo, size);
        }
    }

    return root;
}

VertexNode *VertexNode::minValueNode(VertexNode *root)
{

    VertexNode *p_traverse = root;
    while ((p_traverse != nullptr) && (p_traverse->left != nullptr))
    {
        p_traverse = p_traverse->left;
    }
    return p_traverse;
}

void VertexNode::removeEdge(int b_p)
{
    int j = 0;
    for (auto i : edges)
    {
        // access by value, the type of i is int
        if (i.b == b_p)
        {
            edges.erase(edges.begin() + j);
        }
        j++;
    }
}

VertexNode *BinaryTreeGraph::insertNewVertexOrEdge(int a_p, int b_p, double weight_p)
{
    this->root = this->root->insertNewVertexOrEdge(this->root, this->root, a_p, b_p, weight_p, this->size);
    
    //this->root->insertNew_Just_Node(root, b_p, size);
    return root;
}

VertexNode *BinaryTreeGraph::insertNewVertexOrEdge_print(int a_p, int b_p, double weight_p)
{
    this->root = this->root->insertNewVertexOrEdge_print(this->root, this->root, a_p, b_p, weight_p, this->size);
    //this->root = this->root->insertNew_Just_Node(this->root, b_p, this->size);
    return this->root;
}

VertexNode *VertexNode::insertNewVertexOrEdge(VertexNode *baseRoot,VertexNode *root, int a_p, int b_p, double weight_p, int &size)
{
    if (root == nullptr)
    {
        root = new VertexNode(a_p);
        root->addEdge(baseRoot, root,  b_p, weight_p, size);
        size++;
        return root;
    }

    if (root->researcherNo == a_p)
    {
        root->addEdge(baseRoot, root, b_p, weight_p, size);
        return root;
    }

    if (root->researcherNo > a_p)
    {
        root->left = insertNewVertexOrEdge(baseRoot,root->left, a_p, b_p, weight_p, size);
    }
    else if (root->researcherNo < a_p)
    {
        root->right = insertNewVertexOrEdge(baseRoot,root->right, a_p, b_p, weight_p, size);
    }

    return root;
}

VertexNode *VertexNode::insertNewVertexOrEdge_print(VertexNode *baseRoot, VertexNode *root_p, int a_p, int b_p, double weight_p, int &size)
{
    if (root_p == nullptr)
    {
        root_p = new VertexNode(a_p);
        root_p->addEdge_print(baseRoot, root_p, b_p, weight_p, size);
        size++;
        return root_p;
    }

    if (root_p->researcherNo == a_p)
    {
        root_p->addEdge_print(baseRoot, root_p, b_p, weight_p, size);
        return root_p;
    }

    if (root_p->researcherNo > a_p)
    {
        root_p->left = insertNewVertexOrEdge_print(baseRoot,root_p->left, a_p, b_p, weight_p, size);
    }
    else if (root_p->researcherNo < a_p)
    {
        root_p->right = insertNewVertexOrEdge_print(baseRoot,root_p->right, a_p, b_p, weight_p, size);
    }

    return root_p;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Edge::Edge(VertexNode *root, int a_p, int b_p, double weight_p, int &size) : a{a_p}, b{b_p}, weight{weight_p}
{
    //cout<<root->researcherNo<<"yayayyayayayyaypopopopopopog";
    this->b_address = root->insertNew_Just_Node(root, b_p, size); //////WRONG
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EdgesPQ::EdgesPQ()
{
}

void EdgesPQ::Heapify(int i)
{
    int size = this->heap.size();
    int l = leftChild(i);
    int r = rightChild(i);
    int largest{};
    if ((l < size) && (heap[l].weight > heap[i].weight))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if ((r < size) && (heap[r].weight > heap[largest].weight))
    {
        largest = r;
    }

    if (largest != i)
    {
        this->swap(i, largest);
        Heapify(largest);
    }
}

void EdgesPQ::insert(Edge newEdge_p)
{
    int i = this->heap.size();

    this->heap.push_back(newEdge_p);

    while ((i > 0) && (heap[parent(i)].weight < newEdge_p.weight))
    {
        this->swap(i, parent(i));
        i = parent(i);
    }
}

Edge EdgesPQ::extractMax()
{
    Edge max = heap[0];
    int lastIndex = this->heap.size() - 1;

    this->swap(0, lastIndex);
    heap.pop_back();
    this->Heapify(0);
    return max;
}

void EdgesPQ::swap(int a, int b)
{
    Edge temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

int EdgesPQ::parent(int i)
{
    return (i - 1) / 2;
}
int EdgesPQ::leftChild(int i)
{
    return i * 2 + 1;
}
int EdgesPQ::rightChild(int i)
{
    return i * 2 + 2;
}

bool EdgesPQ::empty()
{
    if (heap.size() == 0)
    {
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

illegal_exception::illegal_exception()
{
}

void illegal_exception::check_ResearcherNo(int researcherNo_p) const
{
    if (researcherNo_p <= 0 || researcherNo_p > 23133)
    {
        throw illegal_exception();
    }
}

void illegal_exception::check_weight(double weight) const
{
    if (weight < 0 || weight > 1)
    {
        throw illegal_exception();
    }
}