// This may look like C code, but it is really -*- C++ -*-
// List class borrowed from libg++ and modified into template format.
// $Log: list.h,v $
// Revision 1.3  1993/07/19  00:24:21  ctkwok
// Workable g++ list class w/o counting
//

#ifndef LIST_H
#define LIST_H

#include "utility.h"
#include <iostream.h>

template <class T> class ListIterator;
template <class T> class SearchQueue;



template <class T>
class ListNode {
  friend class List<T>;
  friend class ListIterator<T>;
  friend class SearchQueue<T>;
  friend ostream& operator<< (ostream& os, const List<T>& l);
  // these are best occur in non-class context,  since "this" is T* const
  friend void Reference(ListNode<T>* p) {if (p->ref>= 0) ++p->ref;}
  friend void Dereference(ListNode<T>* p) {
    while (p->ref > 0 && --p->ref==0) {
      ListNode<T>* n = p->tl;
      p->tl=ListNode<T>::free;
      ListNode<T>::free = p; 
      p->hd->Dereference();
      if (p->hd->Deletable()) {
//	cerr << "Deleting something..." << endl;
	delete p->hd;
      }
      p = n;    
    }
  }
  
public:
  ListNode();// : tl(this), ref(-1), hd(NULL) {}
  ListNode(int);
  void* operator new (size_t size);
private:
  ListNode(T& h); //: tl(link), hd(&h), ref(1) {}
  ListNode(T* h); //: tl(link), hd(h), ref(1) {}

  ListNode(T& h, ListNode<T>* link); //: tl(link), hd(&h), ref(1) {}
  ListNode(T* h, ListNode<T>* link); //: tl(link), hd(h), ref(1) {}

  // NilListNode initializer
  
//private:
public:
  ListNode<T>*          tl;
  short                 ref; // I'm not sure if short is enough
  T*                    hd;
  static ListNode<T>*   free;
};

template <class T>
class List {
  friend class ListIterator<T>;
  friend class SearchQueue<T>;
  friend ostream& operator<< (ostream& os, const List<T>& l);

public:
  // constructors:
  List();
//  List(T& head);
  List(T& head, const List<T>& tl);
  List(T* head, const List<T>& tl);
  List(const List<T>& a);
  List(ListNode<T>* p);
  ~List();

  // assignment:
  List<T>&               operator= (const List<T>& a);
  
  // List predicates:
  int                   Null() const;
  int                   Empty() const;
  int                   Valid() const;
  operator const void* () const;
  int                   operator ! () const;

  int                   Length() const;

  // functions:
  T*                    First() const;
  T*                    Head() const;
  List<T>               Tail();
  List<T>               Last();

  bool                  contains(T& targ) const;

  friend List<T>        Copy(const List<T>& a);
  
  friend List<T>        Concat(const List<T>& a, const List<T>& b);
  friend List<T>        Append(List<T>& a, List<T>& b);

  List<T>               Copy() const;
  List<T>               operator+(T& itm) const;
  List<T>               operator+(T* itm) const;
  List<T>               operator+(const List<T>&);

  List<T>&              operator+=(const List<T>& l);
  List<T>&              operator+=(T& itm);
  List<T>&              operator+=(T* itm);

  List<T>               operator- (T& x);
  List<T>               operator- (T* x);

  bool                  operator== (const T& x) const;
  bool                  operator== (T* x) const;
  
  bool                  operator!= (const T& x) const;
  bool                  operator!= (T* x) const;
//  friend List<T>        subst(<T&> old, <T&> repl, List<T>& a);

  void                  Push(T& x);
  void                  Push(T* x);
  T*                    Pop();

  void                  SetTail(List<T>& p);

  void                  Append(const List<T>& p);
  void                  Prepend(const List<T>& p);
  void                  Append(T& item);
  void                  Prepend(T& item);
  void                  Append(T* item);
  void                  Prepend(T* item);

  void                  FreeUp();

  static ListNode<T>* NilListNode;
//protected:  // bug in gcc!
public:
  
  ListNode<T>*          P;
};

template <class T>
class ListIterator {
public:
  ListIterator(); // this may not be necessary
  ListIterator(const List<T>&);
  T*          operator() (void);           // operator for iteration

    // assign a different list for iteration
  void        operator=(const List<T>&);
  void Reset();
  bool AtEnd() const {return c==List<T>::NilListNode;}
  List<T> Rest();

private:
  ListNode<T>* c;
  List<T> l; // use a const ptr because we want to reassign
};

// a macro to simplify common loop iteration code
#define ITERATE(elem, list, ptr, T)  ListIterator<T> ptr(list); T* elem;
#define DOLIST(elem, next) for (elem=next();!next.AtEnd();elem=next())
//#define DOLIST(elem, next) while ((!next.AtEnd()) && (elem=next()))
#define ITERATE_NO_INIT(elem, ptr, T)  ListIterator<T> ptr; T* elem;
#define DECLAREPRINT(T) ostream& operator<< (ostream& os, const List<T>& l)  {\
    os << "( ";\
    ListNode<T>* c=l.P;\
    while (c != List<T>::NilListNode) {\
      os << *(c->hd) << endl;\
      c=c->tl;\
    }\
    os << ")";\
    return os;\
  }

#include "list.cc"
#endif

