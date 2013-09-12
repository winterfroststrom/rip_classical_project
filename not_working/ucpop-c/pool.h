// small chunk memory allocation routines

template <class T>
class Pool {
public:
  Pool();
private:
  const int InitialPoolSize;
  BitStr* pool;
  const int poolSize; // Each memory allocation size
  BitStr freeList;
  BitStr trail;
  int poolCount;

private:
  int count;
  T* memory;
  T* freeList;
};
