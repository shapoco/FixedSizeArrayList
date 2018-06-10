#pragma once

#include "FixedSizeArrayList.h"

template<int SIZE> class FixedSizeSortedList
{
protected:
	FixedSizeArrayList<int, SIZE> m_list;
public:
	FixedSizeSortedList()
	{
		//m_list = new FixedSizeArrayList<int, SIZE>();
	}

	inline int operator[](const int i) const {
		return m_list[i];
	}

	inline int& operator[](const int i) {
		return m_list[i];
	}

	int getCount() {
		return m_list.getCount();
	}

	bool add(int value) {
		for (int i = 0; i < SIZE; ++i) {
			if (value > m_list[i]) {
				return m_list.insert(value, i);
			}
		}
		return m_list.add(value);
	}

	bool remove(int value) {
		for (int i = 0; i < SIZE; ++i) {
			if (value == m_list[i]) {
				return m_list.removeAt(i);
			}
		}
		return false;
	}

};

