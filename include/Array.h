#pragma once
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class Array
{
private:
    std::shared_ptr<T[]> data;
    size_t arr_size;
    size_t arr_capacity;

    void resize(size_t new_capacity)
    {
        std::shared_ptr<T[]> new_data = std::make_shared<T[]>(new_capacity);

        for (size_t i = 0; i < arr_size; ++i)
        {
            if constexpr (std::is_move_assignable_v<T>)
            {
                new_data[i] = std::move(data[i]);
            }
            else
            {
                new_data[i] = data[i];
            }
        }

        data = new_data;
        arr_capacity = new_capacity;
    }

public:
    Array() : data(nullptr), arr_size(0), arr_capacity(0) {}

    Array(const Array &other) : arr_size(other.arr_size), arr_capacity(other.arr_capacity)
    {
        data = std::make_shared<T[]>(arr_capacity);
        for (size_t i = 0; i < arr_size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    Array(Array &&other) noexcept
        : data(std::move(other.data)), arr_size(other.arr_size), arr_capacity(other.arr_capacity)
    {
        other.arr_size = 0;
        other.arr_capacity = 0;
    }

    ~Array() = default;

    void add(const T &element)
    {
        if (arr_size >= arr_capacity)
        {
            resize(arr_capacity == 0 ? 1 : arr_capacity * 2);
        }
        data[arr_size++] = element;
    }

    void add(T &&element)
    {
        if (arr_size >= arr_capacity)
        {
            resize(arr_capacity == 0 ? 1 : arr_capacity * 2);
        }
        data[arr_size++] = std::move(element);
    }

    void remove(size_t index)
    {
        if (index >= arr_size)
        {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < arr_size - 1; ++i)
        {
            data[i] = std::move(data[i + 1]);
        }
        --arr_size;
    }

    T &operator[](size_t index)
    {
        if (index >= arr_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= arr_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const { return arr_size; }
    size_t capacity() const { return arr_capacity; }

    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            arr_size = other.arr_size;
            arr_capacity = other.arr_capacity;
            data = std::make_shared<T[]>(arr_capacity);
            for (size_t i = 0; i < arr_size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array &operator=(Array &&other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            arr_size = other.arr_size;
            arr_capacity = other.arr_capacity;
            other.arr_size = 0;
            other.arr_capacity = 0;
        }
        return *this;
    }
};