#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

template <typename T> class Vector {
private:
    T* data;
    std::size_t vectorSize;
    std::size_t capacity;

    void resize(std::size_t newCapacity);

public:
    Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    void push_back(const T& value);
    void pop_back();
    void erase(std::size_t index); // New erase function

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;
    std::size_t getCapacity() const;
    bool isEmpty() const;
    void clear();
};

// Implementation of Vector class

template <typename T> Vector<T>::Vector() : data(nullptr), vectorSize(0), capacity(0) {}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data(new T[other.capacity]), vectorSize(other.vectorSize), capacity(other.capacity) {
    for (std::size_t i = 0; i < vectorSize; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T> Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        data = new T[other.capacity];
        vectorSize = other.vectorSize;
        capacity = other.capacity;
        for (std::size_t i = 0; i < vectorSize; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T> Vector<T>::~Vector() { delete[] data; }

template <typename T> void Vector<T>::push_back(const T& value) {
    if (vectorSize == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[vectorSize++] = value;
}

template <typename T> void Vector<T>::pop_back() {
    if (vectorSize > 0) {
        --vectorSize;
    } else {
        throw std::out_of_range("Vector is empty");
    }
}

template <typename T> void Vector<T>::erase(std::size_t index) {
    if (index >= vectorSize) {
        throw std::out_of_range("Index out of bounds");
    }
    // Shift elements to the left to fill the gap
    for (std::size_t i = index; i < vectorSize - 1; ++i) {
        data[i] = data[i + 1];
    }
    --vectorSize; // Decrease size after removing element
}

template <typename T> T& Vector<T>::operator[](std::size_t index) {
    if (index >= vectorSize) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T> const T& Vector<T>::operator[](std::size_t index) const {
    if (index >= vectorSize) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T> std::size_t Vector<T>::size() const { return vectorSize; }

template <typename T> std::size_t Vector<T>::getCapacity() const { return capacity; }

template <typename T> bool Vector<T>::isEmpty() const { return vectorSize == 0; }

template <typename T> void Vector<T>::clear() { vectorSize = 0; }

template <typename T> void Vector<T>::resize(std::size_t newCapacity) {
    T* newData = new T[newCapacity];
    for (std::size_t i = 0; i < vectorSize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

#endif // VECTOR_H
