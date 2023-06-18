#include <iostream>
#include <string>
#include <fstream>
#include "graph.hpp"
using namespace std;

int main()
{

    BinaryTreeGraph graph1;

    string addWord;
    illegal_exception ie;

    while ((!std::cin.eof()))
    {
        if (cin.eof())
        {
            return 0;
        }

        string userInput2;
        cin >> userInput2;

        try
        {

            if (userInput2 == "load")
            {
                ifstream fin("paperCollabWeighted.txt");
                while (fin)
                {
                    int a, b;
                    double w;
                    fin >> a;
                    fin >> b;
                    fin >> w;
                    ie.check_ResearcherNo(a);
                    ie.check_ResearcherNo(b);
                    ie.check_weight(w);
                    graph1.insertNewVertexOrEdge(a, b, w);
                }
                cout << "success" << endl;
            }
            else if (userInput2 == "i")
            {
                int a, b;
                double w;
                cin >> a;
                cin >> b;
                cin >> w;
                ie.check_ResearcherNo(a);
                ie.check_ResearcherNo(b);
                ie.check_weight(w);
                graph1.insertNewVertexOrEdge_print(a, b, w);

                if (graph1.root == nullptr)
                {
                    cout << "nullptr";
                }
                else
                {
                    cout << graph1.root->researcherNo << endl;
                }

                graph1.root->inOrderPrint(graph1.root);
            }

            else if (userInput2 == "pr")
            {
                graph1.root->inOrderPrint(graph1.root);
            }

            else if (userInput2 == "p")
            {
                int a;
                cin >> a;
                ie.check_ResearcherNo(a);
                graph1.printAdjacenciesOfVertex(a);
            }
            else if (userInput2 == "d")
            {
                int a;
                cin >> a;
                ie.check_ResearcherNo(a);
                if (graph1.findVertex(a))
                {
                    graph1.deleteVertex(a);
                    cout<<"success\n";
                }else{
                    cout<<"failure\n";
                }
            }
            else if (userInput2 == "mst")
            {
                int a;
                cin >> a;
                ie.check_ResearcherNo(a);
                graph1.mst(a);
            }
            else if (userInput2 == "size")
            {
                graph1.printSize();
            }
            else if (userInput2 == "clear")
            {
                graph1.clear();
            }
            else if (userInput2 == "exit")
            {
                graph1.clear();
                return 0;
            }
        }
        catch (illegal_exception e)
        {
            cout << "illegal argument\n";
        }

        if (cin.eof())
        {
            return 0;
        }
    }

    return 0;
}
