#pragma once
#include "nodes_builder.h"

template<typename T>
class AbstractFactory {
public:
    virtual BaseNodePtr<T> Create() = default;
    virtual ~AbstractFactory() = default;
}
