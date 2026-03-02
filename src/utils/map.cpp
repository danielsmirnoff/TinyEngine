#include "map.h"

template <typename T>
int map<T>::add(T item) {
    list[nextIndex] = item;
    return nextIndex++;
}

template <typename T>
T map<T>::get(int index) {
    return list[index];
}

template <typename T>
void map<T>::remove(int index) {
    list.erase(index);
}

template <typename T>
void map<T>::clear() {
    list.clear();
}