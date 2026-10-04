#include "Fixtures.hpp"

TEST_F(SharedPtr_Fixture, CopyPreservesValue){
    SharedPtr<int> copy_ptr = *valid_ptr;
    EXPECT_EQ(*copy_ptr, 99);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка копирования SharedPtr (значение) ---\n";
        std::cout << "Копия не получила ожидаемое значение 99.\n";
    }
}

TEST_F(SharedPtr_Fixture, CopyMaintainsDonor){
    SharedPtr<int> copy_ptr = *valid_ptr;
    EXPECT_EQ(static_cast<bool>(*valid_ptr), true); 
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка копирования SharedPtr (состояние оригинала) ---\n";
        std::cout << "Оригинальный указатель ошибочно обнулился при копировании.\n";
    }
}

TEST_F(SharedPtr_Fixture, MemoryIsMutable){
    SharedPtr<int> copy_ptr = *valid_ptr;
    *copy_ptr = 100;
    EXPECT_EQ(**valid_ptr, 100); 
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка синхронизации SharedPtr ---\n";
        std::cout << "Изменение через копию не отразилось на оригинале. Ожидалось 100.\n";
    }
}

TEST_F(SharedPtr_Fixture, ThrowsOnEmpty){
    EXPECT_THROW(**empty_ptr, std::invalid_argument);
    if (testing::Test::HasFailure()){
        std::cout << "\n--- Ошибка проверки исключений SharedPtr ---\n";
        std::cout << "Ожидалось исключение std::invalid_argument при доступе к nullptr.\n";
    }
}