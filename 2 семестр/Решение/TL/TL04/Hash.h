
#include "List.h"

#define HASH_SIZE 256*256
#define HASH_INDEX unsigned long int

using namespace std;

HASH_INDEX stringToHash(string str)
{
    HASH_INDEX h = 0;

	for (unsigned int i = 0; i < str.length(); i++)
    {
		h += str[i];
		h += (h << 10);
		h ^= (h >> 6);
	}

	h += (h << 3);
	h ^= (h >> 11);
	h += (h << 15);

    return h  % HASH_SIZE;
 } 

template <typename K, typename V>
class Hash
{
public:

    Hash(int hashSize, HASH_INDEX (*getHash)(K))
    {
        _length = 0;
		_hashSize = max(hashSize, 2);
		_array = new List<K, V>[_hashSize];
		_getHash = getHash;
    }

    ~Hash()
    {
		for (int i = 0; i < _length; i++)
			_array[i].clear();

		delete[] _array;
    }

    bool add(K key, V val)
    {
		//cout << key << " : "<< _getHash(key) << endl;
         HASH_INDEX h = _getHash(key) % _hashSize;
        _array[h].add(key, val);

        _length++;
		return true;
    }

    bool count(K key)
    {
        return _array[_getHash(key) % _hashSize].length() != 0;
    }

	List<K, V>* getList(K key)
	{
		return &_array[_getHash(key) % _hashSize];
	}

	V* find(K key)
	{
		V *val = getList(key)->find(key);
		
		return val;
	}

	void remove(K key)
	{
		_array[_getHash(key) % _hashSize].remove(key);
	}

	int length()
	{
		return _length;
	}

	void trace()
	{
		for (int i = 0; i < _length; i++)
		{
			if (_array[i].trace()) cout << endl;
		}
	}

private:
	List<K, V> *_array;
    int _length;
	int _hashSize;
	HASH_INDEX (*_getHash)(K);
};
