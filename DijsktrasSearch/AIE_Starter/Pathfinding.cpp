#include "Pathfinding.h"
#include <iostream>
#include "raylib.h"
#include <queue>

void AIForGames::NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	this->cellSize = cellSize;
	const char emptySquare = '0';

	// Assume all string are the same length, se we will size our map
	// according to the number of strings and the length of the first one

	height = asciiMap.size();
	width = asciiMap[0].size();

	mapSize = width * height;
	nodes = new Node * [mapSize];

	// Loop over our strings, creating node entries as we go
	for (int y = 0; y < height; y++) {
		std::string& line = asciiMap[y];
		// Report to the user if we have a mismatched string length
		if (line.size() != width) {
			std::cout << "Mismatched line # " << y << " in the ASCII map( " << line.size() << " instead of " << width << std::endl;
		}

		for (int x = 0; x < width; x++) {
			/* Get the x-th character, or return an empty node
			if the string isnt long enough*/
			char tile = x < line.size() ? line[x] : emptySquare;

			// Create a node for anything but a '0' character
			nodes[x + width * y] = tile == emptySquare ? nullptr : new Node((x + 0.5f) * cellSize, (y + 0.5f) * cellSize);
		}

	}

	/* Now loop over the nodes, creating connections between each node and its neighbour
	to its west and North on the grid, this will link every node*/
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Node* node = GetNode(x, y);
			if (node) {
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest) {
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeNorth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeNorth) {
					node->ConnectTo(nodeNorth, 1);
					nodeNorth->ConnectTo(node, 1);
				}
			}
		}
	}

	path = DijkstrasSearch(GetNode(1, 1), GetNode(10, 2));

}



AIForGames::Node* AIForGames::NodeMap::GetNode(int x, int y)
{
	Node* node = x + width * y < mapSize ? nodes[x + width * y] : nullptr;
	return node;
}




void AIForGames::NodeMap::Draw()
{
	// Purple colour for the walls
	Color cellColor;
	cellColor.r = 51;
	cellColor.g = 51;
	cellColor.b = 51;
	cellColor.a = 255;

	// differing greys for the boxes
	Color firstBoxColor;
	firstBoxColor.r = 73;
	firstBoxColor.g = 28;
	firstBoxColor.b = 208;
	firstBoxColor.a = 255;

	Color secondBoxColor;
	secondBoxColor.r = 192;
	secondBoxColor.g = 192;
	secondBoxColor.b = 192;
	secondBoxColor.a = 255;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Node* node = GetNode(x, y);
			if (node == nullptr) {
				DrawRectangle((int)(x * cellSize), (int)(y * cellSize), (int)(cellSize - 1), (int)(cellSize - 1), cellColor);
			}
			
		}
	}

	if (path.empty()) return;

	DrawRectangle((int)(path[0]->position.x - (cellSize / 2)), (int)(path[0]->position.y - (cellSize / 2)), (int)(cellSize - 1), (int)(cellSize - 1), firstBoxColor);

	DrawRectangle((int)(path[path.size()-1]->position.x - (cellSize / 2)), (int)(path[path.size() - 1]->position.y - (cellSize / 2)), (int)(cellSize - 1), (int)(cellSize - 1), GRAY);

}



//float AIForGames::Node::Heuristic(Node* start, Node* end)
//{
//	double dx = start->position.x - end->position.x;
//	double dy = start->position.y - end->position.y;
//	return dx * dx + dy * dy;
//}





std::vector<AIForGames::Node*> AIForGames::NodeMap::DijkstrasSearch(Node* start, Node* end)
{
	std::vector<Node*> path;
	if (start == nullptr || end == nullptr) {
		std::cout << "Start or end were nullptr" << std::endl;
		return path;
	}

	if (start == end) {
		return path;
	}

	// Reset nodes to base state, ready for pathfinding algorithm
	for (int i = 0; i < width * height; i++) {
		if (nodes[i] != nullptr) {
			nodes[i]->previous = nullptr;
			nodes[i]->gScore = 0;
		}
	}
	
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	AIForGames::Node* currentNode;

	openList.push_back(start);

	while (!openList.empty()) {
		// Lambda function to sort priority queue by gScore
		auto comp = [&](Node* a, Node* b) {return a->gScore > b->gScore; };
		std::sort(openList.begin(), openList.end(), comp);
		
		// Assign the next node in the open list to be our current node
		currentNode = openList.back();

		// Removes the top of the queue from the queue
		openList.pop_back();

		// Adds the currentNode to the closed list so we don't process again
		closedList.push_back(currentNode);


		for (int i = 0; i < currentNode->connections.size(); i++) {

			if (std::find(closedList.begin(), closedList.end(), currentNode->connections[i].target) == std::end(closedList)) {

				float gscore = currentNode->gScore + currentNode->connections[i].cost;
<<<<<<< HEAD
				float hScore = glm::length(end->position - currentNode->position) / cellSize;
				float fScore = gscore + hScore;
=======

>>>>>>> parent of 6c66b1d (starting a heuristic)


				if (std::find(openList.begin(), openList.end(), currentNode->connections[i].target) != std::end(openList)) {
					// Node is already in the open list with a valid score
					// so we need to compare the calculated score with the existing scre
					// to find the shorter path
					if (gscore < currentNode->connections[i].target->gScore) {
						currentNode->connections[i].target->gScore = gscore;
						currentNode->connections[i].target->previous = currentNode;
					}
				}
				else {
					currentNode->connections[i].target->gScore = gscore;
					currentNode->connections[i].target->previous = currentNode;
					openList.push_back(currentNode->connections[i].target);
				}
			}
		}
	}

	currentNode = end;
	while (currentNode != nullptr) {
		path.push_back(currentNode);
		currentNode = currentNode->previous;
	}
	std::reverse(path.begin(), path.end());
	return path;


}

void AIForGames::NodeMap::DrawPath()
{
	for (int i = 1; i < path.size(); i++) {
		DrawLine(path[i]->position.x, path[i]->position.y, path[i - 1]->position.x, path[i - 1]->position.y, GREEN);
	}
}





AIForGames::Node* AIForGames::NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int i = (int)(worldPos.x / cellSize);
	if (i < 0 || i >= width) return nullptr;

	int j = (int)(worldPos.y) / cellSize;
	if (j < 0 || j >= height) return nullptr;

	return GetNode(i, j);
}




AIForGames::NodeMap::~NodeMap()
{
	for (int i = 0; i < width * height; i++) {
		if (nodes[i] != nullptr) {
			delete nodes[i];
		}
	}
	delete[] nodes;
}




AIForGames::Node::Node(float x, float y)
{
	position.x = x;
	position.y = y;

}

void AIForGames::Node::ConnectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}

<<<<<<< HEAD
=======

>>>>>>> parent of 6c66b1d (starting a heuristic)




AIForGames::Edge::Edge() : Edge(nullptr, 0)
{
}

AIForGames::Edge::Edge(Node* target, float cost) :  target{target}, cost{cost}
{
}
