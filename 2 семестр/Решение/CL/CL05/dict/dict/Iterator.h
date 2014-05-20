

template<class T>
class Iterator
{
public:
   Iterator(T* curr):current(curr)
   {
   }
   Iterator& operator =(const Iterator& other)
   {
       if (this != &other)
       {
           current = other.current;
       }
       return *this;
   }
   Iterator& operator ++()
   {
       ++current;
       return *this;
   }
   Iterator operator ++(int i)
   {
       Iterator tmp(current);
       ++current;
       return tmp;
   }
   T operator *()
   {
      return *current;
   }
   T* operator ->()
   {
      return current;
   }
private:
   T* current;
};