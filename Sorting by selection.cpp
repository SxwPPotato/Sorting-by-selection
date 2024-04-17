#include <iostream>
#include <vector>
#include <future>

void min_func(std::vector<int>& vec , int pos_j, int & pos, bool & selector , int & min, std::promise<int>& valPromise) {
    selector = false;
    min = vec[pos_j];
    for (int i = pos_j + 1; i < vec.size(); ++i) {
        if (min > vec[i]) {
            min = vec[i];
            pos = i;
            selector = true;
        }

    }
    valPromise.set_value(min);
}


void Selection_sorting(std::vector<int>& vec) {
    int pos;
    bool selector;
    int min;

    for (int j = 0; j < vec.size(); ++j) {
        std::promise<int> valPromise;
        auto ValPromiseFuture(valPromise.get_future());

        auto SortFuture{ std::async(min_func,std::ref(vec),j, std::ref(pos), std::ref(selector), std::ref(min), std::ref(valPromise) ) };
        const auto val{ ValPromiseFuture.get() };

        if (selector) {
            int tmp = vec[j];
            vec[j] = min;
            vec[pos] = tmp;
        }
        
    }
}

int main()
{
    setlocale(LC_ALL, "russian");
    std::vector<int> vec{ 7,4,7,2,9,1,6,5 };

    Selection_sorting(vec);
    
    std::cout << "Отсортированый масив: ";
    for (int el : vec) {
        std::cout << el << " ";
    }


    return 0;
}
