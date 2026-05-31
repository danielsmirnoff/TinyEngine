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

        typename std::unordered_map<int, T>::iterator begin() { return list.begin(); }
        typename std::unordered_map<int, T>::iterator end()   { return list.end(); }
    private:
        int nextIndex = 0;
        std::unordered_map<int, T> list;
};