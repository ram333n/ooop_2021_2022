#pragma once
#include <unordered_map>

class AdjacencyList {
public:
	using Edge = std::pair<std::list<int>::iterator, std::list<int>::iterator>;

	AdjacencyList() = default;
	AdjacencyList(size_t number_of_vertices);

	Edge GetPositionsInAdjList(size_t from, size_t to);
	bool IsEdgeExist(size_t from, size_t to);
	
	void AddVertex(size_t number_of_vertex);
	void AddEdge(size_t from, size_t to);

	void RemoveVertex(size_t number_of_vertex);
	void RemoveEdge(size_t from, size_t to);

	void Dfs(int start, std::vector<bool>& visited);

	bool IsConnected();
	size_t VerticesCount() const;
private:
	std::unordered_map<int, std::list<int>> adj_list;
};
