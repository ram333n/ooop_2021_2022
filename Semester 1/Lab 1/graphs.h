#pragma once
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>

class AdjacencyList {
public:
	AdjacencyList() = default;
	explicit AdjacencyList(size_t number_of_vertices);

	bool IsEdgeExist(int from, int to);
	
	void AddVertex(int number_of_vertex);
	void AddEdge(int from, int to);

	void RemoveVertex(int number_of_vertex);
	void RemoveEdge(int from, int to);

	bool IsConnected();
	int DistanceBetweenTwoVertices(int from, int to);
private:
	std::unordered_map<int, bool> GenerateVisitedMap();
	std::unordered_map<int, std::list<int>> adj_list;

	void Dfs(int start, std::unordered_map<int, bool>& is_visited);
};


class AdjacencyMatrix {
public:
	AdjacencyMatrix() = default;
	explicit AdjacencyMatrix(size_t number_of_vertices);

	bool IsEdgeExist(int from, int to);

	void AddVertex(int number_of_vertex);
	void AddEdge(int from, int to);

	void RemoveVertex(int number_of_vertex);
	void RemoveEdge(int from, int to);

	bool IsConnected();
	int DistanceBetweenTwoVertices(int from, int to);
private:
	std::vector<bool> non_empty_vertices;
	std::vector<std::vector<bool>> adj_matrix;

	std::unordered_map<int, bool> GenerateVisitedMap();
	void Dfs(int start, std::unordered_map<int, bool>& is_visited);
};
