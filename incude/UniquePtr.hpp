#pragma once
#include <iostream>

template <typename T>
class UniquePtr{
private:
    T* ptr = nullptr;

    template <typename T1>
    friend class UniquePtr;
public:

    UniquePtr(T *new_ptr = nullptr);

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    ~UniquePtr();

    T& operator*() const;
    T* operator->() const;
    operator bool() const;
    
    T* get_address() const;

    template <typename T1>
    UniquePtr(UniquePtr<T1>&& other) noexcept;

    template <typename T1>
    UniquePtr& operator=(UniquePtr<T1>&& other) noexcept;

};

template <typename T>
UniquePtr<T>::UniquePtr(T *new_ptr) : ptr(new_ptr){};

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept{
    ptr = other.ptr;
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept{
    if(this != &other){
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T>::~UniquePtr(){
    delete ptr;
}

template <typename T>
T& UniquePtr<T>::operator*() const{
    if (ptr == nullptr){
        throw std::invalid_argument("Ошибка доступа: нулевой UniquePtr");
    }
    return *ptr;
}

template <typename T>
T* UniquePtr<T>::operator->() const{
    if (ptr == nullptr){
        throw std::invalid_argument("Ошибка доступа: нулевой UniquePtr");
    }
    return ptr;
}

template <typename T>
UniquePtr<T>::operator bool() const{
    if(ptr == nullptr){
        return 0;
    }
    else{
        return 1;
    }
}

template <typename T>
T* UniquePtr<T>::get_address() const{
    return ptr;
}

template<typename T>
template<typename T1>
UniquePtr<T>::UniquePtr(UniquePtr<T1>&& other) noexcept{
    ptr = static_cast<T*>(other.ptr);
    other.ptr = nullptr;
    
}

template<typename T>
template<typename T1>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T1>&& other) noexcept{
    delete ptr;
    ptr = static_cast<T*>(other.ptr);
    other.ptr = nullptr;
    return *this;
}




template <typename T>
class UniquePtr<T[]>{
private:
    T* ptr = nullptr;

    template <typename T1>
    friend class UniquePtr;
public:

    UniquePtr(T *new_ptr = nullptr);

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    ~UniquePtr();

    T& operator[](size_t index) const;
    operator bool() const;
    
    T* get_address() const;

    template <typename T1>
    UniquePtr(UniquePtr<T1[]>&& other) noexcept;

    template <typename T1>
    UniquePtr& operator=(UniquePtr<T1[]>&& other) noexcept;

};

template <typename T>
UniquePtr<T[]>::UniquePtr(T *new_ptr) : ptr(new_ptr){};

template <typename T>
UniquePtr<T[]>::UniquePtr(UniquePtr&& other) noexcept{
    ptr = other.ptr;
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T[]>& UniquePtr<T[]>::operator=(UniquePtr&& other) noexcept{
    if(this != &other){
        delete[] ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T[]>::~UniquePtr(){
    delete[] ptr;
}

template <typename T>
T& UniquePtr<T[]>::operator[](size_t index) const{
    if (ptr == nullptr){
        throw std::invalid_argument("Обращение к пустому массиву UniquePtr");
    }
    return ptr[index];
}

template <typename T>
UniquePtr<T[]>::operator bool() const{
    if(ptr == nullptr){
        return 0;
    }
    else{
        return 1;
    }
}

template <typename T>
T* UniquePtr<T[]>::get_address() const{
    return ptr;
}

template<typename T>
template<typename T1>
UniquePtr<T[]>::UniquePtr(UniquePtr<T1[]>&& other) noexcept{
    ptr = static_cast<T*>(other.ptr);
    other.ptr = nullptr;
    
}

template<typename T>
template<typename T1>
UniquePtr<T[]>& UniquePtr<T[]>::operator=(UniquePtr<T1[]>&& other) noexcept{
    delete[] ptr;
    ptr = static_cast<T*>(other.ptr);
    other.ptr = nullptr;
    return *this;
}