#include "Fixtures.hpp"

TEST_F(DynamicArray_Fixture, GetValidElements){
    EXPECT_EQ(valid_arr->GetSize(), 5);
    EXPECT_EQ(valid_arr->Get(0), 1);
    EXPECT_EQ(valid_arr->Get(4), 5);
    EXPECT_EQ((*valid_arr)[2], 3); 
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка доступа DynamicArray ---\n";
        std::cout << "Размер должен быть 5. Ожидаемые элементы: 1, 2, 3, 4, 5.\n";
    }
}

TEST_F(DynamicArray_Fixture, ThrowsOnOutOfBounds){
    EXPECT_THROW(empty_arr->Get(0), std::out_of_range);
    EXPECT_THROW(valid_arr->Get(10), std::out_of_range);
    EXPECT_THROW(valid_arr->Set(5, 10), std::out_of_range);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка исключений DynamicArray ---\n";
        std::cout << "Ожидалось исключение std::out_of_range при выходе за пределы массива.\n";
    }
}

TEST_F(DynamicArray_Fixture, CopyConstructorDeepCopies){
    DynamicArray<int> copy_arr(*valid_arr);
    
    copy_arr.Set(0, 999);
    EXPECT_EQ(copy_arr.Get(0), 999);
    EXPECT_EQ(valid_arr->Get(0), 1);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка глубокого копирования DynamicArray ---\n";
        std::cout << "Изменение копии не должно влиять на оригинальный массив. Ожидалось значение оригинала: 1.\n";
    }
}