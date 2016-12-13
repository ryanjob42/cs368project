////////////////////////////////////////////////////////////////////////////////
// File Name:      Vector.hpp
//
// Author:         Ryan Job, Austin Abts
// CS email:       job@cs.wisc.edu, abts@cs.wisc.edu
//
// Description:    A custom vector class with a subset
//                 of features from std::vector
////////////////////////////////////////////////////////////////////////////////

#ifndef A6_VECTOR_HPP
#define A6_VECTOR_HPP

#include <cstdio>
#include <iostream>
#include <stdexcept>

/**
 * @brief A templated sequence container that encapsulates dynamic size arrays.
 */
template<typename T>
class Vector {
private:
    T *elems;
    std::size_t capacity;
    std::size_t size;
    static const std::size_t initialCapacity = 4;
    /* If you want to add methods, add them below this line */

    /* If you want to add methods, add them above this line */

public:
    /**
     * @brief Default Constructor.
     */
    Vector() {
        capacity = initialCapacity;
        size = 0;
        elems = new T[capacity];
    }

    /**
     * @brief Copy Constructor.
     * @param other The vector from which we should copy from.
     */
    Vector(const Vector &other) {
        elems = new T[capacity];
        capacity = other.capacity;
        size = other.size;
        for (int i = 0; i < size; ++i) {
            elems[i] = other.elems[i];
        }
    }

    /**
     * @brief Copy Assignment Operator.
     * @param other The vector on the RHS of the assignment.
     * @return A reference to the vector on the LHS.
     */
    Vector &operator=(const Vector &other) {
        if (this != &other) {
            capacity = other.capacity;
            size = other.size;
            delete[] elems;
            elems = new T[capacity];
            for (int k = 0; k < capacity; ++k) {
                elems[k] = other.elems[k];
            }
        }
    }

    /**
     * @brief Destructor.
     */
    ~Vector(){
        delete[] elems;
    }

    typedef T* iterator;
    typedef const T* const_iterator;

    /**
     * @brief Begin iterator.
     * @return An iterator to the first element.
     */
    iterator Begin() {
        return elems;
    }

    /**
     * @brief End iterator.
     * @return An iterator to one past the last element.
     */
    iterator End() {
        return elems + size;
    }

    /**
     * @brief Begin iterator.
     * @return A const iterator to the first element.
     */
    const_iterator Begin() const {
        return elems;
    }

    /**
     * @brief End iterator.
     * @return A const iterator to one past the last element.
     */
    const_iterator End() const {
        return elems + size;
    }

    /**
     * @brief Gets the number of elements that the container has currently allocated space for.
     * @return The number of elements that can be held in currently allocated storage.
     */
    std::size_t Capacity() const {
        return capacity;
    }

    /**
     * @brief Gets the number of elements.
     * @return The number of elements in the container.
     */
    std::size_t Size() const {
        return size;
    }

    /**
     * @brief Adds an element to the end.
     *        If there is no space to add an element, then the capacity of the vector is doubled..
     * @param elem The element to be added.
     */
    void Push_Back(T elem) {
        if (size == capacity) {
            capacity *= 2;
            T *newElems = new T[capacity];
            for (int k = 0; k < size; ++k) {
                newElems[k] = elems[k];
            }
            elems = newElems;
        }
        elems[size++] = elem;
    }

    /**
     * @brief Removes the last element of the container.
     *        The capacity of the vector is unchanged.
     *        If there are no elements in the container, then do nothing.
     */
    void Pop_Back() {
        size--;
    }

    /**
     * @brief Increases the capacity of the container to a value greater or equal to new_cap.
     *        If new_cap is greater than the current capacity(), new storage is allocated,
     *        otherwise the method does nothing.
     * @param new_cap new capacity of the container.
     */
    void Reserve(std::size_t new_cap) {
        if (new_cap > capacity) {
            capacity = new_cap;
            T *newelems = new T[capacity];
            for (int k = 0; k < size; ++k) {
                newelems[k] = elems[k];
            }
            elems = newelems;
        }
    }

    /**
     * @brief Overloaded array subscripting operator.
     * @param pos The position of the element to access.
     * @return A reference to the element at specified location pos.
     *         No bounds checking is performed.
     */
    T &operator[](std::size_t pos) {
        return elems[pos];
    }

    /**
     * @brief Const overload of the overloaded array subscripting operator.
     * @param pos The position of the element to access.
     * @return A const reference to the element at specified location pos.
     *         No bounds checking is performed.
     */
    const T &operator[](std::size_t pos) const {
        return elems[pos];
    }

    /**
     * @brief Access specified element with bounds checking.
     * @param pos The position of the element to access.
     * @return A reference to the element at specified location pos, with bounds checking.
     * @throw std::out_of_range if pos >= size.
     */
    T &At(std::size_t pos) {
        if (pos <= size) {
            return elems[pos];
        } else {
            throw std::out_of_range();
        }
    }

    /**
     * @brief Access specified element with bounds checking.
     * @param pos The position of the element to access.
     * @return A const reference to the element at specified location pos, with bounds checking.
     * @throw std::out_of_range if pos >= size.
     */
    const T &At(std::size_t pos) const {
        if (pos <= size) {
            return elems[pos];
        } else {
            throw std::out_of_range();
        }
    }

    /**
     * @brief Checks whether the container is empty.
     * @return true if the container is empty, false otherwise.
     */
    bool Empty() const {
        return size == 0;
    }

    /**
     * @brief Removes all elements from the container.
     *        Leaves the capacity of the vector unchanged.
     */
    void Clear() {
        size = 0;
    }

    /**
     * @brief Erases an element at pos.
     * @param pos Iterator to the element to remove.
     * @return Iterator following the last removed element.
     *         If the iterator pos refers to the last element, the end() iterator is returned.
     */
    iterator Erase(iterator pos) {
        while (pos != this.End()) {
            *pos = *(pos + 1);
            pos++;
        }
        --size;
    }
};

#endif //A6_VECTOR_HPP
