#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>
class Myarray {
public:
	Myarray(int capacity) {                   //�вι���
		this->capacity = capacity;
		this->a_size = 0;
		this->p = new T[this->capacity]; //������������
		cout << "�вι���" << endl;
	}

	Myarray(const Myarray& arr) {             //��������
		this->capacity = arr.capacity;
		this->a_size = arr.a_size;
		//this->p = arr.p;
		this->p = new T[arr.capacity];
		for (int i = 0; i < this->a_size; i++) {  //����arr����
			this->p[i] = arr.p[i];
		}
		cout << "��������" << endl;
	}

	Myarray& operator=(const Myarray& arr)   //��������أ���ֹǳ����
	{
		if (this->p != NULL) {
			delete[] this->p;
			this->p = NULL;
			this->capacity = 0;
			this->a_size = 0;
		}
		this->capacity = arr.capacity;
		this->a_size = arr.a_size;
		this->p = new T[arr.capacity];
		for (int i = 0; i < this->a_size; i++) {
			this->p[i] = arr.p[i];
		}
		return *this;
	}

	~Myarray() {
		if (this->p != NULL) { delete[] this->p; this->p = NULL; }
		cout << "����" << endl;
	}
private:
	T* p; //ָ���������
	int capacity;
	int a_size;
};

void main() {
	Myarray<int> arr1(5);
	Myarray<int>arr2(arr1);
	Myarray<int>arr3 = arr2;
}