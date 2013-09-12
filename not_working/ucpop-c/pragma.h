#ifndef PRAGMA_H
#define PRAGMA_H

#ifdef __DECCXX
class Term;
class Effect;
class Link;
class Step;
class Varset;
class TemplateEntry;
class Node;
class Pair;
class String;
class Unsafe;
class Problem;
class Plan;
#ifndef Sym
//class Sym;
typedef int Sym;
#endif

#ifndef TERM_TEM
#define TERM_TEM
#pragma define_template ListNode<Term>
#pragma define_template List<Term>
#pragma define_template ListIterator<Term>
#endif

#ifndef EFFECT_TEM
#define EFFECT_TEM
#pragma define_template ListNode<Effect>
#pragma define_template List<Effect>
#pragma define_template ListIterator<Effect>
#endif

#ifndef OPENC_TEM
#define OPENC_TEM
#pragma define_template ListNode<Openc>
#pragma define_template List<Openc>
#pragma define_template ListIterator<Openc>
#endif

#ifndef LINK_TEM
#define LINK_TEM
#pragma define_template ListNode<Link>
#pragma define_template List<Link>
#pragma define_template ListIterator<Link>
#endif

#ifndef STEP_TEM
#define STEP_TEM
#pragma define_template ListNode<Step>
#pragma define_template List<Step>
#pragma define_template ListIterator<Step>
#endif

// #ifndef INT_TEM
// #define INT_TEM
// #pragma define_template ListNode<int>
// #pragma define_template List<int>
// #pragma define_template ListIterator<int>
// #endif

#pragma define_template ListNode<Varset>
#pragma define_template List<Varset>
#pragma define_template ListIterator<Varset>

//#pragma define_template Array<String>
#pragma define_template Array<Sym>

#pragma define_template ListNode<TemplateEntry>
#pragma define_template List<TemplateEntry>
#pragma define_template ListIterator<TemplateEntry>

#pragma define_template ListNode<Node>
#pragma define_template List<Node>
#pragma define_template ListIterator<Node>

#pragma define_template ListNode<Pair>
#pragma define_template List<Pair>
#pragma define_template ListIterator<Pair>

#pragma define_template ListNode<Unsafe>
#pragma define_template List<Unsafe>
#pragma define_template ListIterator<Unsafe>

#pragma define_template ListNode<Problem>
#pragma define_template List<Problem>
#pragma define_template ListIterator<Problem>

#pragma define_template ListNode<Plan>
#pragma define_template List<Plan>
#pragma define_template ListIterator<Plan>

#pragma define_template SListNode<StepId>
#pragma define_template SList<StepId>
#pragma define_template SListIterator<StepId>

#pragma define_template SListNode<Sym>
#pragma define_template SList<Sym>
#pragma define_template SListIterator<Sym>

#pragma define_template SearchQueue<Plan>

#endif
#endif
