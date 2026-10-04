#pragma once
#include <iostream>


template <typename T>
class SharedPtr{
private:
    T* ptr = nullptr;
    size_t* count = nullptr;

    template <typename T1>
    friend class SharedPtr;

public:
    SharedPtr(T* new_ptr = nullptr);

    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    ~SharedPtr();

    T& operator*() const;
    T* operator->() const;
    operator bool() const;

    T* get_address() const;

    template <typename T1>
    SharedPtr(const SharedPtr<T1>& other);

    template <typename T1>
    SharedPtr(SharedPtr<T1>&& other) noexcept;

    template <typename T1>
    SharedPtr& operator=(const SharedPtr<T1>& other);
    template <typename T1>
    SharedPtr& operator=(SharedPtr<T1>&& other) noexcept;



};

template <typename T>
SharedPtr<T>::SharedPtr(T* new_ptr){
    ptr = new_ptr;
    if(ptr != nullptr){
        count = new size_t(1);
    }
    else{
        count = nullptr;
    }
}
    
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other){
    ptr = other.ptr;
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept{
    ptr = other.ptr;
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;

}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other){
    if(&other != this){
        if(count != nullptr){
            (*count)--;
            if(*count == 0){
                delete ptr;
                delete count;
            }
        }

        ptr = other.ptr;
        count = other.count;
        if(count != nullptr){
            (*count)++;
        }
    }
    return *this;

}



template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept{
    if(&other != this){
        if(count != nullptr){
            (*count)--;
            if(*count == 0){
                delete ptr;
                delete count;
            }
        }

        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr; 
        other.count = nullptr;
    }
    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr(){
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete ptr;
            delete count;
        }
    }
}

template <typename T>
T& SharedPtr<T>::operator*() const{
    if (ptr == nullptr){
        throw std::invalid_argument("Ошибка доступа: нулевой SharedPtr");
    }
    return *ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const{
    if (ptr == nullptr){
        throw std::invalid_argument("Ошибка доступа: нулевой SharedPtr");
    }
    return ptr;
}

template <typename T>
T* SharedPtr<T>::get_address() const{
    return ptr;
}

template <typename T>
SharedPtr<T>::operator bool() const{
    if(ptr != nullptr){
        return 1;
    }
    else{
        return 0;
    }
}

template <typename T>
template <typename T1>
SharedPtr<T>::SharedPtr(const SharedPtr<T1>& other){
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }

}

template<typename T>
template<typename T1>
SharedPtr<T>::SharedPtr(SharedPtr<T1>&& other) noexcept{
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;
    
}

template <typename T>
template <typename T1>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T1>& other){
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete ptr;
            delete count;
        }
    }
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }
    return *this;



}


template<typename T>
template<typename T1>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T1>&& other) noexcept{
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete ptr;
            delete count;
        }
    }
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;
    return *this;
}















template <typename T>
class SharedPtr<T[]>{
private:
    T* ptr = nullptr;
    size_t* count = nullptr;

    template <typename T1>
    friend class SharedPtr;

public:
    SharedPtr(T* new_ptr = nullptr);

    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    ~SharedPtr();

    T& operator[](size_t index) const;
    operator bool() const;

    T* get_address() const;

    template <typename T1>
    SharedPtr(const SharedPtr<T1[]>& other);

    template <typename T1>
    SharedPtr(SharedPtr<T1[]>&& other) noexcept;

    template <typename T1>
    SharedPtr& operator=(const SharedPtr<T1[]>& other);
    template <typename T1>
    SharedPtr& operator=(SharedPtr<T1[]>&& other) noexcept;

};

template <typename T>
SharedPtr<T[]>::SharedPtr(T* new_ptr){
    ptr = new_ptr;
    if(ptr != nullptr){
        count = new size_t(1);
    }
    else{
        count = nullptr;
    }
}
    
template <typename T>
SharedPtr<T[]>::SharedPtr(const SharedPtr& other){
    ptr = other.ptr;
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }
}

template <typename T>
SharedPtr<T[]>::SharedPtr(SharedPtr&& other) noexcept{
    ptr = other.ptr;
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;

}

template <typename T>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(const SharedPtr& other){
    if(&other != this){
        if(count != nullptr){
            (*count)--;
            if(*count == 0){
                delete[] ptr;
                delete count;
            }
        }

        ptr = other.ptr;
        count = other.count;
        if(count != nullptr){
            (*count)++;
        }
    }
    return *this;

}

template <typename T>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(SharedPtr&& other) noexcept{
    if(&other != this){
        if(count != nullptr){
            (*count)--;
            if(*count == 0){
                delete[] ptr;
                delete count;
            }
        }

        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr; 
        other.count = nullptr;
    }
    return *this;
}

template <typename T>
SharedPtr<T[]>::~SharedPtr(){
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete[] ptr;
            delete count;
        }
    }
}

template <typename T>
T& SharedPtr<T[]>::operator[](size_t index) const{
    if (ptr == nullptr){
        throw std::invalid_argument("Обращение к пустому массиву SharedPtr");
    }
    return ptr[index];
}

template <typename T>
T* SharedPtr<T[]>::get_address() const{
    return ptr;
}

template <typename T>
SharedPtr<T[]>::operator bool() const{
    if(ptr != nullptr){
        return 1;
    }
    else{
        return 0;
    }
}

template <typename T>
template <typename T1>
SharedPtr<T[]>::SharedPtr(const SharedPtr<T1[]>& other){
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }

}

template<typename T>
template<typename T1>
SharedPtr<T[]>::SharedPtr(SharedPtr<T1[]>&& other) noexcept{
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;
    
}

template <typename T>
template <typename T1>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(const SharedPtr<T1[]>& other){
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete[] ptr;
            delete count;
        }
    }
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    if(count != nullptr){
        (*count)++;
    }
    return *this;

}

template<typename T>
template<typename T1>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(SharedPtr<T1[]>&& other) noexcept{
    if(count != nullptr){
        (*count)--;
        if(*count == 0){
            delete[] ptr;
            delete count;
        }
    }
    ptr = static_cast<T*>(other.ptr);
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;
    return *this;
}