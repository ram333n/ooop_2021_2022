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
    CHECK(l.begin() == l.end());
    CHECK(l.begin() == LinkedList<int>::Iterator());
}

TEST_CASE("LinkedList<int>::PushBack()") {
    std::vector<int> source, dest;
    source.resize(50);

    std::iota(source.begin(), source.end(), 0);
    LinkedList<int> l;

    CHECK(l.Empty() == true);
    for (auto num : source) {
        l.PushBack(num);
    }

    for (auto num : l) {
        dest.push_back(num);
    }

    CHECK(source == dest);
    CHECK(*l.begin() == 0);
    CHECK(l.Size() == 50);
}


//Insert
//Remove(back,front)
//Iterators

//int main()
//{
//    std::cout << "Hello World!\n";
//}
