#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;

        Edge();
        Edge(Node* target, float cost);
    };

    struct Node {
        Node(float x, float y);
        void ConnectTo(Node* other, float cost);
        float Heuristic(Node* start, Node* end);


        glm::vec2 position;
        std::vector<Edge> connections;
        float gScore;
        float hScore;
        float fScore;
        Node* previous;

    };

    class NodeMap {
        int width;
        int height;
        float cellSize;

        Node** nodes;

    public:
        std::vector<Node*> path;

        int mapSize;

        void Initialise(std::vector <std::string> asciiMap, int cellSize);

        Node* GetNode(int x, int y);

        void Draw();

        std::vector<Node*> AStarSearch(Node* start, Node* end);

        void DrawPath();

        Node* GetClosestNode(glm::vec2 worldPos);


        ~NodeMap();

    };









}
