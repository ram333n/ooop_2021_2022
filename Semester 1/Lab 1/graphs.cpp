#include "graphs.h"

AdjacencyList::AdjacencyList(size_t number_of_vertices) {
	for (size_t i = 0; i < number_of_vertices; ++i) {
		adj_list[i] = std::list<int>();
	}
}

void AdjacencyList::AddVertex(int number_of_vertex) {
	if (adj_list.find(number_of_vertex) == adj_list.end()) {
		adj_list[number_of_vertex] = std::list<int>();
	}
}


bool AdjacencyList::IsEdgeExist(int from, int to) {

	if (adj_list.find(from) != adj_list.end()) {
		for (auto it = adj_list[from].begin(); it != adj_list[from].end(); ++it) {
			if (*it == to) {
				return true;
			}
		}
	}

	return false;
}


void AdjacencyList::AddEdge(int from, int to) {
	if (IsEdgeExist(from, to)) {
		return;
	}

	adj_list[from].push_back(to);
	adj_list[to].push_back(from);
}

void AdjacencyList::RemoveVertex(int number_of_vertex) {
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

void AdjacencyList::RemoveEdge(int from, int to) {
	for (auto it = adj_list[from].begin(); it != adj_list[from].end(); ++it) {
		if (*it == to) {
			adj_list[from].erase(it);
			break;
		}
	}

	for (auto it = adj_list[to].begin(); it != adj_list[to].end(); ++it) {
		if (*it == from) {
			adj_list[to].erase(it);
			break;
		}
	}
}


std::unordered_map<int, bool> AdjacencyList::GenerateVisitedMap() {
	std::unordered_map<int, bool> is_visited;

	for (const auto& p : adj_list) {
		is_visited[p.first] = false;
	}
	return is_visited;
}


void AdjacencyList::Dfs(int start, std::unordered_map<int, bool>& is_visited) {
	std::stack<int> stack;
	stack.push(start);

	while (!stack.empty()) {
		start = stack.top();
		stack.pop();

		if (!is_visited[start]) {
			is_visited[start] = true;
		}

		for (int adj_vertex : adj_list[start]) {
			if (!is_visited[adj_vertex]) {
				stack.push(adj_vertex);
			}
		}
	}
}

bool AdjacencyList::IsConnected() {
	std::unordered_map<int, bool> is_visited = GenerateVisitedMap();

	bool to_break_search = false;
	for (const auto& p : adj_list) {
		if (!is_visited[p.first]) {
			if (to_break_search) {
				return false;
			}
			Dfs(p.first, is_visited);
			to_break_search = true;
		}
	}

	return true;
}

int AdjacencyList::DistanceBetweenTwoVertices(int from, int to) {
	if (adj_list.find(from) == adj_list.end() || adj_list.find(to) == adj_list.end()) {
		return 0;
	}

	std::unordered_map<int, bool> is_visited = GenerateVisitedMap();
	std::unordered_map<int, int> distance;
	for (const auto& p : adj_list) {
		distance[p.first] = 0;
	}

	std::queue<int> queue;

	queue.push(from);
	is_visited[from] = true;
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();

		for (int adj_vertex : adj_list[current]) {
			if (!is_visited[adj_vertex]) {
				distance[adj_vertex] = distance[current] + 1;
				queue.push(adj_vertex);
				is_visited[adj_vertex] = true;
			}
		}
	}
	return distance[to];
}

//---------------------------------------------------------------------------------

AdjacencyMatrix::AdjacencyMatrix(size_t number_of_vertices) {
	adj_matrix.resize(number_of_vertices);

	for (auto& row : adj_matrix) {
		row.resize(number_of_vertices, false);
	}

	non_empty_vertices.resize(number_of_vertices, true);
}

bool AdjacencyMatrix::IsEdgeExist(int from, int to) {
	if (from >= static_cast<int>(adj_matrix.size()) || to >= static_cast<int>(adj_matrix.size()) || from < 0 || to < 0) {
		return false;
	}

	return adj_matrix[from][to];
}

void AdjacencyMatrix::AddVertex(int number_of_vertex) {
	if (number_of_vertex >= static_cast<int>(adj_matrix.size()) || number_of_vertex < 0) {
		return;
	}

	if (non_empty_vertices[number_of_vertex]) {
		return;
	}

	non_empty_vertices[number_of_vertex] = true;
}

void AdjacencyMatrix::AddEdge(int from, int to) {
	if (from >= static_cast<int>(adj_matrix.size()) || to >= static_cast<int>(adj_matrix.size()) || from < 0 || to < 0) {
		return;
	}

	if (non_empty_vertices[from] && non_empty_vertices[to]) {
		adj_matrix[from][to] = true;
		adj_matrix[to][from] = true;
	}
}


void AdjacencyMatrix::RemoveVertex(int number_of_vertex) {
	if (number_of_vertex >= static_cast<int>(adj_matrix.size()) || number_of_vertex < 0) {
		return;
	}

	for (size_t i = 0; i < adj_matrix.size(); ++i) {
		adj_matrix[i][number_of_vertex] = false;
		adj_matrix[number_of_vertex][i] = false;
	}
	
	non_empty_vertices[number_of_vertex] = false;
}

void AdjacencyMatrix::RemoveEdge(int from, int to) {
	if (from >= static_cast<int>(adj_matrix.size()) || to >= static_cast<int>(adj_matrix.size())) {
		return;
	}

	adj_matrix[from][to] = false;
	adj_matrix[to][from] = false;
}

void AdjacencyMatrix::Dfs(int start, std::unordered_map<int, bool>& is_visited) {
	is_visited[start] = true;

	for (int i = 0; i < static_cast<int>(adj_matrix.size()); i++) {
		if (non_empty_vertices[i]) {
			if (adj_matrix[start][i] && (!is_visited[i])) {
				Dfs(i, is_visited);
			}
		}
	}
}

std::unordered_map<int, bool> AdjacencyMatrix::GenerateVisitedMap() {
	std::unordered_map<int, bool> result;
	for (int i = 0; i < static_cast<int>(non_empty_vertices.size()); ++i) {
		if (non_empty_vertices[i]) {
			result[i] = false;
		}
	}

	return result;
}

bool AdjacencyMatrix::IsConnected() {
	std::unordered_map<int, bool> is_visited = GenerateVisitedMap();
	bool to_break_search = false;
	for (int i = 0; i < static_cast<int>(adj_matrix.size()); ++i) {
		if (non_empty_vertices[i]) {
			if (!is_visited[i]) {
				if (to_break_search) {
					return false;
				}

				Dfs(i, is_visited);
				to_break_search = true;
			}
		}
	}

	return true;
}

int AdjacencyMatrix::DistanceBetweenTwoVertices(int from, int to) {
	if(from >= static_cast<int>(adj_matrix.size()) || to >= static_cast<int>(adj_matrix.size()) || from < 0 || to < 0) {
		return 0;
	}

	std::unordered_map<int, bool> is_visited = GenerateVisitedMap();
	std::unordered_map<int, int> distance;
	for (const auto& p : is_visited) {
		distance[p.first] = 0;
	}

	std::queue<int> queue;

	queue.push(from);
	is_visited[from] = true;
	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();
		for (int i = 0; i < static_cast<int>(adj_matrix.size());++i) {
			if (adj_matrix[current][i]) {
				if (!is_visited[i]) {
					distance[i] = distance[current] + 1;
					queue.push(i);
					is_visited[i] = true;
				}
			}
		}
	}
	return distance[to];
}
