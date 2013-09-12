#ifndef _BITSTRING_H_
#define _BITSTRING_H_
// I think this can be found by a dummy uint using sizeof.
//#include "global.h"

/*
 * This header file defines the bitstring class,  a contiguous block
 * of unsigned integers.  The UINTSIZE is machine dependent (oops...)
 * and is here defined as 4.
 * Many code borrowed from bit vector class from Lippman\'s C++. 
 * modified for unequal size bitstrings.
 * $Log: bitstring.h,v $
 * Revision 1.1  1993/07/04  05:06:19  ctkwok
 * Initial revision
 *
 */

/* Bug:  It seems trying to instantiate a BitString with "ON" is not
 * a good idea;  \'|\' and others doesn\'t work correctly
 */

#include <iostream.h>

#define UINTSIZE 32		 // Size of an unsigned integer (in bits)
#define SHIFTSIZE 5              // 32 == 2^5
#define MODBIT    0x1F           // 32 == 0x1F
enum {OFF=0, ON};

typedef unsigned int BitStrType;
typedef BitStrType *BitStr;	 // BitStr is of type pointer to BitString

#ifndef bool
typedef int bool;
#endif

class BitString {     
  friend ostream& operator<< (ostream&, const BitString&);
  // use this one if you want Empty(t|u);
  friend bool IsEmpty (const BitString& b) {return b.Empty();}

public:
  BitString(int sz=UINTSIZE, int init=OFF);     
  BitString(const BitString&);
  ~BitString();
  const BitString& operator=(const BitString &);
  void operator+=( int pos );	 // Turn on bit \'pos\'
  void operator-=( int pos );	 // Turn off bit \'pos\'
  bool operator==( int pos ) const;	 // check if bit at \'pos\' is on
  bool operator!=( int pos ) const;	 // check if bit at \'pos\' is off
  bool operator==(const BitString &) const;    // compare 2 bitstrings
  // return 1 if successful, 0 if not, -1 if oversized
  int In(int pos) const;
  // these operators does not allow some out-of-bound elem to exist
  void operator|=(const BitString&); 
  void operator&=(const BitString&); 
  void operator^=(const BitString&); 
  // reset all bits to off
  void Reset() {for (int i=0; i<num_u_int; i++) *(bs+i) = 0;}
  void SetOn() {for (int i=0; i<num_u_int; i++) *(bs+i) = ~0;}

  // These operators can handle unequal sizes
  // for correctness,  don\'t try to initiate a bitstring with ON
  BitString operator|(const BitString&) const; 
  BitString operator&(const BitString&) const; 
  BitString operator^(const BitString&) const; 
  bool Empty() const;			 // check if all bits are 0   

  int GetSize() const;
  // someone has to use this;
  static void PoolInitialize();
//private:
  int size;		         // number of bits : This and below,  may use diff types,  but I don\'t want errors at start :)
  BitStr bs;			 // bitstring
  int num_u_int;		 // num of unsigned int invoved
private:
//  getIndex( int pos ) const { return (pos / UINTSIZE); }
//  getOffset( int pos ) const { return (pos % UINTSIZE); }
  getIndex( int pos ) const { return (pos >>= SHIFTSIZE); }
  getOffset( int pos ) const { return (pos & MODBIT); }
  static BitStr Allocate(int needed);
  static void Deallocate(BitStr bs, int used);
private:
  static const int poolSize; // Each memory allocation size
  static BitStr* freeList;
};

#ifndef OUTLINE
#include "bitstring.icc"
#endif

#endif 				 //_BITSTRING_H_
