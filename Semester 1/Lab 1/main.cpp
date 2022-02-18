#include "doctest.h"
#include "graphs.h"
#include "figures.h"
#include "sorting_algorithms.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

TEST_CASE("Default linked list construct") {
    Lists::LinkedList<int> linked_list;
    CHECK(linked_list.Size() == 0);
    CHECK(linked_list.Empty());
    CHECK(linked_list.begin() == linked_list.end());
}

TEST_CASE("LinkedList<int>::PushBack()") {
    std::vector<int> source, dest;
    source.resize(20);

    std::iota(source.begin(), source.end(), 0);
    Lists::LinkedList<int> linked_list;

    CHECK(linked_list.Empty());
    for (int num : source) {
        linked_list.PushBack(num);
    }

    for (auto num : linked_list) {
        dest.push_back(num);
    }

    CHECK(source == dest);
    CHECK(*linked_list.begin() == 0);
    CHECK(linked_list.Size() == 20);
}

TEST_CASE("LinkedList<int>::PushFront()") {
    std::vector<int> source, dest;
    Lists::LinkedList<int> linked_list;
    for (int i = 0; i < 20; ++i) {
        source.push_back(i);
        linked_list.PushFront(i);
    }
    CHECK(linked_list.Size() == 20);
    CHECK(*linked_list.begin() == 19);
    std::reverse(source.begin(), source.end());

    for (auto num : linked_list) {
        dest.push_back(num);
    }
    CHECK(source == dest);
}

TEST_CASE("LinkedList<int>::Insert()") {
    std::vector<int> source(10),dest;
    std::iota(source.begin(), source.end(), 0);
    Lists::LinkedList<int> linked_list;

    for (int num : source) {
        linked_list.PushBack(num);
    }

    CHECK(linked_list.Size() == 10);
    CHECK(*linked_list.begin() == 0);
    auto found_num = std::find(linked_list.begin(), linked_list.end(), 5);
    
    CHECK(*found_num == 5);

    linked_list.Insert(100, found_num);
    CHECK(linked_list.Size() == 11);
    auto source_it = std::find(source.begin(), source.end(), 5);
    source.insert(source_it, 100);

    for (auto num : linked_list) {
        dest.push_back(num);
    }

    CHECK(source == dest);

    linked_list.Insert(3000, linked_list.begin());
    CHECK(linked_list.Size() == 12);
    CHECK(*linked_list.begin() == 3000);

    linked_list.Insert(-3000, linked_list.end());
    CHECK(linked_list.Size() == 13);
}

TEST_CASE("LinkedList<int>::Remove()") {
    Lists::LinkedList<int> linked_list;
    linked_list.PushBack(1);
    linked_list.PushBack(13);

    linked_list.Remove(std::find(linked_list.begin(), linked_list.end(), 13));

    CHECK(++linked_list.begin() == linked_list.end());
    linked_list.PopBack();
    CHECK(linked_list.Empty());

    std::vector<int> source(20);
    std::iota(source.begin(), source.end(), 0);

    for (int num : source) {
        linked_list.PushBack(num);
    }

    auto it = linked_list.begin();
    while (it != linked_list.end()) {
        auto temp = it++;

        if (*temp % 4 > 0) {
            linked_list.Remove(temp);
        }
    }

    CHECK(linked_list.Size() == 5);
    source.clear();

    for (auto num : linked_list) {
        source.push_back(num);
    }

    const std::vector<int> expected = { 0, 4, 8, 12, 16 };
    CHECK(source == expected);
}

TEST_CASE("ArrayList default construct") {
    Lists::ArrayList<int> array_list;
    CHECK(array_list.Size() == 0);
    CHECK(array_list.Capacity() == 0);
    CHECK(array_list.end() == array_list.begin());
}

TEST_CASE("ArrayList construct") {
    Lists::ArrayList<int> array_list(5);
    CHECK(array_list.Size() == 5);
    CHECK(array_list.Capacity() == 5);
}

TEST_CASE("ArrayList<string>::PushBack()") {
    const std::string default_str = std::string(100, 'a');
    Lists::ArrayList<std::string> array_list(1);
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
    Lists::ArrayList<std::string> array_list(5);

    for (int i = 0; i < static_cast<int>(array_list.Size()); ++i) {
        array_list[i] = std::string(100, 'a' + i);
    }

    array_list.Insert("x", array_list.begin());
    CHECK(array_list.Size() == 6);
    CHECK(array_list.Capacity() == 10);
    CHECK(array_list[0] == "x");

    for (int i = 1; i < static_cast<int>(array_list.Size()); ++i) {
        CHECK(array_list[i] == std::string(100, 'a' + i - 1));
    }

    array_list.Insert("y", array_list.begin() + 3);
    CHECK(array_list.Size() == 7);
    CHECK(array_list.Capacity() == 10);
    CHECK(array_list[3] == "y");

    array_list.Remove(array_list.begin() + 3);
    CHECK(array_list.Size() == 6);
    CHECK(array_list.Capacity() == 10);

    array_list.Remove(array_list.begin());
    CHECK(array_list.Size() == 5);
    CHECK(array_list.Capacity() == 10);

    for (int i = 0; i < static_cast<int>(array_list.Size()); ++i) {
        CHECK(array_list[i] == std::string(100, 'a' + i));
    }


    Lists::ArrayList<int>test_empty;
    test_empty.Insert(1, test_empty.begin());

    CHECK(test_empty.Size() == 1);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty[0] == 1);

    test_empty.Remove(test_empty.begin());
    CHECK(test_empty.Size() == 0);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty.Empty());

    test_empty.Insert(-1, test_empty.begin() + 1000);
    CHECK(test_empty.Size() == 0);
    CHECK(test_empty.Capacity() == 1);
    CHECK(test_empty.Empty());
}

TEST_CASE("Test iterators on some stl algorithms") {
    std::vector<int> source = { -2, 6, 2, -31, 23, 65, 8743, 432, 65, 12, 7, 5 };
    SUBCASE("ArrayListIterator") {
        std::vector<int> copy_source(source.size());
        Lists::ArrayList<int> array_list(source.size());

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

    SUBCASE("LinkedListIterator") {
        Lists::LinkedList<int> linked_list;
        for (int i = 0; i < static_cast<int>(source.size()); ++i) {
            linked_list.PushBack(source[i]);
        }
        std::vector<int> copy_source(source.size());
        std::copy(linked_list.begin(), linked_list.end(), copy_source.begin());

        auto iter = linked_list.begin();

        while (std::next(iter) != linked_list.end()) {
            ++iter;
        }


        CHECK(copy_source == source);

        {
            Lists::LinkedList<int> sorted_list;
            std::iota(sorted_list.begin(), sorted_list.end(), 0);
            CHECK(std::is_sorted(sorted_list.begin(), sorted_list.end()));
        }

        auto it = std::find(linked_list.begin(), linked_list.end(), 432);
        CHECK(*it == 432);

        it = std::find(linked_list.begin(), linked_list.end(), -3034834);
        CHECK(it == linked_list.end());

        std::fill(linked_list.begin(), linked_list.end(), 10);

        CHECK(linked_list.Size() == std::count(linked_list.begin(), linked_list.end(), 10));

        {
            Lists::LinkedList<int> replaced_list;
            for (int i = 0; i < 40; ++i) {
                replaced_list.PushBack(i);
            }
            auto predicate = [](int num) {
                return num % 5 == 0;
            };

            std::replace_if(replaced_list.begin(), replaced_list.end(), predicate, 3);

            CHECK(std::count_if(replaced_list.begin(), replaced_list.end(), predicate) == 0);
        }
        {
            Lists::LinkedList<int> reversed_list;

            for (int i = 0; i < 40; ++i) {
                reversed_list.PushBack(i);
            }

            CHECK(std::is_sorted(reversed_list.begin(), reversed_list.end()));
        }

    }
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

//TEST_CASE("Tests for sorting algorithms") {
//    auto comparator = [](int lhs, int rhs) {
//        return lhs > rhs;
//    };
//    std::vector<int> source = { 1,6,-2,-4,45,-3,2,1,5,7,56,876,1337,45,21,0 };
//    ArrayList<int> arr_list(source.size());
//    {
//        LinkedList<int> linked_list;
//        std::list<int> stl_list;
//        for (size_t i = 0; i < source.size(); ++i) {
//            arr_list[i] = source[i];
//            linked_list.PushBack(source[i]);
//            stl_list.push_back(source[i]);
//        }
//
//        QuickSort(stl_list.begin(), stl_list.end(), comparator);
//        QuickSort(arr_list, 0, arr_list.Size() - 1, comparator);
//        QuickSort(linked_list.GetHead(), linked_list.GetTail(), comparator);
//
//        CHECK(std::is_sorted(stl_list.begin(), stl_list.end(), comparator));
//        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
//        CHECK(IsSorted(linked_list,comparator));
//    }
//
//    {
//        LinkedList<int> linked_list;
//        std::list<int> stl_list;
//        for (size_t i = 0; i < source.size(); ++i) {
//            arr_list[i] = source[i];
//            linked_list.PushBack(source[i]);
//            stl_list.push_back(source[i]);
//        }
//
//        MergeSort(stl_list.begin(), stl_list.end(), comparator);
//        MergeSort(linked_list, comparator);
//        MergeSort(arr_list.begin(), arr_list.end(), comparator);
//
//
//
//        CHECK(std::is_sorted(stl_list.begin(), stl_list.end(), comparator));
//        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
//        CHECK(IsSorted(linked_list, comparator));
//    }
//
//    {
//        LinkedList<int> linked_list;
//        std::list<int> stl_list;
//        for (size_t i = 0; i < source.size(); ++i) {
//            arr_list[i] = source[i];
//            linked_list.PushBack(source[i]);
//            stl_list.push_back(source[i]);
//        }
//
//        InsertionSort(linked_list, comparator);
//        InsertionSort(arr_list, comparator);
//
//        CHECK(std::is_sorted(arr_list.begin(), arr_list.end(), comparator));
//        CHECK(IsSorted(linked_list, comparator));
//    }      
//
//}

