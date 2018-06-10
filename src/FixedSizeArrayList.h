#ifndef FixedSizeArrayList_h
#define FixedSizeArrayList_h

template<typename TValue, int SIZE>
class FixedSizeArrayList
{
private:
	static constexpr int generateMaskRecursive(int x, int i, int mask) {
		return ((x >> i) == 0) ?
			mask :
			generateMaskRecursive(x, i + 1, (mask << 1) | 1);
	}
	static constexpr int generateMask(int x) {
		return (x < 0) ? 1 : generateMaskRecursive(x, 1, 1);
	}
#pragma region assertions_for_generateMask
	static_assert(generateMask(0x0) == 0x1, "generateMask(0x0) must be 0x1");
	static_assert(generateMask(0x1) == 0x1, "generateMask(0x1) must be 0x1");
	static_assert(generateMask(0x2) == 0x3, "generateMask(0x2) must be 0x3");
	static_assert(generateMask(0x3) == 0x3, "generateMask(0x3) must be 0x3");
	static_assert(generateMask(0x4) == 0x7, "generateMask(0x4) must be 0x7");
	static_assert(generateMask(0x5) == 0x7, "generateMask(0x5) must be 0x7");
	static_assert(generateMask(0x6) == 0x7, "generateMask(0x6) must be 0x7");
	static_assert(generateMask(0x7) == 0x7, "generateMask(0x7) must be 0x7");
	static_assert(generateMask(0x8) == 0xf, "generateMask(0x8) must be 0xf");
	static_assert(generateMask(0x9) == 0xf, "generateMask(0x9) must be 0xf");
	static_assert(generateMask(0xa) == 0xf, "generateMask(0xa) must be 0xf");
	static_assert(generateMask(0xb) == 0xf, "generateMask(0xb) must be 0xf");
	static_assert(generateMask(0xc) == 0xf, "generateMask(0xc) must be 0xf");
	static_assert(generateMask(0xd) == 0xf, "generateMask(0xd) must be 0xf");
	static_assert(generateMask(0xe) == 0xf, "generateMask(0xe) must be 0xf");
	static_assert(generateMask(0xf) == 0xf, "generateMask(0xf) must be 0xf");
	static_assert(generateMask(0x10) == 0x1f, "generateMask(0x10) must be 0x1f");
	static_assert(generateMask(0x11) == 0x1f, "generateMask(0x81) must be 0xff");
	static_assert(generateMask(0xff) == 0xff, "generateMask(0xff) must be 0xff");
	static_assert(generateMask(0x100) == 0x1ff, "generateMask(0x100) must be 0x1ff");
	static_assert(generateMask(0x155) == 0x1ff, "generateMask(0x155) must be 0x1ff");
	static_assert(generateMask(0x4001) == 0x7fff, "generateMask(0x4001) must be 0x7fff");
	static_assert(generateMask(0x7fff) == 0x7fff, "generateMask(0x7fff) must be 0x7fff");
#pragma endregion

protected:
	const int INDEX_MASK = generateMask(SIZE);
	TValue m_array[SIZE];
	int m_baseIndex;
	int m_count;
public:
	FixedSizeArrayList()
	{
		m_baseIndex = 0;
		m_count = 0;
	}

	inline TValue operator[](int i) const {
		return m_array[(m_baseIndex + i) & INDEX_MASK];
	}

	inline TValue& operator[](int i) {
		return m_array[(m_baseIndex + i) & INDEX_MASK];
	}

	int getCount() { return m_count; }

	bool add(TValue value) {
		return insert(value, m_count);
	}

	bool insert(TValue value, int index) {
		if (m_count >= SIZE || index < 0 || m_count < index)
			return false;

		if (index < m_count / 2) {
			// 前半に挿入した場合
			// --> 前半を一つずつ前方へずらす
			int iL = (m_baseIndex)& INDEX_MASK;
			for (int i = 0; i < index - 1; ++i) {
				int iR = (iL + 1) & INDEX_MASK;
				m_array[iL] = m_array[iR];
				iL = iR;
			}
			m_baseIndex = (m_baseIndex - 1) & INDEX_MASK;
		}
		else {
			// 後半に挿入した場合
			// --> 後半を一つずつ後方へずらす
			int iL = (m_baseIndex + m_count) & INDEX_MASK;
			for (int i = m_count; i >= index + 1; --i) {
				int iR = (iL - 1) & INDEX_MASK;
				m_array[iL] = m_array[iR];
				iL = iR;
			}
		}

		m_array[(m_baseIndex + index) & INDEX_MASK] = value;
		m_count++;
		return true;
	}

	bool removeAt(int index) {
		if (index < 0 || m_count <= index)
			return false;

		if (index < m_count / 2) {
			// 前半を消した場合
			// --> 前半を一つずつ後方へずらす
			int iL = (m_baseIndex + index) & INDEX_MASK;
			for (int i = index; i >= 1; --i) {
				int iR = (iL - 1) & INDEX_MASK;
				m_array[iL] = m_array[iR];
				iL = iR;
			}
			m_baseIndex = (m_baseIndex + 1) & INDEX_MASK;
		}
		else {
			// 後半を消した場合
			// --> 後半を一つずつ前方へずらす
			int iL = (m_baseIndex + index) & INDEX_MASK;
			for (int i = index; i < m_count - 1; ++i) {
				int iR = (iL + 1) & INDEX_MASK;
				m_array[iL] = m_array[iR];
				iL = iR;
			}
		}

		m_count--;
		return true;
	}


};

#endif