#include "graphs.h"

AdjacencyList::AdjacencyList(size_t number_of_vertices) {
	for (size_t i = 0; i < number_of_vertices; ++i) {
		adj_list[i] = std::list<int>();
	}
}

void AdjacencyList::AddVertex(size_t number_of_vertex) {
	if (adj_list.find(number_of_vertex) == adj_list.end()) {
		adj_list[number_of_vertex] = std::list<int>();
	}
}

AdjacencyList::Edge AdjacencyList::GetPositionsInAdjList(size_t from, size_t to) {
	AdjacencyList::Edge result = {};

	if (adj_list.find(from) != adj_list.end()) {
		for (auto it = adj_list[from].begin(); it != adj_list[from].end(); ++it) {
			if (*it == to) {
				result.first = it;
				break;
			}
		}

		for (auto it = adj_list[to].begin(); it != adj_list[to].end(); ++it) {
			if (*it == from) {
				result.second = it;
				break;
			}
		}
	}

	return result;
}

bool AdjacencyList::IsEdgeExist(size_t from, size_t to) {
	auto found_edge = GetPositionsInAdjList(from, to);
	return !(found_edge == Edge{} || found_edge == {adj_list[from].end(), adj_list[to].end()});
}

void AdjacencyList::AddVertex(size_t number_of_vertex) {
	if (adj_list.find(number_of_vertex) == adj_list.end()) {
		adj_list[number_of_vertex] = std::list<int>();
	}
}

void AdjacencyList::AddEdge(size_t from, size_t to) {
	if (IsEdgeExist(from, to)) {
		return;
	}

	adj_list[from].push_back(to);
	adj_list[to].push_back(from);
}

void AdjacencyList::RemoveVertex(size_t number_of_vertex) {
	auto to_remove = adj_list.find(number_of_vertex);
	if (to_remove == adj_list.end()) {
		return;
	}

	for (int adjacent_vertex : to_remove->second) {
		for (auto it = adj_list[adjacent_vertex].begin(); it != adj_list[adjacent_vertex].end(); ++it) {
			if (*it == number_of_vertex) {
				adj_list[adjacent_vertex].erase(it);
				break;
			}
		}
	}

	adj_list.erase(to_remove);
}

void AdjacencyList::RemoveEdge(size_t from, size_t to) {
	auto edge_to_remove = GetPositionsInAdjList(from, to);

	if (!(edge_to_remove == Edge{} || edge_to_remove == {adj_list[from].end(), adj_list[to].end()})) {
		return;
	}

	adj_list[from].erase(edge_to_remove.first);
	adj_list[to].erase(edge_to_remove.second);
}

