#include "Fixtures.hpp"

TEST_F(DynamicArray_Fixture, SizeIsCorrect){
    EXPECT_EQ(valid_arr->GetSize(), 5);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Размер) ---\n";
        std::cout << "Ожидаемый размер: 5. Фактический: " << valid_arr->GetSize() << "\n";
    }
}

TEST_F(DynamicArray_Fixture, GetReturnsCorrect){
    EXPECT_EQ(valid_arr->Get(0), 1);
    EXPECT_EQ(valid_arr->Get(4), 5);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Метод Get) ---\n";
        std::cout << "Несовпадение значений по краям массива (ожидалось 1 и 5).\n";
    }
}

TEST_F(DynamicArray_Fixture, OperatorBrackets){
    EXPECT_EQ((*valid_arr)[2], 3); 
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Оператор []) ---\n";
        std::cout << "Неверное значение по индексу 2 (ожидалось 3).\n";
    }
}

TEST_F(DynamicArray_Fixture, ThrowsOnEmptyAccess){
    EXPECT_THROW(empty_arr->Get(0), std::out_of_range);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Исключения) ---\n";
        std::cout << "Обращение к пустому массиву не вызвало std::out_of_range.\n";
    }
}

TEST_F(DynamicArray_Fixture, ThrowsOnOutOfBoundsRead){
    EXPECT_THROW(valid_arr->Get(10), std::out_of_range);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Исключения чтения) ---\n";
        std::cout << "Чтение за пределами массива не вызвало std::out_of_range.\n";
    }
}

TEST_F(DynamicArray_Fixture, ThrowsOnOutOfBoundsWrite){
    EXPECT_THROW(valid_arr->Set(5, 10), std::out_of_range);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка DynamicArray (Исключения записи) ---\n";
        std::cout << "Запись за пределами массива не вызвала std::out_of_range.\n";
    }
}

TEST_F(DynamicArray_Fixture, DeepCopyIsIndependent){
    DynamicArray<int> copy_arr(*valid_arr);
    copy_arr.Set(0, 999);
    EXPECT_EQ(valid_arr->Get(0), 1);
    EXPECT_EQ(copy_arr.Get(0), 999);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка глубокого копирования DynamicArray ---\n";
        std::cout << "Изменение копии повлияло на оригинал. Память не была изолирована.\n";
    }
}