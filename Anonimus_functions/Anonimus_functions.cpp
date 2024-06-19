#include <iostream>
#include <vector>
#include <thread>
#include <locale>
#include <codecvt>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;

        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }

private:
    void Merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            arr[k++] = left[i++];
        }
        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    std::locale::global(std::locale(""));

    std::vector<int> arr(10);

    std::wcout << L"Введите 10 целых чисел, нажимая Enter после каждого:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::wcin >> arr[i];
    }

    MergeSort sorter;
    std::thread mergeSortThread([&sorter, &arr]() {
        sorter.Sort(arr);
        });

    mergeSortThread.join();

    std::wcout << L"Отсортированный массив: ";
    for (const int& num : arr) {
        std::wcout << num << " ";
    }
    std::wcout << std::endl;

    return 0;
}
