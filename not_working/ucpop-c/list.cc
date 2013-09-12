// This may look like C code, but it is really -*- C++ -*-
// code borrwed from libg++,  use template format.
// $Log: list.cc,v $
// Revision 1.1  1993/07/19  00:24:43  ctkwok
// Initial revision
//
// Revision 1.1  1993/07/13  17:28:05  ctkwok
// Initial revision
//
// ListNode::ListNode(T* h, List<T>& l)
// : tl(l.P), hd(h), ref(1) {Reference(l.P);}

// the following could/should be defined in a .cc file
// #ifdef __GNUG__
// template <class T>
// ListNode<T> List<T>::NilListNode;
// #else
// template <class T>
// ListNode<T> List<T>::NilListNode;
// #endif

template <class T>
inline void*
ListNode<T>::operator new(size_t size)
{
  if (free) {
    ListNode<T>* trail=free;
    free=free->tl;
    return trail;
  } else return malloc(size);
}


template <class T>
inline 
ListNode<T>::ListNode(int i)
: tl(this), ref(-1), hd(NULL) {ASSERT(tl);}


template <class T>
inline 
ListNode<T>::ListNode()
: tl(List<T>::NilListNode), ref(-1), hd(NULL) {ASSERT(tl);}

template <class T>
inline 
ListNode<T>::ListNode(T* h, ListNode<T>* link)
: tl(link), hd(h), ref(1) {ASSERT(h);h->Reference();}


template <class T>
inline 
ListNode<T>::ListNode(T& h, ListNode<T>* link)
: tl(link), hd(&h), ref(1) {ASSERT(&h);h.Reference();}

template <class T>
inline 
ListNode<T>::ListNode(T* h)
: tl(List<T>::NilListNode), hd(h), ref(1) {ASSERT(h);h->Reference();}


template <class T>
inline 
ListNode<T>::ListNode(T& h)
: tl(List<T>::NilListNode), hd(&h), ref(1) {ASSERT(&h);h.Reference();}
// 
// template <class T>
// inline 
// void
// Reference(ListNode<T>* n)
// {if (n->ref>= 0) ++n->ref;}
// 
// 
// template <class T>
// inline 
// void
// Dereference(ListNode<T>* p)
// {
//   while (p->ref > 0 && --p->ref==0) {
//     ListNode<T>* n = p->tl;
//     delete p; 
//     p = n;    
//   }
// }
// 

template <class T>
inline 
List<T>::~List()
{Dereference(P);}


template <class T>
inline 
void
List<T>::FreeUp()
{Dereference(P);P=NilListNode;}


template <class T>
inline 
List<T>::List()
: P(NilListNode) {ASSERT(NilListNode);}


// should this reference something?
template <class T>
inline 
List<T>::List(ListNode<T>* p)
: P(p) {ASSERT(p);}



// template <class T>
// List<T>::List(T& head)
// : P(new ListNode<T>(head, NilListNode)) {}


template <class T>
inline 
List<T>::List(T& head, const List<T>& tl)
: P(new ListNode<T>(head, tl.P))
{ASSERT(&head);Reference(P->tl); }


template <class T>
inline 
List<T>::List(T* head, const List<T>& tl)
: P(new ListNode<T>(head, tl.P))
{
  //ASSERT(head);
  Reference(P->tl);
}

     
template <class T>
inline 
List<T>::List(const List<T>& a)
: P(a.P)
{Reference(a.P);}


template <class T>
inline 
List<T>&
List<T>::operator+=(const List<T>& l)
{Prepend(l); return (*this);}


// these two conterintuitively prepends elem,  builds up-tree
template <class T>
inline 
List<T>&
List<T>::operator+=(T& x)
{if (&x) P=new ListNode<T>(x, P);return (*this);}


template <class T>
inline 
List<T>&
List<T>::operator+=(T* x)
{if (x) P=new ListNode<T>(x, P); return (*this);}


template <class T>
inline 
List<T>
List<T>::operator+(T& x) const
{return (&x) ? List<T>(x, *this) : *this;}


template <class T>
inline 
List<T>
List<T>::operator+(T* x) const
{return (x) ? List<T>(x, *this) : *this;}


template <class T>
inline 
T*
List<T>::First() const
{return P->hd;}


template <class T>
inline 
T*
List<T>::Head() const
{return P->hd;}


template <class T>
inline 
List<T>
List<T>::Tail()
{
  Reference(P->tl);
  return List<T>(P->tl);
}


template <class T>
inline 
bool
List<T>::Null() const
{return P == NilListNode;}


template <class T>
inline 
bool
List<T>::Empty() const
{return P == NilListNode;}


template <class T>
inline 
bool
List<T>::Valid() const
{return P != NilListNode;}


// casting
template <class T>
inline 
List<T>::operator const void* () const
{return (P == NilListNode)? 0 : this;}


template <class T>
inline 
bool
List<T>::operator ! () const
{return (P == NilListNode);}


template <class T>
inline 
void
List<T>::Push(T& head)
{if (&head) P = new ListNode<T>(head, P);}


template <class T>
inline 
void
List<T>::Push(T* head)
{if (head) P = new ListNode<T>(head, P);}


template <class T>
inline 
void
List<T>::Prepend(T& x)
{if (&x) P=new ListNode<T>(x, P);}


template <class T>
inline 
void
List<T>::Prepend(T* x)
{if (x) P=new ListNode<T>(x, P);}


template <class T>
inline 
List<T>&
List<T>::operator= (const List<T>& a)
{
  ASSERT(this != &a);
  Reference(a.P);
  Dereference(P); // destroy itself
  P = a.P;
  return *this;
}


template <class T>
inline 
T*
List<T>::Pop()
{
  T* res = P->hd;
  P->hd->Reference();  // prevent it from being deleted
  ListNode<T>* tail = P->tl;
  Reference(tail);
  Dereference(P);
  P = tail;
  return res;
}


template <class T>
inline 
void
List<T>::SetTail(List<T>& a)
{
  Reference(a.P);
  Dereference(P->tl);
  P->tl = a.P;
}


template <class T>
inline 
List<T>
List<T>::Last()
{
  ListNode<T>* p = P;
  if (p != NilListNode) while (p->tl != NilListNode) p = p->tl;
  Reference(p);
  return List<T>(p);
}


template <class T>
inline 
void
List<T>::Append(const List<T>& l)
{
  ListNode<T>* p = P;
  ListNode<T>* a = l.P;
  Reference(a);
  if (p != NilListNode) {
    while (p->tl != NilListNode) p = p->tl;
    p->tl = a;
  } else
     P = a;
}


template <class T>
inline 
int
List<T>::Length() const
{
  int l = 0;
  for (ListNode<T>* p = P; p != NilListNode; p = p->tl) ++l;
  return l;
}


// void List<T>::subst(<T&> old, <T&> repl)
// {
//   for(ListNode<T>* p = P; p != NilListNode; p = p->tl)
//     if (<T>EQ(p->hd, old))
//       p->hd = repl;
// }


template <class T>
inline 
List<T>
List<T>::Copy() const
{
  ListNode<T>* a = this->P;
  if (a == NilListNode)
    return List<T>(a);
  else {
    ListNode<T>* h = new ListNode<T>(a->hd);
    ListNode<T>* trail = h;
    for(a = a->tl; a != NilListNode; a = a->tl) {
      ListNode<T>* n = new ListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = NilListNode;
    return List<T>(h);
  }
}


// List<T> subst(<T&> old, <T&> repl, List<T>& x)
// {
//   ListNode<T>* a = x.P;
//   if (a == &NilListNode)
//     return List<T>(a);
//   else
//   {
//     ListNode<T>* h = new ListNode<T>;
//     h->ref = 1;
//     if (<T>EQ(a->hd, old))
//       h->hd = repl;
//     else
//       h->hd = a->hd;
//     ListNode<T>* trail = h;
//     for(a = a->tl; a != &NilListNode; a = a->tl)
//     {
//       ListNode<T>* n = new ListNode<T>;
//       n->ref = 1;
//       if (<T>EQ(a->hd, old))
//         n->hd = repl;
//       else
//         n->hd = a->hd;
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilListNode;
//     return List<T>(h);
//   }
// }



template <class T>
inline 
List<T>
Append(List<T>& x, List<T>& y)
{
  ListNode<T>* a = x.P;
  ListNode<T>* b = y.P;
  Reference(b);
  if (a != NilListNode)
  {
    ListNode<T>* h = new ListNode<T>(a->hd);
    ListNode<T>* trail = h;
    for(a = a->tl; a != NilListNode; a = a->tl)
    {
      ListNode<T>* n = new ListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = b;
    return List<T>(h);
  }
  else
    return List<T>(b);
}


template <class T>
inline 
List<T>
List<T>::operator+(const List<T>& y)
{
  ListNode<T>* a = P;
  ListNode<T>* b = y.P;
  ListNode<T> *h, *n, *trail;
  

  Reference(b);
//  cerr << "HERE!!!!!!";
  if (a != NilListNode) {
    ASSERT(a->hd);
    h = new ListNode<T>(a->hd);
    trail = h;
    ASSERT(h);
    for(a = a->tl; a != NilListNode; a = a->tl) {
      n = new ListNode<T>(a->hd);
      trail->tl = n;
      trail = n;
      ASSERT(n);
    }
//  cerr << "HERE2!!!!!!";
    ASSERT(trail);
    trail->tl = b;
    return List<T>(h);
  } else
     return List<T>(b);
}


template <class T>
inline 
void
List<T>::Prepend(const List<T>& y)
{
  ListNode<T>* b = y.P;
  if (b != NilListNode)
  {
    ListNode<T>* h = new ListNode<T>(b->hd);
    ListNode<T>* trail = h;
    for(b = b->tl; b != NilListNode; b = b->tl)
    {
      ListNode<T>* n = new ListNode<T>(b->hd);
      trail->tl = n;
      trail = n;
    }
    trail->tl = P;
    P = h;
  }
}


// template <class T>
// List<T> concat(List<T>& x, List<T>& y)
// {
//   ListNode<T>* a = x.P;
//   ListNode<T>* b = y.P;
//   if (a != NilListNode)
//   {
//     ListNode<T>* h = newListNode<T>(a->hd);
//     ListNode<T>* trail = h;
//     for(a = a->tl; a != &NilListNode; a = a->tl)
//     {
//       ListNode<T>* n = newListNode<T>(a->hd);
//       trail->tl = n;
//       trail = n;
//     };
//     for(;b != &NilListNode; b = b->tl)
//     {
//       ListNode<T>* n = newListNode<T>(b->hd);
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilListNode;
//     return List<T>(h);
//   }
//   else if (b != &NilListNode)
//   {
//     ListNode<T>* h = newListNode<T>(b->hd);
//     ListNode<T>* trail = h;
//     for(b = b->tl; b != &NilListNode; b = b->tl)
//     {
//       ListNode<T>* n = newListNode<T>(b->hd);
//       trail->tl = n;
//       trail = n;
//     }
//     trail->tl = &NilListNode;
//     return List<T>(h);
//   }
//   else
//     return List<T>(&NilListNode);
// }
// 

template <class T>
inline 
List<T>
List<T>::operator- (T& targ)
{
  ListNode<T>* a = P;
  ListNode<T>* h = NilListNode;
  while (a != NilListNode) {
    if (!(a->hd==&targ)) {
      h = new ListNode<T>(a->hd);
      ListNode<T>* trail = h;
      for(a = a->tl; a != NilListNode; a = a->tl) {
        if (!(a->hd==&targ)) {
          ListNode<T>* n = new ListNode<T>(a->hd);
          trail->tl = n;
          trail = n;
        }
      }
      trail->tl = NilListNode;
      break;
    } else
       a = a->tl;
  }
  return List<T>(h);
}

template <class T>
inline 
List<T>
List<T>::operator- (T* targ)
{
  ListNode<T>* a = P;
  ListNode<T>* h = NilListNode;
  while (a != NilListNode) {
    if (!(a->hd == targ)) {
      h = new ListNode<T>(a->hd);
      ListNode<T>* trail = h;
      for(a = a->tl; a != NilListNode; a = a->tl) {
        if (!(a->hd == targ)) {
          ListNode<T>* n = new ListNode<T>(a->hd);
          trail->tl = n;
          trail = n;
        }
      }
      trail->tl = NilListNode;
      break;
    } else
       a = a->tl;
  }
  return List<T>(h);
}


template <class T>
inline 
bool
List<T>::operator== (const T& x) const
{
  ListNode<T>* c=P;
  while (c!=NilListNode) {
     if (c->hd==&x) return TRUE;
     else c=c->tl;
   }
  return FALSE;
}


template <class T>
inline 
bool
List<T>::operator== (T* x) const
{
  ListNode<T>* c=P;

  while (c!=NilListNode) {
     if (c->hd==x) return TRUE;
     else c=c->tl;
   }
  return FALSE;
}


template <class T>
inline 
bool
List<T>::operator!= (const T& x) const
{
  ListNode<T>* c=P;

  while (c!=NilListNode) {
    if (c->hd==&x) return FALSE;
    else c=c->tl;
  }
  return TRUE;
}


template <class T>
inline 
bool
List<T>::operator!= (T* x) const
{
  ListNode<T>* c=P;
  while (c!=NilListNode) {
    if (c->hd==x) return FALSE;
    else c=c->tl;
  }
  return TRUE;
}

// no special case: if meets NilListNode,  which points back to itself,
// it'll cycle back and return NULL.
// rely on c being NULL when initialized.
template <class T>
inline 
T*
ListIterator<T>::operator () ()
{
  c=(c)?c->tl:l.P;
  return c->hd;
}


// c could well be null
template <class T>
inline 
List<T>
ListIterator<T>::Rest()
{if (!c) c=l.P; Reference(c->tl); return List<T>(c->tl);}


template <class T>
inline 
ListIterator<T>::ListIterator()
: l(), c(NULL) {}


template <class T>
inline 
ListIterator<T>::ListIterator(const List<T>& ls)
: l(ls), c(NULL) {}


template <class T>
inline 
void
ListIterator<T>::Reset()
{c=NULL;}

template <class T>
inline 
void
ListIterator<T>::operator=(const List<T>& ls)
{l=ls; c=NULL;}

