#include <iostream>
#include "DynamicArray.hpp"

using namespace std;

void createAndDestroyArray(){
    int raw_data[] ={10, 20, 30};
    DynamicArray<int> arr(raw_data); 

    for(size_t i = 0; i < arr.GetSize(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
} 

int main(){
    createAndDestroyArray();
    return 0;
}