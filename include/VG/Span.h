#pragma once
#include <span>

template <typename T>
class Span : public std::span<T>
{
public:
    using std::span<T>::span;

    Span(std::initializer_list<T> list) requires std::is_const_v<T>
        : std::span<T>(list.begin(), list.size()) {}

    Span(T& element)
        : std::span<T>(&element, 1) {}

    Span(T&& element) requires std::is_const_v<T>
        : std::span<T>(&element, 1) {}
};