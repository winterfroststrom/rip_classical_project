// searchqueue.cc

#ifdef OUTLINE
#define inline
#include "searchqueue.icc"
#undef inline
#endif
  
template <class T>
SearchQueue<T>::SearchQueue(T* initialElem)
: upperboundRank(rankPlan(*initialElem))
{
  queue=new List<T>[upperboundRank+1];
  queue[upperboundRank].Push(initialElem);
}


template <class T>
SearchQueue<T>::~SearchQueue()
{
  delete [] queue;
}
