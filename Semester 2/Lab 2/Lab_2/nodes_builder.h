#pragma once
#include "nodes.h"

template<typename T>
class ListNodeBuilder {
private:
    ListNodePtr<T> to_build;
public:
    ListNodeBuilder() {
        Reset();
    }

    ListNodeBuilder<T>& SetValue(T value) {
        to_build->_value = std::move(value);
        return *this;
    }

    ListNodeBuilder<T>& SetNext(const ListNodePtr<T> next) {
        to_build->_next = next;
        return *this;
    }

    void Reset() {
        to_build = std::make_shared<ListNode<T>>();
    }

    operator ListNodePtr<T>() {
        auto res = to_build;
        Reset();
        return std::move(res);
    }
};


template<typename T>
class BinaryTreeNodeBuilder {
private:
    BinaryTreeNodePtr<T> to_build;
public:
    BinaryTreeNodeBuilder() {
        Reset();
    }

    BinaryTreeNodeBuilder<T>& SetValue(T value) {
        this->to_build->_value = std::move(value);
        return *this;
    }

    BinaryTreeNodeBuilder<T>& SetLeft(const BinaryTreeNodePtr<T> left){
        this->to_build->_left = left;
        return *this;
    }

    BinaryTreeNodeBuilder<T>& SetRight(const BinaryTreeNodePtr<T> right){
        this->to_build->_right = right;
        return *this;
    }

    BinaryTreeNodeBuilder<T>& SetParent(const BinaryTreeNodePtr<T> parent){
        this->to_build->_parent = parent;
        return *this;
    }

    void Reset() {
        to_build = std::make_shared<BinaryTreeNode<T>>();
    }

    operator BinaryTreeNodePtr<T>() {
        auto res = to_build;
        Reset();
        return std::move(res);
    }
};

template<typename T>
class RBTreeNodeBuilder {
private:
    RBTreeNodePtr<T> to_build;
public:
    RBTreeNodeBuilder() {
        Reset();
    }

    RBTreeNodeBuilder<T>& SetValue(T value) {
        this->to_build->_value = std::move(value);
        return *this;
    }

    RBTreeNodeBuilder<T>& SetLeft(const BinaryTreeNodePtr<T> left){
        this->to_build->_left = left;
        return *this;
    }

    RBTreeNodeBuilder<T>& SetRight(const BinaryTreeNodePtr<T> right){
        this->to_build->_right = right;
        return *this;
    }

    RBTreeNodeBuilder<T>& SetParent(const BinaryTreeNodePtr<T> parent){
        this->to_build->_parent = parent;
        return *this;
    }

    RBTreeNodeBuilder<T>& SetColor(Color color = Color::Black) {
        this->to_build->_color = color;
        return *this;
    }

    void Reset() {
        to_build = std::make_shared<RBTreeNode<T>>();
    }

    operator RBTreeNodePtr<T>() {
        auto res = to_build;
        Reset();
        return std::move(this->to_build);
    }
};
