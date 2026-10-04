#include "Fixtures.hpp"

TEST_F(UniquePtr_Fixture, DereferenceValidPointer){
    EXPECT_EQ(**valid_ptr, 42);
    EXPECT_EQ((*arr_ptr)[1], 20);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка при разыменовании UniquePtr ---\n";
        std::cout << "Ожидалось значение 42 для одиночного указателя и 20 для массива.\n";
    }
}

TEST_F(UniquePtr_Fixture, ThrowsOnEmptyDereference){
    EXPECT_THROW(**empty_ptr, std::invalid_argument);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка проверки исключений ---\n";
        std::cout << "Ожидалось исключение std::invalid_argument при разыменовании нулевого указателя.\n";
    }
}

TEST_F(UniquePtr_Fixture, MoveSemanticsTransferOwnership){
    UniquePtr<int> moved_ptr = std::move(*valid_ptr); 
    
    EXPECT_EQ(*moved_ptr, 42);
    // Проверка без сокращений (!)
    EXPECT_EQ(static_cast<bool>(*valid_ptr), false);
    EXPECT_THROW(**valid_ptr, std::invalid_argument);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка перемещения UniquePtr ---\n";
        std::cout << "Ожидалось, что старый указатель обнулится после перемещения (move-конструктор должен забрать адрес и оставить nullptr).\n";
    }
}