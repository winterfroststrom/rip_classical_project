// 	$Id: utility.h,v 1.2 1993/07/06 22:58:55 ctkwok Exp ctkwok $	
// utility.h -- some useful stuff 
//
// Copyright (c) 1992 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

//#include "copyright.h"

// Wrap everything that is actually C with an extern "C" block.
// This prevents the internal forms of the names from being
// changed by the C++ compiler.
#ifndef UTILITY_H
#define UTILITY_H
#include <stdarg.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define max(a,b)  (((a) > (b)) ? (a) : (b))

// Boolean values.  This is the same definition as in the g++ library.
// how about making this short
#ifndef bool
typedef int bool;
#endif

// GC:  ref counting
typedef short Ref;

#define FALSE 0
#define TRUE 1
//enum { FALSE = 0, TRUE = 1 } bool;

// This declares the type "VoidFunctionPtr" to be a "pointer to a
// function taking an integer argument and returning nothing".  With
// such a function pointer (say it is "func"), we can call it like this:
//	(*func) (17);
typedef void (*VoidFunctionPtr)(int arg); 

// Enable selected debug messages.
//   '+' -- turn on all debug messages
//   't' -- thread system
//   's' -- semaphores, locks, and conditions
//   'i' -- interrupt emulation
//   'm' -- machine emulation
//   'd' -- disk emulation (in homework 2)
//   'f' -- file system (in homework 2)
//   'a' -- address spaces (in homework 3)
//   'n' -- network emulation (in homework 5)
extern void DebugInit (char* flags);

// Is this debug flag enabled?
extern bool DebugIsEnabled(char flag);

// Print debug message if flag is enabled
//extern void DEBUG (char flag, char* format, ...);
#ifdef DEBUG
#define _ACTION_ 1
#define _PLAN_   2
#define _LINK_   3
#define _UNSAFE_ 4
#define _BIND_   5
#define _CONSTR_ 6
#define _TEMPL_  7
#define _PROBLEM_ 8
#define _ORDER_ 9
#define _DEL_ 10
#define _VAR_ 11
#define _SEARCH_ 12
#define ASSERT(condition)						      \
  if (!(condition)) {							      \
  									      fprintf(stderr, "Assertion failed: line %d, file \"%s\"\n",	      \
		__LINE__, __FILE__);					      \
	abort();							      \
    }

#include "bitstring.h"

extern BitString debugFlags;

#define  DBG(flag, anything)  if (debugFlags==flag) anything
#else
#define ASSERT(condition) /* nothing */
#define  DBG(flag, anything)  /*nothing*/
#endif

//#include "gc.h"
// If the condition is false, print a message and dump core. 
//
// Useful for documenting assumptions in the code.

// The below isn\'t useful

// From here down are some routines used to simplify the emulation software
#ifdef HW2
// open/read/write/lseek/close, and check for error
extern int Open(char *name, int flags, int mode);
extern void Read(int fd, char *buffer, int nBytes);
extern void Write(int fd, char *buffer, int nBytes);
extern void Lseek(int fd, int offset, int whence);
extern void Close(int fd);
#endif

#ifdef HW3
// Check file to see if there are any characters to be read without waiting
extern bool PollFile(int fd);
#endif

#endif
