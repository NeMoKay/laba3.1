#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "DynamicArray.hpp"

const size_t LOAD_SIZE = 1000000;

TEST(LoadTest, CompareArrays){
    auto start_custom = std::chrono::high_resolution_clock::now();
    DynamicArray<int> custom_array;
    custom_array.Resize(LOAD_SIZE);
    for (size_t index = 0; index < LOAD_SIZE; index++){
        custom_array.Set(index, index);
    }
    auto end_custom = std::chrono::high_resolution_clock::now();
    double time_custom = std::chrono::duration<double, std::milli>(end_custom - start_custom).count();

    auto start_standard = std::chrono::high_resolution_clock::now();
    std::vector<int> standard_array;
    standard_array.resize(LOAD_SIZE);
    for (size_t index = 0; index < LOAD_SIZE; index++){
        standard_array[index] = index;
    }
    auto end_standard = std::chrono::high_resolution_clock::now();
    double time_standard = std::chrono::duration<double, std::milli>(end_standard - start_standard).count();

    std::cout << "\n--- Сравнение массивов (выделение и запись " << LOAD_SIZE << " элементов) ---\n";
    std::cout << "Мой DynamicArray: " << time_custom << " ms\n";
    std::cout << "std::vector:      " << time_standard << " ms\n";
}

TEST(LoadTest, CompareUniquePtr){
    auto start_custom = std::chrono::high_resolution_clock::now();
    UniquePtr<int[]> custom_unique(new int[LOAD_SIZE]);
    for (size_t index = 0; index < LOAD_SIZE; index++){
        custom_unique[index] = index;
    }
    UniquePtr<int[]> moved_custom = std::move(custom_unique);
    auto end_custom = std::chrono::high_resolution_clock::now();
    double time_custom = std::chrono::duration<double, std::milli>(end_custom - start_custom).count();


    auto start_standard = std::chrono::high_resolution_clock::now();
    std::unique_ptr<int[]> standard_unique(new int[LOAD_SIZE]);
    for (size_t index = 0; index < LOAD_SIZE; index++){
        standard_unique[index] = index;
    }
    std::unique_ptr<int[]> moved_standard = std::move(standard_unique);
    auto end_standard = std::chrono::high_resolution_clock::now();
    double time_standard = std::chrono::duration<double, std::milli>(end_standard - start_standard).count();

    std::cout << "\n--- Сравнение UniquePtr (выделение, запись и перемещение) ---\n";
    std::cout << "Мой UniquePtr:    " << time_custom << " ms\n";
    std::cout << "std::unique_ptr:  " << time_standard << " ms\n";
}

TEST(LoadTest, CompareSharedPtr){
    SharedPtr<int> custom_shared(new int(100));
    auto start_custom = std::chrono::high_resolution_clock::now();
    for (size_t index = 0; index < LOAD_SIZE; index++){
        SharedPtr<int> copy_shared = custom_shared;
    }
    auto end_custom = std::chrono::high_resolution_clock::now();
    double time_custom = std::chrono::duration<double, std::milli>(end_custom - start_custom).count();

    std::shared_ptr<int> standard_shared = std::make_shared<int>(100);
    auto start_standard = std::chrono::high_resolution_clock::now();
    for (size_t index = 0; index < LOAD_SIZE; index++){
        std::shared_ptr<int> copy_standard = standard_shared;
    }
    auto end_standard = std::chrono::high_resolution_clock::now();
    double time_standard = std::chrono::duration<double, std::milli>(end_standard - start_standard).count();

    std::cout << "\n--- Сравнение SharedPtr (миллион копирований счетчика ссылок) ---\n";
    std::cout << "Мой SharedPtr:    " << time_custom << " ms\n";
    std::cout << "std::shared_ptr:  " << time_standard << " ms\n";
}