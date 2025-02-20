#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// ֱ�Ӳ�������
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ��ѡ������
void selectionSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// ð������
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ��������
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) --j;
        arr[i] = arr[j];
        while (i < j && arr[i] <= pivot) ++i;
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

// ������
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ϣ������
void shellSort(vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < arr.size(); ++i) {
            int temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// ��ʱ������������
template <typename Func>
void testSort(const string& name, Func sortFunc, vector<int> arr, vector<int>& result) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    cout << name << " ��ʱ: "
        << duration_cast<microseconds>(end - start).count()
        << " ΢��" << endl;

    // ����������
    result = arr;
}

// ��ӡ����
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// ������
int main() {
    // �������30������
    srand(time(0));
    vector<int> arr(30);
    for (int& num : arr) {
        num = rand() % 100; // ���ɷ�Χ��0-99�������
    }

    cout << "ԭʼ����: ";
    printArray(arr);

    vector<int> result;

    // ���Բ�ͬ�����㷨����¼������
    testSort("ֱ�Ӳ�������", insertionSort, arr, result);
    testSort("��ѡ������", selectionSort, arr, result);
    testSort("ð������", bubbleSort, arr, result);
    testSort("��������", [&](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr, result);
    testSort("������", heapSort, arr, result);
    testSort("ϣ������", shellSort, arr, result);

    // �������������
    cout << "\n����������: ";
    printArray(result);

    return 0;
}
