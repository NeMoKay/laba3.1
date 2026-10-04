#include "Fixtures.hpp"

TEST_F(SharedPtr_Fixture, CopySemanticsAndReferenceCounting){
    SharedPtr<int> copy_ptr = *valid_ptr;
    
    EXPECT_EQ(*copy_ptr, 99);
    EXPECT_EQ(static_cast<bool>(*valid_ptr), true); 
    
    *copy_ptr = 100;
    EXPECT_EQ(**valid_ptr, 100); 
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка копирования SharedPtr ---\n";
        std::cout << "Ожидалось, что изменение данных через копию отразится на оригинале (ожидаемое значение 100).\n";
    }
}

TEST_F(SharedPtr_Fixture, ThrowsOnEmptyDereference){
    EXPECT_THROW(**empty_ptr, std::invalid_argument);
    
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка проверки исключений SharedPtr ---\n";
        std::cout << "Ожидалось исключение std::invalid_argument.\n";
    }
}