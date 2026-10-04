#include "Fixtures.hpp"

TEST_F(UniquePtr_Fixture, DereferenceSinglePointer){
    EXPECT_EQ(**valid_ptr, 42);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка при разыменовании одиночного UniquePtr ---\n";
        std::cout << "Ожидалось значение 42.\n";
    }
}

TEST_F(UniquePtr_Fixture, DereferenceArrayPointer){
    EXPECT_EQ((*arr_ptr)[1], 20);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка при разыменовании массива UniquePtr ---\n";
        std::cout << "Ожидалось значение 20 по индексу 1.\n";
    }
}

TEST_F(UniquePtr_Fixture, ThrowsOnEmptyDereference){
    EXPECT_THROW(**empty_ptr, std::invalid_argument);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка проверки исключений ---\n";
        std::cout << "Ожидалось исключение std::invalid_argument при обращении к nullptr.\n";
    }
}

TEST_F(UniquePtr_Fixture, MoveTransfersValue){
    UniquePtr<int> moved_ptr = std::move(*valid_ptr); 
    EXPECT_EQ(*moved_ptr, 42);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка перемещения UniquePtr (значение) ---\n";
        std::cout << "Новый указатель не получил ожидаемое значение 42.\n";
    }
}

TEST_F(UniquePtr_Fixture, MoveClearsDonorPointer){
    UniquePtr<int> moved_ptr = std::move(*valid_ptr); 
    EXPECT_EQ(static_cast<bool>(*valid_ptr), false);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка обнуления донора ---\n";
        std::cout << "Указатель не был обнулен (не стал nullptr) после передачи владения.\n";
    }
}

TEST_F(UniquePtr_Fixture, MoveThrowsOnDonorAccess){
    UniquePtr<int> moved_ptr = std::move(*valid_ptr); 
    EXPECT_THROW(**valid_ptr, std::invalid_argument);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка доступа после перемещения ---\n";
        std::cout << "Разыменование перемещенного указателя должно вызывать std::invalid_argument.\n";
    }
}