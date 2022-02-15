#pragma once
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>

namespace Graphs {
	class AbstractGraph {
	public:
		virtual ~AbstractGraph() = default;
		virtual bool IsEdgeExist(int from, int to) const = 0;

		virtual void AddVertex(int number_of_vertex) = 0;
		virtual void AddEdge(int from, int to) = 0;

		virtual void RemoveVertex(int number_of_vertex) = 0;
		virtual void RemoveEdge(int from, int to) = 0;

		virtual bool IsConnected() const = 0;
		virtual int DistanceBetweenTwoVertices(int from, int to) const = 0;
	private:
		virtual std::unordered_map<int, bool> GenerateVisitedMap() const = 0;
		virtual void Dfs(int start, std::unordered_map<int, bool>& is_visited) const = 0;
	};


	class AdjacencyList : public AbstractGraph {
	public:
		AdjacencyList() = default;

		explicit AdjacencyList(size_t number_of_vertices) {
			for (size_t i = 0; i < number_of_vertices; ++i) {
				adj_list[i] = std::list<int>();
			}
		}

		void AddVertex(int number_of_vertex) override {
			if (adj_list.find(number_of_vertex) == adj_list.end()) {
				adj_list[number_of_vertex] = std::list<int>();
			}
		}

		bool IsEdgeExist(int from, int to) const override {
			if (adj_list.find(from) == adj_list.end()) {
				return false;
			}

			return std::find(adj_list.at(from).begin(), adj_list.at(from).end(), to) != adj_list.at(from).end();
		}


		void AddEdge(int from, int to) override {
			if (IsEdgeExist(from, to)) {
				return;
			}

			adj_list[from].push_back(to);
			adj_list[to].push_back(from);
		}

		void RemoveVertex(int number_of_vertex) override {
			auto list_to_remove = adj_list.find(number_of_vertex);
			if (list_to_remove == adj_list.end()) {
				return;
			}

			for (int adjacent_vertex : list_to_remove->second) {
				auto to_remove = std::find(adj_list[adjacent_vertex].begin(), adj_list[adjacent_vertex].end(), number_of_vertex);

				if (to_remove != adj_list[adjacent_vertex].end()) {
					adj_list[adjacent_vertex].erase(to_remove);
				}
			}

			adj_list.erase(list_to_remove);
		}

		void RemoveEdge(int from, int to) override {
			auto first_entrance = std::find(adj_list[from].begin(), adj_list[from].end(), to);
			auto second_entrance = std::find(adj_list[to].begin(), adj_list[to].end(), from);

			if (first_entrance != adj_list[from].end()) {
				adj_list[from].erase(first_entrance);
				adj_list[to].erase(second_entrance);
			}
		}

		bool IsConnected() const override {
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

		int DistanceBetweenTwoVertices(int from, int to) const override {
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

				for (int adj_vertex : adj_list.at(current)) {
					if (!is_visited[adj_vertex]) {
						distance[adj_vertex] = distance[current] + 1;
						queue.push(adj_vertex);
						is_visited[adj_vertex] = true;
					}
				}
			}
			return distance[to];
		}


	private:
		std::unordered_map<int, bool> GenerateVisitedMap() const override {
			std::unordered_map<int, bool> is_visited;

			for (const auto& p : adj_list) {
				is_visited[p.first] = false;
			}
			return is_visited;
		}

		void Dfs(int start, std::unordered_map<int, bool>& is_visited) const override {
			std::stack<int> stack;
			stack.push(start);

			while (!stack.empty()) {
				start = stack.top();
				stack.pop();

				if (!is_visited[start]) {
					is_visited[start] = true;
				}

				for (int adj_vertex : adj_list.at(start)) {
					if (!is_visited[adj_vertex]) {
						stack.push(adj_vertex);
					}
				}
			}
		}

		std::unordered_map<int, std::list<int>> adj_list;
	};


	class AdjacencyMatrix : public AbstractGraph {
	public:
		AdjacencyMatrix() = default;

		explicit AdjacencyMatrix(size_t number_of_vertices) {
			adj_matrix.resize(number_of_vertices);

			for (auto& row : adj_matrix) {
				row.resize(number_of_vertices, false);
			}

			non_empty_vertices.resize(number_of_vertices, true);
		}

		bool IsEdgeExist(int from, int to) const override {
			if (from >= adj_matrix.size() || to >= adj_matrix.size() || from < 0 || to < 0) {
				return false;
			}

			return adj_matrix[from][to];
		}

		void AddVertex(int number_of_vertex) override {
			if (number_of_vertex >= adj_matrix.size() || number_of_vertex < 0) {
				return;
			}

			if (non_empty_vertices[number_of_vertex]) {
				return;
			}

			non_empty_vertices[number_of_vertex] = true;
		}

		void AddEdge(int from, int to) override {
			if (from >= adj_matrix.size() || to >= adj_matrix.size() || from < 0 || to < 0) {
				return;
			}

			if (non_empty_vertices[from]) {
				adj_matrix[from][to] = true;
				adj_matrix[to][from] = true;
			}
		}


		void RemoveVertex(int number_of_vertex) override {
			if (number_of_vertex >= adj_matrix.size() || number_of_vertex < 0) {
				return;
			}

			for (size_t i = 0; i < adj_matrix.size(); ++i) {
				adj_matrix[i][number_of_vertex] = false;
				adj_matrix[number_of_vertex][i] = false;
			}

			non_empty_vertices[number_of_vertex] = false;
		}

		void RemoveEdge(int from, int to) override {
			if (from >= adj_matrix.size() || to >= adj_matrix.size()) {
				return;
			}

			adj_matrix[from][to] = false;
			adj_matrix[to][from] = false;
		}

		bool IsConnected() const override {
			std::unordered_map<int, bool> is_visited = GenerateVisitedMap();

			bool to_break_search = false;
			for (int i = 0; i < adj_matrix.size(); ++i) {
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

		int DistanceBetweenTwoVertices(int from, int to) const override {
			if (from >= adj_matrix.size() || to >= adj_matrix.size() || from < 0 || to < 0) {
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
				for (int i = 0; i < adj_matrix.size(); ++i) {
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
	
	private:
		void Dfs(int start, std::unordered_map<int, bool>& is_visited) const override {
			is_visited[start] = true;

			for (int i = 0; i < adj_matrix.size(); i++) {
				if (non_empty_vertices[i]) {
					if (adj_matrix[start][i] && (!is_visited[i])) {
						Dfs(i, is_visited);
					}
				}
			}
		}

		std::unordered_map<int, bool> GenerateVisitedMap() const override {
			std::unordered_map<int, bool> result;
			for (int i = 0; i < non_empty_vertices.size(); ++i) {
				if (non_empty_vertices[i]) {
					result[i] = false;
				}
			}

			return result;
		}

		std::vector<bool> non_empty_vertices;
		std::vector<std::vector<bool>> adj_matrix;
	};
}

