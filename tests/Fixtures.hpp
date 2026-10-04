#pragma once

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "DynamicArray.hpp"

class UniquePtr_Fixture : public testing::Test{
protected:
    UniquePtr<int>* empty_ptr;
    UniquePtr<int>* valid_ptr;
    UniquePtr<int[]>* arr_ptr;

    void SetUp() override{
        empty_ptr = new UniquePtr<int>();
        valid_ptr = new UniquePtr<int>(new int(42));
        
        int* raw_arr = new int[3]{10, 20, 30};
        arr_ptr = new UniquePtr<int[]>(raw_arr);
    }

    void TearDown() override{
        delete empty_ptr;
        delete valid_ptr;
        delete arr_ptr;
    }
};

class SharedPtr_Fixture : public testing::Test{
protected:
    SharedPtr<int>* empty_ptr;
    SharedPtr<int>* valid_ptr;
    SharedPtr<int[]>* arr_ptr;

    void SetUp() override{
        empty_ptr = new SharedPtr<int>();
        valid_ptr = new SharedPtr<int>(new int(99));
        
        int* raw_arr = new int[2]{55, 66};
        arr_ptr = new SharedPtr<int[]>(raw_arr);
    }

    void TearDown() override{
        delete empty_ptr;
        delete valid_ptr;
        delete arr_ptr;
    }
};

class DynamicArray_Fixture : public testing::Test{
protected:
    DynamicArray<int>* empty_arr;
    DynamicArray<int>* valid_arr;

    void SetUp() override{
        empty_arr = new DynamicArray<int>();
        
        int raw_data[] ={1, 2, 3, 4, 5};
        valid_arr = new DynamicArray<int>(raw_data);
    }

    void TearDown() override{
        delete empty_arr;
        delete valid_arr;
    }
};