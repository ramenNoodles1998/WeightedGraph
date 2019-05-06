
#include <iostream>
#include <cassert>
#include <stack>
#include <unordered_set>
#include <climits>
#include <queue>
#include <vector>

#include "Graph.h"

using namespace std;

Graph::Graph()
{
	for (int from = 0; from < MAX_VERTICES; from++)
	{
		for (int to = 0; to < MAX_VERTICES; to++)
		{
			matrix[from][to] = MAXINT;
		}
	}

	numVertices = 0;
}

bool Graph::AddVertex(std::string label)
{
	if (numVertices == MAX_VERTICES)
		return false;
	else
		labels[numVertices++] = label;

	return true;
}

int Graph::AddEdge(std::string from, std::string to, int weight)
{
	int fromIndex = FindIndex(from);
	int toIndex = FindIndex(to);

	if (fromIndex == -1 || toIndex == -1)
		return false;

	matrix[fromIndex][toIndex] = weight;
	return weight;
}

int Graph::FindIndex(const std::string & label)
{
	for (int i = 0; i < numVertices; i++)
	{
		if (labels[i] == label)
			return i;
	}

	return -1;
}

void Graph::PrintGraph()
{
	std::cout << "\t";
	for (int i = 0; i < numVertices; i++)
	{
		cout << labels[i] << "\t";
	}
	cout << endl;

	for (int from = 0; from < numVertices; from++)
	{
		cout << labels[from];
		for (int to = 0; to < numVertices; to++)
		{
			if (matrix[from][to] != MAXINT)
				cout << "\t"<<matrix[from][to];
			else
				cout << "\t ";
		}
		cout << endl;
	}

	cout << endl;
}

void Graph::BreadthFirstSearch(std::string startingLabel)
{
	int startingIndex = FindIndex(startingLabel);
	assert(startingIndex != -1);
	queue<int> myQ;
	unordered_set<int> visited;

	cout << "Starting BFS with vertex " << startingLabel << endl;
	myQ.push(startingIndex);
	while (myQ.empty() == false){
		int currentV = myQ.front(); myQ.pop();
		cout << "\t" << "visited " << labels[currentV]<< endl;
		visited.insert(currentV);
		for (int i = 0; i < numVertices; i++) {
			if (matrix[currentV][i] != MAXINT && visited.find(i) == visited.end()) {
				visited.insert(i);
				myQ.push(i);
			}
		}
	}
	cout << " " << endl;
}
int Graph::GetWeight(int sourceIndex, int targetIndex)
{
	if (matrix[sourceIndex][targetIndex] == MAXINT) {
		return MAXINT;
	}
	int weight = matrix[sourceIndex][targetIndex];
	return weight;
	
}
void Graph::DijkstraShortedPath(std::string startingVertex)
{
	int startingIndex = FindIndex(startingVertex);
	assert(startingIndex != -1);
	const int size = 10;
	Vertex vertices[size];

	for (int i = 0; i < numVertices; i++) {
		vertices[i].distance = MAXINT;
		vertices[i].prevV = -1;
		vertices[i].visited = false;
	}

	vertices[startingIndex].distance = 0;

	while (VerticesHaveAFalse(vertices, 6)) {
		int currentV = PopSmallestIndexOfFalse(vertices, 6);
		vertices[currentV].visited = true;
		if (currentV == 50) {
			break;
		}
		for (int i = 0; i < numVertices; i++) {
			if (matrix[currentV][i] != MAXINT) {
				int edgeWeight = matrix[currentV][i];
				int alternativePathDistance = vertices[currentV].distance + edgeWeight;
				if (alternativePathDistance < vertices[i].distance ) {
					vertices[i].distance = alternativePathDistance;
					vertices[i].prevV = currentV;
				}
			}
		}
	}
	cout << "Shortest Distance starting from vertex " << labels[startingIndex]<<endl;
	for (int i = 0; i < 6; i++) {
		int previousVector = vertices[i].prevV;
		cout << "\tto:" << labels[i] << " ";
		if (vertices[i].distance == MAXINT) {
			cout << "\tno path" << endl;
			
		}
		else {
			cout << "\t" << vertices[i].distance << " ";
			cout << "\tPath: " << labels[i] << ",";
			while (previousVector != -1) {
				cout << labels[previousVector] << ", ";
				previousVector = vertices[previousVector].prevV;
			}
			cout << endl;
		}
	}
	cout << endl;
}

bool Graph::VerticesHaveAFalse(Vertex array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i].visited == false) {
			return true;
		}
	}
	return false;
}

int Graph::PopSmallestIndexOfFalse(Vertex array[], int size)
{
	int smallestIndex = 50;
	int smallestDistance = 50;
	for (int i = 0; i < size; i++)
	{
		if (array[i].visited == false) {
			if (smallestDistance > array[i].distance) {
				smallestDistance = array[i].distance;
				smallestIndex = i;
			}
		}
	}
	
	return smallestIndex;
}
