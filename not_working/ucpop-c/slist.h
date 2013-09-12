// This may look like C code, but it is really -*- C++ -*-
// SList class borrowed from libg++ and modified into template format.
// $Log: SList.h,v $
// Revision 1.3  1993/07/19  00:24:21  ctkwok
// Workable g++ SList class w/o counting
// 


#ifndef SList_H
#define SList_H

#include "utility.h"
#include "stddef.h"
#include <iostream.h>

template <class T> class SListIterator;
template <class T> class SearchQueue;

template <class T>
class SListNode {
  friend class SList<T>;
  friend class SListIterator<T>;
  friend class SearchQueue<T>;
  friend ostream& operator<< (ostream& os, const SList<T>& l);
  // these are best occur in non-class context,  since "this" is T* const
  friend void Reference(SListNode<T>* p) {if (p->ref>= 0) ++p->ref;}
  friend void Dereference(SListNode<T>* p) {
    while (p->ref > 0 && --p->ref==0) {
      SListNode<T>* n = p->tl;
      p->tl=SListNode<T>::free;
      SListNode<T>::free = p; 
      p = n;    
    }
  }
  
public:
  SListNode();
  SListNode(T h);
  SListNode(T h, SListNode<T>* link);
  SListNode(int, int); // super dummy!
  void* operator new(size_t size);
//private:
public:
  SListNode<T>*          tl;
  short                  ref; // I'm not sure if short is enough
  T                      hd;
  static SListNode<T>*   free;
};

template <class T>
class SList {
  friend class SListIterator<T>;
  friend ostream& operator<< (ostream& os, const SList<T>& l);

public:

  // constructors:
  SList();
  SList(T head, const SList<T>& tl);
  SList(const SList<T>& a);
  SList(SListNode<T>* p);
  ~SList();

  // assignment:
  SList<T>&               operator= (const SList<T>& a);
  
  // SList predicates:
  int                   Null() const;
  int                   Empty() const;
  int                   Valid() const;
  operator const void* () const;
  int                   operator ! () const;

  int                   Length() const;

  // functions:
  T                    First() const;
  T                    Head() const;
  SList<T>               Tail();
  SList<T>               Last();

  bool                  contains(T targ) const;

  friend SList<T>        Copy(const SList<T>& a);
  
  friend SList<T>        Concat(const SList<T>& a, const SList<T>& b);
  friend SList<T>        Append(SList<T>& a, SList<T>& b);
 
  SList<T>               operator+(T itm) const;
  SList<T>               operator+(const SList<T>&) const;

  SList<T>&              operator+=(const SList<T>& l);
  SList<T>&              operator+=(T itm);

  SList<T>               operator- (T x);

  bool                  operator== (const T& x) const;
  bool                  operator!= (const T& x) const;

//  friend SList<T>        subst(<T&> old, <T&> repl, SList<T>& a);

  void                  Push(T x);
  T                    Pop();

  void                  SetTail(SList<T>& p);

  void                  Append(const SList<T>& p);
  void                  Prepend(const SList<T>& p);
  void                  Append(T x);
  void                  Prepend(T x);

  void                  FreeUp();
//  void                  subst(<T&> old, <T&> repl);
  static SListNode<T>* NilSListNode;
protected:

  SListNode<T>*          P;
};


template <class T>
class SListIterator {
public:
//  SListIterator(T newsentinel);
//  SListIterator(const SList<T>&, T newsentinel);
  SListIterator(const SList<T>& l);
  SListIterator();
  
  // SList iteration primitives
  bool AtEnd() const {return c==SList<T>::NilSListNode;}
  void Reset();
  void operator=(const SList<T>& ls);
  T operator() ();
  
private:
  SListNode<T>* c;
  SList<T> l;
//  T sentinel;  // sentinel for signalling end of iteration
};

// a macro to simplify common loop iteration code
#define SITERATE(elem, list, ptr, T)  SListIterator<T> ptr(list); T elem;

#define SDOLIST(elem, ptr) for (elem=ptr();!ptr.AtEnd();elem=ptr())


#define SITERATE_NO_INIT(elem, ptr, T)  SListIterator<T> ptr; T elem;

#ifdef OUTLINE
#define inline
#include "slist.cc"
#undef inline
#endif

#ifndef OUTLINE
#include "slist.cc"
#endif

#endif
