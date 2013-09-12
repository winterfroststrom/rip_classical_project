// This may look like C code, but it is really -*- C++ -*-
// code borrwed from libg++,  use template format.
// $Log: SList.cc,v $
// Revision 1.1  1993/07/19  00:24:43  ctkwok
// Initial revision
//
// Revision 1.1  1993/07/13  17:28:05  ctkwok
// Initial revision
//

// SListNode::SListNode(T* h, SList<T>& l)
// : tl(l.P), hd(h), ref(1) {Reference(l.P);}

// put this elsewhere
//template <class T> SListNode<T> SList<T>::NilSListNode;

template <class T>
inline void*
SListNode<T>::operator new(size_t size)
{
  if (free) {
    SListNode<T>* trail=free;
    free=free->tl;
    ASSERT(trail);
    return trail;
  } else return ::operator new( size );
}


template <class T>
inline
SListNode<T>::SListNode(int i, int j)
: tl(this), ref(-1) {ASSERT(tl);}

// memory of hd is undefined
template <class T>
inline
SListNode<T>::SListNode()
: tl(SList<T>::NilSListNode), ref(-1) {}


template <class T>
inline
SListNode<T>::SListNode(T h)
: tl(SList<T>::NilSListNode), hd(h), ref(1)
{}


template <class T>
inline
SListNode<T>::SListNode(T h, SListNode<T>* link)
: tl(link), hd(h), ref(1) {}


template <class T>
inline void
Reference(SListNode<T>* n)
{if (n->ref>= 0) ++n->ref;}


template <class T>
inline void
Dereference(SListNode<T>* p)
{
  while (p->ref > 0 && --p->ref==0) {
    SListNode<T>* n = p->tl;
    delete p; 
    p = n;    
  }
}


template <class T>
inline
SList<T>::~SList()
{Dereference(P);}


template <class T>
inline void
SList<T>::FreeUp()
{Dereference(P);P=NilSListNode;}


template <class T>
inline
SList<T>::SList()
: P(NilSListNode) {}


// should this reference something?
template <class T>
inline
SList<T>::SList(SListNode<T>* p)
: P(p) {}



// template <class T>
// SList<T>::SList(T& head)
// : P(new SListNode<T>(head, NilSListNode)) {}


template <class T>
inline 
SList<T>::SList(T head, const SList<T>& tl)
: P(new SListNode<T>(head, tl.P))
{Reference(P->tl); }


template <class T>
inline 
SList<T>::SList(const SList<T>& a)
: P(a.P)
{Reference(a.P);}


template <class T>
inline 
SList<T>&
SList<T>::operator+=(const SList<T>& l)
{Prepend(l); return (*this);}


// these two conterintuitively prepends elem,  builds up-tree
template <class T>
inline 
SList<T>&
SList<T>::operator+=(T x)
{P=new SListNode<T>(x, P);return (*this);}


template <class T>
inline 
SList<T>
SList<T>::operator+(T x) const
{return SList<T>(x, *this);}



template <class T>
inline 
T
SList<T>::First() const
{return P->hd;}


template <class T>
inline 
T
SList<T>::Head() const
{return P->hd;}


template <class T>
inline 
SList<T>
SList<T>::Tail()
{
  Reference(P->tl);
  return SList<T>(P->tl);
}


template <class T>
inline 
bool
SList<T>::Null() const
{return P == NilSListNode;}


template <class T>
inline 
bool
SList<T>::Empty() const
{return P == NilSListNode;}


template <class T>
inline 
bool
SList<T>::Valid() const
{return P != NilSListNode;}


// casting
template <class T>
inline 
SList<T>::operator const void* () const
{return (P == NilSListNode)? 0 : this;}


template <class T>
inline 
bool
SList<T>::operator ! () const
{return (P == NilSListNode);}


template <class T>
inline 
void
SList<T>::Push(T head)
{P = new SListNode<T>(head, P);}


template <class T>
inline 
void
SList<T>::Prepend(T x)
{P=new SListNode<T>(x, P);}



template <class T>
inline 
SList<T>&
SList<T>::operator= (const SList<T>& a)
{
  ASSERT(this != &a);
  Reference(a.P);
  Dereference(P); // destroy itself
  P = a.P;
  return *this;
}


template <class T>
inline 
T
SList<T>::Pop()
{
  T res = P->hd;
  SListNode<T>* tail = P->tl;
  Reference(tail);
  Dereference(P);
  P = tail;
  return res;
}


template <class T>
inline 
void
SList<T>::SetTail(SList<T>& a)
{
  Reference(a.P);
  Dereference(P->tl);
  P->tl = a.P;
}


template <class T>
inline 
SList<T>
SList<T>::Last()
{
  SListNode<T>* p = P;
  if (p != NilSListNode) while (p->tl != NilSListNode) p = p->tl;
  Reference(p);
  return SList<T>(p);
}


template <class T>
inline 
void
SList<T>::Append(const SList<T>& l)
{
  SListNode<T>* p = P;
  SListNode<T>* a = l.P;
  Reference(a);
  if (p != NilSListNode) {
    while (p->tl != NilSListNode) p = p->tl;
    p->tl = a;
  } else
     P = a;
}


template <class T>
inline 
int
SList<T>::Length() const
{
  int l = 0;
  for (SListNode<T>* p = P; p != NilSListNode; p = p->tl) ++l;
  return l;
}


// void SList<T>::subst(<T&> old, <T&> repl)
// {
//   for(SListNode<T>* p = P; p != NilSListNode; p = p->tl)
//     if (<T>EQ(p->hd, old))
//       p->hd = repl;
// }


template <class T>
inline 
SList<T>
Copy(SList<T>& x)
{
  SListNode<T>* a = x.P;
  if (a == NilSListNode)
    return SList<T>(a);
  else {
    SListNode<T>* h = new SListNode<T>(a->hd);
    SListNode<T>* trail = h;
    for(a = a->tl; a != NilSListNode; a = a->tl) {
      SListNode<T>* n = new SListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = NilSListNode;
    return SList<T>(h);
  }
}


// SList<T> subst(<T&> old, <T&> repl, SList<T>& x)
// {
//   SListNode<T>* a = x.P;
//   if (a == NilSListNode)
//     return SList<T>(a);
//   else
//   {
//     SListNode<T>* h = new SListNode<T>;
//     h->ref = 1;
//     if (<T>EQ(a->hd, old))
//       h->hd = repl;
//     else
//       h->hd = a->hd;
//     SListNode<T>* trail = h;
//     for(a = a->tl; a != &NilSListNode; a = a->tl)
//     {
//       SListNode<T>* n = new SListNode<T>;
//       n->ref = 1;
//       if (<T>EQ(a->hd, old))
//         n->hd = repl;
//       else
//         n->hd = a->hd;
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilSListNode;
//     return SList<T>(h);
//   }
// }



template <class T>
inline 
SList<T>
Append(SList<T>& x, SList<T>& y)
{
  SListNode<T>* a = x.P;
  SListNode<T>* b = y.P;
  Reference(b);
  if (a != NilSListNode)
  {
    SListNode<T>* h = new SListNode<T>(a->hd);
    SListNode<T>* trail = h;
    for(a = a->tl; a != NilSListNode; a = a->tl)
    {
      SListNode<T>* n = new SListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = b;
    return SList<T>(h);
  }
  else
    return SList<T>(b);
}


template <class T>
inline 
SList<T>
SList<T>::operator+(const SList<T>& y) const
{
  SListNode<T>* a = P;
  SListNode<T>* b = y.P;
  SListNode<T> *h, *n, *trail;

  Reference(b);
  if (a != NilSListNode) {
    h = new SListNode<T>(a->hd);
    trail = h;
    for(a = a->tl; a != NilSListNode; a = a->tl) {
      n = new SListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = b;
    return SList<T>(h);
  } else
     return SList<T>(b);
}


template <class T>
inline 
void
SList<T>::Prepend(const SList<T>& y)
{
  SListNode<T>* b = y.P;
  if (b != NilSListNode)
  {
    SListNode<T>* h = new SListNode<T>(b->hd);
    SListNode<T>* trail = h;
    for(b = b->tl; b != NilSListNode; b = b->tl)
    {
      SListNode<T>* n = new SListNode<T>(b->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = P;
    P = h;
  }
}


// template <class T>
// SList<T> concat(SList<T>& x, SList<T>& y)
// {
//   SListNode<T>* a = x.P;
//   SListNode<T>* b = y.P;
//   if (a != NilSListNode)
//   {
//     SListNode<T>* h = newSListNode<T>(a->hd);
//     SListNode<T>* trail = h;
//     for(a = a->tl; a != &NilSListNode; a = a->tl)
//     {
//       SListNode<T>* n = newSListNode<T>(a->hd);
//       trail->tl = n;
//       trail = n;
//     };
//     for(;b != &NilSListNode; b = b->tl)
//     {
//       SListNode<T>* n = newSListNode<T>(b->hd);
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilSListNode;
//     return SList<T>(h);
//   }
//   else if (b != &NilSListNode)
//   {
//     SListNode<T>* h = newSListNode<T>(b->hd);
//     SListNode<T>* trail = h;
//     for(b = b->tl; b != &NilSListNode; b = b->tl)
//     {
//       SListNode<T>* n = newSListNode<T>(b->hd);
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilSListNode;
//     return SList<T>(h);
//   }
//   else
//     return SList<T>(&NilSListNode);
// }
// 

template <class T>
inline 
SList<T>
SList<T>::operator- (T targ)
{
  SListNode<T>* a = P;
  SListNode<T>* h = NilSListNode;
  while (a != NilSListNode) {
    if (!(a->hd==targ)) {
      h = new SListNode<T>(a->hd);
      SListNode<T>* trail = h;
      for(a = a->tl; a != NilSListNode; a = a->tl) {
        if (!(a->hd==targ)) {
          SListNode<T>* n = new SListNode<T>(a->hd);
          trail->tl = n;
          trail = n;
        }
      }
      trail->tl = NilSListNode;
      break;
    } else
       a = a->tl;
  }
  return SList<T>(h);
}


template <class T>
inline 
bool
SList<T>::operator== (const T& x) const
{
  SListNode<T>* c=P;
  while (c!=NilSListNode) {
    if (c->hd==x) return TRUE;
    else c=c->tl;
  }
  return FALSE;
}



template <class T>
inline 
bool
SList<T>::operator!= (const T& x) const
{
  SListNode<T>* c=P;
  while (c != NilSListNode) {
    if (c->hd==x) return FALSE;
    else c=c->tl;
  }
  return TRUE;
}


template <class T>
inline 
SListIterator<T>::SListIterator(const SList<T>& ls)
: l(ls), c(NULL) {}


template <class T>
inline 
SListIterator<T>::SListIterator()
: l(), c(NULL) {}


template <class T>
inline 
void
SListIterator<T>::Reset()
{c=NULL;}

template <class T>
inline 
void
SListIterator<T>::operator=(const SList<T>& ls)
{l=ls; c=NULL;}


template <class T>
inline 
T
SListIterator<T>::operator() ()
{
// DOLIST CONTROLS WHEN TO STOP
  c=(c)?c->tl:l.P;
  return c->hd;
}

