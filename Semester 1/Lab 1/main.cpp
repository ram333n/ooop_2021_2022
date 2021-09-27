#include "doctest.h"
#include "linked_list.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

TEST_CASE("Default linked list construct") {
    LinkedList<int> l;
    CHECK(l.Size() == 0);
    CHECK(l.Empty() == true);
    CHECK(l.GetHead() == l.GetTail());
    CHECK(l.GetHead() == nullptr);
}

TEST_CASE("LinkedList<int>::PushBack()") {
    std::vector<int> source, dest;
    source.resize(20);

    std::iota(source.begin(), source.end(), 0);
    LinkedList<int> l;

    CHECK(l.Empty() == true);
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
    CHECK(l.Empty() == true);

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


//Insert
//Remove(back,front)

//int main()
//{
//    std::cout << "Hello World!\n";
//}
