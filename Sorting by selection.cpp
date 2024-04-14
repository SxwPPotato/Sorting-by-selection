#include <iostream>
#include <vector>
#include <future>

void Selection_sorting(std::vector<int>& vec, std::promise<int> valPromise) {
    int pos;
   
    for (int j = 0; j < vec.size(); ++j) {
        bool selector = false;
        int min = vec[j];
        for (int i = j + 1; i < vec.size(); ++i) {
            if (min > vec[i]) {
                min = vec[i];
                pos = i;
                selector = true;
            }
            7, 4, 7, 2, 9, 1, 6, 5;
            
        }
        if (selector) {
            int tmp = vec[j];
            vec[j] = min;
            vec[pos] = tmp;
        }
        
    }
    for (int j = 0; j < vec.size(); ++j) {
        valPromise.set_value(vec[j]);
    }
}

int main()
{
    setlocale(LC_ALL, "russian");
    std::vector<int> vec{ 7,4,7,2,9,1,6,5 };


    std::promise<int> valPromise;

    auto ValPromiseFuture(valPromise.get_future());

    auto SortFuture{ std::async(Selection_sorting,std::ref(vec),std::move(valPromise)) };
    
    const auto val{ ValPromiseFuture.get() };
    
    std::cout << "Отсортированый масив: ";
    for (int el : vec) {
        std::cout << el << " ";
    }


    return 0;
}
