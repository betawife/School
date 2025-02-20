#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ���ֲ��Һ��������ز��ҳ���
int binarySearch(const vector<int>& studentIDs, int K) {
    int left = 0, right = studentIDs.size() - 1;
    int searchLength = 0; // ���ҳ���

    while (left <= right) {
        searchLength++; // ÿ�ν���ѭ������һ�β��ҳ���
        int mid = left + (right - left) / 2; // ��ֹ���

        if (studentIDs[mid] == K) {
            cout << "ѧ�� " << K << " �ҵ���λ��Ϊ: " << mid +1<< endl; //�ռ�λ�üǵ�תΪ�߼�λ��
            return searchLength;
        }
        if (studentIDs[mid] < K) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    cout << "ѧ�� " << K << " δ�ҵ���" << endl;
    return searchLength;
}

int main() {
    // ����༶30�˵�ѧ�ţ�������
    vector<int> studentIDs = { 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010,
                              1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020,
                              1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029, 1030 };

    // ����Ҫ���ҵ�ѧ��
    int K;
    cout << "������Ҫ���ҵ�ѧ��: ";
    cin >> K;

    // ���ö��ֲ��Һ���
    int searchLength = binarySearch(studentIDs, K);

    // ������ҳ���
    cout << "���ҳ���Ϊ: " << searchLength << endl;

    return 0;
}
