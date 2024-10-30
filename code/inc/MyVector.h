#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

#include <cstdlib>
#include <iostream>

template <typename T> class MyVector {
public:
    MyVector(size_t initialSize = 10);
    ~MyVector();

    void push_back(const T& value);
    T& operator[](size_t index);
    size_t size() const;
    void clear();

private:
    T* data;
    size_t capacity;
    size_t currentSize;

    void resize(size_t newCapacity);
};

template <typename T> MyVector<T>::MyVector(size_t initialSize) : capacity(initialSize), currentSize(0) {
    data = static_cast<T*>(malloc(capacity * sizeof(T)));
    if (!data) {
        throw std::bad_alloc();
    }
}

template <typename T> MyVector<T>::~MyVector() {
    clear();
    free(data);
}

template <typename T> void MyVector<T>::push_back(const T& value) {
    if (currentSize >= capacity) {
        resize(capacity * 2);
    }
    data[currentSize++] = value;
}

template <typename T> T& MyVector<T>::operator[](size_t index) {
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T> size_t MyVector<T>::size() const { return currentSize; }

template <typename T> void MyVector<T>::clear() { currentSize = 0; }

template <typename T> void MyVector<T>::resize(size_t newCapacity) {
    T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
    if (!newData) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < currentSize; ++i) {
        newData[i] = data[i];
    }
    free(data);
    data = newData;
    capacity = newCapacity;
}

#endif // CUSTOMVECTOR_H
