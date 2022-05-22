#include "doctest.h"
#include "nodes_builder.h"

#include <iostream>

TEST_CASE("Builder"){
    SUBCASE("List node"){
        ListNodePtr<int> n1 = ListNodeBuilder<int>().SetValue(42);
        ListNodePtr<int> n2 = ListNodeBuilder<int>().SetValue(21).SetNext(n1);

        CHECK(n2->_next == n1);
        CHECK(n2->_next->_value == 42);
        CHECK(n2->_value == 21);
    }

    SUBCASE("Binary tree") {
        BinaryTreeNodePtr<int> cur = BinaryTreeNodeBuilder<int>().SetValue(1);
        BinaryTreeNodePtr<int> parent = BinaryTreeNodeBuilder<int>().SetValue(0).SetLeft(cur);
        BinaryTreeNodePtr<int> right = BinaryTreeNodeBuilder<int>().SetValue(2).SetParent(cur);

        CHECK(parent->_left == cur);
        CHECK(right->_parent == cur);
        CHECK(cur->_value == 1);

    }
}
