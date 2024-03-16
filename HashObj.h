#include <cmath>


#define HASH_TABLE_DEFAULT_SIZE 2


template <typename T>
class HashObj {

private:

	int m_hash_table_size;
	int m_used_cells;
	T* m_data;

public:

	HashObj() : m_hash_table_size(HASH_TABLE_DEFAULT_SIZE), m_data(new T[HASH_TABLE_DEFAULT_SIZE]), m_used_cells(0) {}

	int getCapacityFactor() const{
		return m_data->getTreeSize() / m_hash_table_size;
	}

	int getIndexOfKey(int key) {
		double num = (m_hash_table_size * key * (sqrt(5) - 1) / 2);
		return (num - static_cast<int>(num));
	}
};