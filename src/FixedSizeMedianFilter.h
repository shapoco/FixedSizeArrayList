#ifndef FixedSizeMedianFilter_h
#define FixedSizeMedianFilter_h

#include "FixedSizeQueue.h"
#include "FixedSizeSortedList.h"

template<int SIZE> 
class FixedSizeMedianFilter
{
protected:
	FixedSizeQueue<int, SIZE> m_queue;
	FixedSizeSortedList<SIZE> m_sortedList;
public:
	FixedSizeMedianFilter()
	{
		//m_queue = new FixedSizeQueue<int, SIZE>();
		//m_sortedList = new FixedSizeSortedList<SIZE>();
	}

	void push(int value)
	{
		if (m_queue.getCount() < SIZE) {
			m_queue.push(value);
			m_sortedList.add(value);
		}
		else {
			m_sortedList.remove(m_queue.pop());
			m_queue.push(value);
			m_sortedList.add(value);
		}
	}

	int getMedian() {
		return m_sortedList[m_sortedList.getCount() / 2];
	}
};

#endif
