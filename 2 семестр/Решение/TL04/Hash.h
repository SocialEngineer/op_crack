
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

    return h;
 } 

template <typename T>
class Hash
{
private:
    List<T> *_array;
    int _length;
	int _hashSize;
	HASH_INDEX (*_getHash)(T);

public:
    Hash(int hashSize, HASH_INDEX (*getHash)(T))
    {
        _length = 0;
		_hashSize = hashSize;
		_array = new List<T>[_hashSize];
		_getHash = getHash;
    }

    ~Hash()
    {
		for (int i = 0; i < _length; i++)
			_array[i].clear();

		delete[] _array;
    }

    bool add(T val)
    {
		if (_length == _hashSize) return false;

         HASH_INDEX h = _getHash(val) % _hashSize;
        _array[h].add(val);

        _length++;
		return true;
    }

    bool count(T val)
    {
        return _array[_getHash(val)].length() != 0;
    }

	void remove(T val)
	{
		_array[_getHash(val)].remove(val);
	}

	int length()
	{
		return _length;
	}
};
