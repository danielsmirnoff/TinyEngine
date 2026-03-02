#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>

template<typename T>
class map {
    public:
        map() = default;
        ~map() = default;
        int add(T item);
        T get(int index);
        void remove(int index);
        void clear();
    private:
        int nextIndex = 0;
        std::unordered_map<int, T> list;
};