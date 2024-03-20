#include <cmath>
#include "BinaryTree.h"

#define HASH_TABLE_DEFAULT_SIZE 2
#define UPPER_LOAD_FACTOR_LIMIT 0.75
#define LOWER_LOAD_FACTOR_LIMIT 0.1


template <typename T>
class HashObj {

private:

	int m_hash_table_size;
	int m_num_of_elements;
	BinaryTree<T>** m_data;

public:

	HashObj() : m_hash_table_size(HASH_TABLE_DEFAULT_SIZE), m_data(new BinaryTree<T>* [HASH_TABLE_DEFAULT_SIZE]), m_num_of_elements(0) {
		for (int i = 0; i < m_hash_table_size; i++) {
			m_data[i] = new BinaryTree<T>();
		}
	}

	virtual ~HashObj() {
		for (int i = 0; i < m_hash_table_size; i++) {
			m_data[i]->postorderDelete(true);
			delete m_data[i];
		}
		delete m_data;
	}
	
	double getLoadFactor() const {
		return m_num_of_elements / m_hash_table_size;
	}

	int getIndexOfKey(int key) {
    double num = (key * (sqrt(5) - 1) / 2);
    return (num - static_cast<int>(num)) * m_hash_table_size;
}


	int getNumOfElements() const {
		return m_num_of_elements;
	}

	void setNumOfElements(int num_of_elements) {
		m_num_of_elements = num_of_elements;
	}

	void setHashTableSize(int hash_table_size) {
		m_hash_table_size = hash_table_size;
	}

	int getHashTableSize() const {
		return m_hash_table_size;
	}

	BinaryTree<T>** getData() {
		return m_data;
	}

    StatusType resize(bool to_enlarge) {
        bool execute = false;
        if (to_enlarge) {
            if (getLoadFactor() >= UPPER_LOAD_FACTOR_LIMIT)
                execute = true;
        }
        else {
            if (getLoadFactor() <= LOWER_LOAD_FACTOR_LIMIT)
                execute = true;
        }

        if (execute) {
            int old_hash_table_size;
            if (to_enlarge) {
                old_hash_table_size = m_hash_table_size;
                setHashTableSize(m_hash_table_size * 2);
            }

            else {
                old_hash_table_size = m_hash_table_size;
                setHashTableSize(std::max(m_hash_table_size / 2, HASH_TABLE_DEFAULT_SIZE));
            }

            // Constructing the new array
            BinaryTree<T>** new_data = new BinaryTree<T>*[m_hash_table_size];
            if (new_data == nullptr) return StatusType::ALLOCATION_ERROR;
            for (int i = 0; i < m_hash_table_size; i++) {
                new_data[i] = new BinaryTree<T>();
                if (new_data[i] == nullptr) return StatusType::ALLOCATION_ERROR;
            }

            int index, key;
            for (int i = 0; i < old_hash_table_size; i++) {
                while (m_data[i]->getTreeSize()) {
                    T* curr_element = m_data[i]->getRoot()->getData();
                    key = curr_element->getTeamID();
                    index = getIndexOfKey(key);
                    new_data[index]->insert(curr_element);
                    m_data[i]->remove(curr_element);
                }
                delete m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
        }
        return StatusType::SUCCESS;
    }
};