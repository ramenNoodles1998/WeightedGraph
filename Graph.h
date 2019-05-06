
#pragma once
/********************************************************************************************
**	Project: Graph
**  Programmer: Roman Meredith
**  Course:		cs2420
**	Section:	602
**	Assignment: 9
**	Data:		November 28, 2018
**
**	I certify that I wrote all code in this project except that which was
**	provided by the instructor.
**
***********************************************************************************************/
#include <string>
#include <unordered_set>
class Vertex {
public:
	Vertex() = default;
	std::string label;
	int distance;
	int prevV;
	bool visited;
};
class Graph
{
public:
	Graph();

	bool AddVertex(std::string label);
	void PrintGraph();
	int AddEdge(std::string from, std::string to, int weight);
	void BreadthFirstSearch(std::string startingLabel);
	void DijkstraShortedPath(std::string startingVertex);
	int GetWeight(int sourceIndex, int targetIndex);

private:
	const static int MAX_VERTICES = 10;
	const int MAXINT = 200000000;
	int matrix[MAX_VERTICES][MAX_VERTICES];
	int numVertices;
	std::string labels[MAX_VERTICES];
	int FindIndex(const std::string &label);
	bool VerticesHaveAFalse(Vertex array[], int size);
	int PopSmallestIndexOfFalse(Vertex array[], int size);
};
