#ifndef FixedSizeQueue_h
#define FixedSizeQueue_h

#include "FixedSizeArrayList.h"

template<typename TValue, int SIZE> class FixedSizeQueue
{
protected:
	FixedSizeArrayList<TValue, SIZE> m_list;
public:
	FixedSizeQueue()
	{
		//m_list = new FixedSizeArrayList<TValue, SIZE>();
	}

	int getCount() {
		return m_list.getCount(); 
	}
	
	bool push(TValue newValue) {
		return m_list.add(newValue);
	}

	TValue pop() {
		TValue retval = m_list[m_list.getCount() - 1];
		m_list.removeAt(0);
		return retval;
	}

};

#endif
