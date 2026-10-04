
#pragma once

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "UniquePtr.hpp" 


template <typename T>
class DynamicArray{
private:
    UniquePtr<T[]> data; 
    size_t size;
public:
    DynamicArray();
    DynamicArray(size_t count);
    
    template <size_t N>
    DynamicArray(T (&arr)[N]); 
    DynamicArray(const DynamicArray<T>& array);

    T Get(size_t index) const;
    void Set(size_t index, T value);
    void Resize(size_t newSize);
    size_t GetSize() const;
    T operator[](size_t index) const;
    DynamicArray<T>& operator=(const DynamicArray<T>& other);

    ~DynamicArray();
};

template <typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0){}

template <typename T>
DynamicArray<T>::DynamicArray(size_t count) : size(count){
    if (count > 0){
        data = UniquePtr<T[]>(new T[count]);
    }
    else{
        data = UniquePtr<T[]>(nullptr);
    }
}

template <typename T>
template <size_t N>
DynamicArray<T>::DynamicArray(T (&arr)[N]) : DynamicArray(N){
    for(size_t i = 0; i < size; i++){
        data[i] = arr[i];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& array) : size(array.size){
    if (array.size > 0){
        data = UniquePtr<T[]>(new T[array.size]);
    }
    else{
        data = UniquePtr<T[]>(nullptr);
    }
    for(size_t i = 0; i < size; i++){
        data[i] = array.data[i];
    }
}

template <typename T>
T DynamicArray<T>::Get(size_t index) const{
    if(index >= size){
        throw std::out_of_range("Ошибка индекса"); 
    }
    return data[index];
}

template <typename T>
void DynamicArray<T>::Set(size_t index, T value){
    if(index >= size){
        throw std::out_of_range("Ошибка индекса");
    }
    data[index] = value;
}

template <typename T>
void DynamicArray<T>::Resize(size_t newSize){
    UniquePtr<T[]> new_data(nullptr);
    
    if (newSize > 0){
        new_data = UniquePtr<T[]>(new T[newSize]);
    }
    
    if (size != 0 && newSize != 0){
        size_t elements_to_copy;
        if (newSize < size){
            elements_to_copy = newSize;
        }
        else{
            elements_to_copy = size;
        }
        
        for (size_t i = 0; i < elements_to_copy; i++){
            new_data[i] = data[i];
        }
    }
    
    data = std::move(new_data); 
    size = newSize;
}

template <typename T>
size_t DynamicArray<T>::GetSize() const{
    return size;
}

template <typename T>
T DynamicArray<T>::operator[](size_t index) const{
    return Get(index); 
}

template <typename T>
DynamicArray<T>::~DynamicArray(){
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other){
    if (this != &other){
        UniquePtr<T[]> new_data(nullptr);
        
        if (other.size > 0){
            new_data = UniquePtr<T[]>(new T[other.size]);
        }
        
        for(size_t i = 0; i < other.size; i++){
            new_data[i] = other.data[i];
        }
        
        data = std::move(new_data);
        size = other.size;
    }
    return *this;
}