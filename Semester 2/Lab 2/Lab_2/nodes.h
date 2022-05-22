#pragma once
#include <memory>

template<typename T>
struct BaseNode {
    BaseNode() = default;
    BaseNode(T value) : _value(std::move(value)) {}
    virtual ~BaseNode() = default;
    T _value;
};

template<typename T>
struct ListNode : public BaseNode<T> {
    std::shared_ptr<ListNode<T>> _next = nullptr;
};

enum class Color {
    Red,
    Black
};

template<typename T>
struct BinaryTreeNode : public BaseNode<T> {
    std::shared_ptr<BinaryTreeNode<T>> _left   = nullptr;
    std::shared_ptr<BinaryTreeNode<T>> _right  = nullptr;
    std::shared_ptr<BinaryTreeNode<T>> _parent = nullptr;
};

template<typename T>
struct RBTreeNode : public BinaryTreeNode<T> {
    Color _color;
};

template<typename T>
using BaseNodePtr = std::shared_ptr<BaseNode<T>>;

template<typename T>
using ListNodePtr = std::shared_ptr<ListNode<T>>;

template<typename T>
using BinaryTreeNodePtr = std::shared_ptr<BinaryTreeNode<T>>;

template<typename T>
using RBTreeNodePtr = std::shared_ptr<RBTreeNode<T>>;





