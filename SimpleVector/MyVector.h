#pragma once
template<typename T>
class MyVector {
public:
	typedef T value;
	typedef T* iterator;//迭代器
	typedef T& reference;

public:


	MyVector(int len = 0) :m_len(len), m_Data(nullptr), start(nullptr), pos(0)
	{
		if (len > 0)
		{
			m_Data = new value[len];
			start = m_Data;
		}

	}

	~MyVector()
	{
		delete[] m_Data;
	}

	void push_back(const value v) {
		//防止数组越界
		if (m_len > pos) {
			*(start + pos) = v;
			pos++;
		}

	}

	value pop_back() {
		if (pos > 0) {
			--pos;//?
			return *(start + pos);
		}
	}

	value at(int index) {
		return *(start + index);
	}

	int size() {
		return this->m_len;
	}

	iterator begin() {
		return this->start;
	}

	iterator end() {
		return this->start + pos;
	}


	value operator[](int index) {
		if (!(index < m_len))return NULL;

		return *(start + index);

	}


protected:
	iterator m_Data;//表示数据的起始位
	iterator start;//表示数据的起始地址
	int m_len;
	int pos;
};