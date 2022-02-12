#include "doctest.h"
#include "sorting_algorithms.h"
#include "graphs.h"
#include "figures.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

TEST_CASE("Default linked list construct") {
    LinkedList<int> l;
    CHECK(l.Size() == 0);
    CHECK(l.Empty());
    CHECK(l.GetHead() == l.GetTail());
    CHECK(l.GetHead() == nullptr);
}

TEST_CASE("LinkedList<int>::PushBack()") {
    std::vector<int> source, dest;
    source.resize(20);

    std::iota(source.begin(), source.end(), 0);
    LinkedList<int> l;

    CHECK(l.Empty());
    for (int num : source) {
        l.PushBack(num);
    }

    for (auto num = l.GetHead(); num; num = num->next) {
        dest.push_back(num->value);
    }

    CHECK(source == dest);
    CHECK(l.GetHead()->value == 0);
    CHECK(l.Size() == 20);
}

TEST_CASE("LinkedList<int>::PushFront()") {
    std::vector<int> source, dest;
    LinkedList<int> l;
    for (int i = 0; i < 20; ++i) {
        source.push_back(i);
        l.PushFront(i);
    }
    CHECK(l.Size() == 20);
    CHECK(l.GetHead()->value == 19);
    std::reverse(source.begin(), source.end());

    for (auto num = l.GetHead(); num; num = num->next) {
        dest.push_back(num->value);
    }
    CHECK(source == dest);
}

TEST_CASE("LinkedList<int>::Insert()") {
    std::vector<int> source(10),dest;
    std::iota(source.begin(), source.end(), 0);
    LinkedList<int> l;

    for (int num : source) {
        l.PushBack(num);
    }

    CHECK(l.Size() == 10);
    CHECK(l.GetHead()->value == 0);
    auto found_num = l.Find(5);
    
    CHECK(found_num->value == 5);

    l.Insert(100, found_num);
    CHECK(l.Size() == 11);
    auto source_it = std::find(source.begin(), source.end(), 5);
    source.insert(source_it, 100);

    for (auto num = l.GetHead(); num;num = num->next) {
        dest.push_back(num->value);
    }

    CHECK(source == dest);

    l.Insert(3000, l.GetHead());
    CHECK(l.Size() == 12);
    CHECK(l.GetHead()->value == 3000);

    l.Insert(-3000, l.GetTail()->next);
    CHECK(l.Size() == 12);
}

TEST_CASE("LinkedList<int>::Remove()") {
    LinkedList<int> l;
    l.PushBack(1);
    l.PushBack(13);

    l.Remove(l.Find(13));

    CHECK(l.GetHead() == l.GetTail());
    l.PopBack();
    CHECK(l.Empty());

    std::vector<int> source(20);
    std::iota(source.begin(), source.end(), 0);

    for (int num : source) {
        l.PushBack(num);
    }

    auto current_node = l.GetTail();
    while (current_node) {
        auto temp = current_node;
        current_node = current_node->prev;

        if (temp->value % 4 > 0) {
            l.Remove(temp);
        }
    }

    CHECK(l.Size() == 5);
    source.clear();

    for (auto current = l.GetTail(); current; current = current->prev) {
        source.push_back(current->value);
    }

    const std::vector<int> expected = { 16, 12, 8, 4, 0 };
    CHECK(source == expected);
}

TEST_CASE("ArrayList default construct") {
    ArrayList<int> array_list;
    CHECK(array_list.Size() == 0);
    CHECK(array_list.Capacity() == 0);
    CHECK(array_list.end() == array_list.begin());
}

TEST_CASE("ArrayList construct") {
    ArrayList<int> array_list(5);
    CHECK(array_list.Size() == 5);
    CHECK(array_list.Capacity() == 5);
}

TEST_CASE("ArrayList<string>::PushBack()") {
    const std::string default_str = std::string(100, 'a');
    ArrayList<std::string> array_list(1);
    array_list[0] = default_str;
    CHECK(array_list[0] == default_str);

    array_list.PushBack(default_str);
    CHECK(array_list.Size() == 2);
    CHECK(array_list.Capacity() == 2);

    for (int i = 0; i < 2; ++i) {
        array_list.PushBack(default_str);
    }

    CHECK(array_list.Size() == 4);
    CHECK(array_list.Capacity() == 4);

    array_list.PushBack(default_str);

    CHECK(array_list.Size() == 5);
    CHECK(array_list.Capacity() == 8);
}

TEST_CASE("ArrayList<string>::Insert() & ArrayList<string>::Remove()") {
    ArrayList<std::string> array_list(5);

    for (int i = 0; i < static_cast<int>(array_list.Size()); ++i) {
        array_list[i] = std::string(100, 'a' + i);
    }

    array_list.Insert("x", 0);
    CHECK(array_list.Size() == 6);
    CHECK(array_list.Capacity() == 10);
    CHECK(array_list[0] == "x");

    for (int i = 1; i < static_cast<int>(array_list.Size()); ++i) {
        CHECK(array_list[i] == std::string(100, 'a' + i - 1));
    }

    array_list.Insert("y", 3);
    CHECK(array_list.Size() == 7);
    CHECK(array_list.Capacity() == 10);
    CHECK(array_list[3] == "y");

    array_list.Remove(3);
    CHECK(array_list.Size() == 6);
    CHECK(array_list.Capacity() == 10);

    array_list.Remove(0);
    CHECK(array_list.Size() == 5);
    CHECK(array_list.Capacity() == 10);

    for (int i = 0; i < static_cast<int>(array_list.Size()); ++i) {
        CHECK(array_list[i] == std::string(100, 'a' + i));
    }


    ArrayList<int>test_empty;
    test_empty.Insert(1, 0);

    CHECK(test_empty.Size() == 1);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty[0] == 1);

    test_empty.Remove(0);
    CHECK(test_empty.Size() == 0);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty.Empty());

    test_empty.Insert(-1,1000);
    CHECK(test_empty.Size() == 0);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty.Empty());
}

TEST_CASE("Test simple iterators of ArrayList<int> on some stl algorithms") {
    std::vector<int> source = { -2, 6, 2, -31, 23, 65, 8743, 432, 65, 12, 7, 5 };
    std::vector<int> copy_source(source.size());
    ArrayList<int> array_list(source.size());

    for (int i = 0; i < static_cast<int>(source.size()); ++i) {
        array_list[i] = source[i];
    }

    std::copy(array_list.begin(), array_list.end(), copy_source.begin());
    CHECK(copy_source == source);
    std::sort(array_list.begin(), array_list.end());
    bool is_sorted = std::is_sorted(array_list.begin(), array_list.end());

    CHECK(is_sorted);

    auto it = std::find(array_list.begin(), array_list.end(), 432);
    CHECK(*it == 432);

    it = std::find(array_list.begin(), array_list.end(), -3034834);
    CHECK(it == array_list.end());
    std::fill(array_list.begin(), array_list.end(), 10);

    CHECK(array_list.Size() == std::count(array_list.begin(), array_list.end(), 10));

    auto equal_range_res = std::equal_range(array_list.begin(), array_list.end(), 10);
    CHECK(equal_range_res.second - equal_range_res.first == std::count(array_list.begin(), array_list.end(), 10));
}

TEST_CASE("Graphs") {
    SUBCASE("Adjacency list") {
        Graphs::AdjacencyList graph(6);
        graph.AddEdge(0, 3);
        graph.AddEdge(0, 3);

        graph.AddEdge(0, 4);
        graph.AddEdge(0, 5);

        graph.AddEdge(1, 3);
        graph.AddEdge(1, 4);
        graph.AddEdge(1, 5);

        graph.AddEdge(2, 3);
        graph.AddEdge(2, 4);
        graph.AddEdge(2, 5);

        CHECK(graph.IsConnected());
        CHECK(graph.IsEdgeExist(0, 3));
        CHECK(graph.IsEdgeExist(0, 4));
        CHECK(graph.IsEdgeExist(0, 5));
        CHECK(graph.IsEdgeExist(1, 3));
        CHECK(graph.IsEdgeExist(1, 4));
        CHECK(graph.IsEdgeExist(1, 5));
        CHECK(graph.IsEdgeExist(1, 3));
        CHECK(graph.IsEdgeExist(1, 4));
        CHECK(graph.IsEdgeExist(1, 5));

        CHECK(graph.DistanceBetweenTwoVertices(0, 2) == 2);
        CHECK(graph.DistanceBetweenTwoVertices(0, 1) == 2);
        CHECK(graph.DistanceBetweenTwoVertices(0, 5) == 1);
        CHECK(graph.DistanceBetweenTwoVertices(0, 0) == 0);

        graph.RemoveVertex(0);
        graph.RemoveVertex(3);

        CHECK(graph.IsConnected());
        CHECK(graph.DistanceBetweenTwoVertices(1, 2) == 2);
        graph.RemoveEdge(2, 4);
        graph.RemoveEdge(1, 5);

        CHECK(!graph.IsConnected());
        CHECK(graph.DistanceBetweenTwoVertices(2, 4) == 0);
    }
    SUBCASE("Adjacency matrix") {
        Graphs::AdjacencyMatrix graph(6);
        graph.AddEdge(0, 3);
        graph.AddEdge(0, 3);

        graph.AddEdge(0, 4);
        graph.AddEdge(0, 5);

        graph.AddEdge(1, 3);
        graph.AddEdge(1, 4);
        graph.AddEdge(1, 5);

        graph.AddEdge(2, 3);
        graph.AddEdge(2, 4);
        graph.AddEdge(2, 5);

        CHECK(graph.IsConnected());
        CHECK(graph.IsEdgeExist(0, 3));
        CHECK(graph.IsEdgeExist(0, 4));
        CHECK(graph.IsEdgeExist(0, 5));
        CHECK(graph.IsEdgeExist(1, 3));
        CHECK(graph.IsEdgeExist(1, 4));
        CHECK(graph.IsEdgeExist(1, 5));
        CHECK(graph.IsEdgeExist(1, 3));
        CHECK(graph.IsEdgeExist(1, 4));
        CHECK(graph.IsEdgeExist(1, 5));

        CHECK(graph.DistanceBetweenTwoVertices(0, 2) == 2);
        CHECK(graph.DistanceBetweenTwoVertices(0, 1) == 2);
        CHECK(graph.DistanceBetweenTwoVertices(0, 5) == 1);
        CHECK(graph.DistanceBetweenTwoVertices(0, 0) == 0);

        graph.RemoveVertex(0);
        graph.RemoveVertex(3);

        CHECK(graph.IsConnected());
        CHECK(graph.DistanceBetweenTwoVertices(1, 2) == 2);
        graph.RemoveEdge(2, 4);
        graph.RemoveEdge(1, 5);

        CHECK(!graph.IsEdgeExist(2, 4));
        CHECK(!graph.IsEdgeExist(1, 5));

        CHECK(!graph.IsConnected());
        CHECK(graph.DistanceBetweenTwoVertices(2, 4) == 0);
        graph.AddEdge(2, 4);

        CHECK(graph.IsConnected());
    }
    
}


TEST_CASE("Test reflections") {
    Point p_1 = { 1,1 };
    Line l_1 = { 1,1,0 };
    Point exp_p_1 = { -1,-1 };
    CHECK(ReflectPoint(p_1, l_1) == exp_p_1);

    Point p_2 = { 1,2 };
    Line l_2 = { 1,-2,-2 };
    Point exp_p_2 = { 3,-2 };

    CHECK(ReflectPoint(p_2, l_2) == exp_p_2);

    Point p_3 = { 1,2 };
    Line l_3 = { 0,1,0 };
    Point exp_p_3 = { 1,-2 };

    CHECK(ReflectPoint(p_3, l_3) == exp_p_3);

    Point p_4 = { 1,2 };
    Line l_4 = { 1,0,0 };
    Point exp_p_4 = { -1,2 };

    CHECK(ReflectPoint(p_4, l_4) == exp_p_4);

    //----------------------------------------

    Line l_5 = { 1,1,0 };
    Line r = { 1,0,0 };
    Line exp = { -1,1,0 };

    Line res = ReflectLine(l_5, r);


    CHECK(ReflectLine(l_5, r).GetA() == exp.GetA());
    CHECK(ReflectLine(l_5, r).GetB() == exp.GetB());
    CHECK(ReflectLine(l_5, r).GetC() == exp.GetC());
}

TEST_CASE("Tests for sorting algorithms") {
    auto comparator = [](int lhs, int rhs) {
        return lhs > rhs;
    };
    std::vector<int> source = { 1,6,-2,-4,45,-3,2,1,5,7,56,876,1337,45,21,0 };
    ArrayList<int> arr_list(source.size());
    {
        LinkedList<int> linked_list;
        std::list<int> stl_list;
        for (size_t i = 0; i < source.size(); ++i) {
            arr_list[i] = source[i];
            linked_list.PushBack(source[i]);
            stl_list.push_back(source[i]);
        }

        QuickSort(stl_list.begin(), stl_list.end(), comparator);
        QuickSort(arr_list, 0, arr_list.Size() - 1, comparator);
        QuickSort(linked_list.GetHead(), linked_list.GetTail(), comparator);

        CHECK(std::is_sorted(stl_list.begin(), stl_list.end(), comparator));
        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
        CHECK(IsSorted(linked_list,comparator));
    }

    {
        LinkedList<int> linked_list;
        std::list<int> stl_list;
        for (size_t i = 0; i < source.size(); ++i) {
            arr_list[i] = source[i];
            linked_list.PushBack(source[i]);
            stl_list.push_back(source[i]);
        }

        MergeSort(stl_list.begin(), stl_list.end(), comparator);
        MergeSort(linked_list, comparator);
        MergeSort(arr_list.begin(), arr_list.end(), comparator);



        CHECK(std::is_sorted(stl_list.begin(), stl_list.end(), comparator));
        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
        CHECK(IsSorted(linked_list, comparator));
    }

    {
        LinkedList<int> linked_list;
        std::list<int> stl_list;
        for (size_t i = 0; i < source.size(); ++i) {
            arr_list[i] = source[i];
            linked_list.PushBack(source[i]);
            stl_list.push_back(source[i]);
        }

        InsertionSort(linked_list, comparator);
        InsertionSort(arr_list, comparator);

        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
        CHECK(IsSorted(linked_list, comparator));
    }      

}

