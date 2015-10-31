/* Copyright (c) 2002,2004,2005 Marek Michalkiewicz
   Copyright (c) 2005, Carlos Lamas
   Copyright (c) 2005,2007 Joerg Wunsch
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/* $Id: stdint.h,v 1.10 2007/01/23 15:32:48 joerg_wunsch Exp $ */

/*
 * ISO/IEC 9899:1999  7.18 Integer types <stdint.h>
 */

#ifndef __STDINT_H_
#define __STDINT_H_



/** \ingroup avr_stdint
    8-bit signed type. */

#define int8_t signed char

/** \ingroup avr_stdint
    8-bit unsigned type. */

#define uint8_t unsigned char

/** \ingroup avr_stdint
    16-bit signed type. */

#define int16_t signed short int

/** \ingroup avr_stdint
    16-bit unsigned type. */

#define uint16_t unsigned short int

/** \ingroup avr_stdint
    32-bit signed type. */

#define int32_t signed  long int

/** \ingroup avr_stdint
    32-bit unsigned type. */

#define uint32_t unsigned long int

/** \ingroup avr_stdint
    64-bit signed type.
    \note This type is not available when the compiler
    option -mint8 is in effect. */

#define int64_t signed long long int

/** \ingroup avr_stdint
    64-bit unsigned type.
    \note This type is not available when the compiler
    option -mint8 is in effect. */

#define uint64_t unsigned long long int

/*@}*/



/** \name Integer types capable of holding object pointers
    These allow you to declare variables of the same size as a pointer. */

/*@{*/



/** \ingroup avr_stdint
    fastest signed int with at least 8 bits. */

#define int_fast8_t int8_t

/** \ingroup avr_stdint
    fastest unsigned int with at least 8 bits. */

#define uint_fast8_t uint8_t

/** \ingroup avr_stdint
    fastest signed int with at least 16 bits. */

#define int_fast16_t int16_t

/** \ingroup avr_stdint
    fastest unsigned int with at least 16 bits. */

#define uint_fast16_t uint16_t

/** \ingroup avr_stdint
    fastest signed int with at least 32 bits. */

#define int_fast32_t int32_t

/** \ingroup avr_stdint
    fastest unsigned int with at least 32 bits. */

#define uint_fast32_t uint32_t



#define int_fast64_t int64_t

/** \ingroup avr_stdint
    fastest unsigned int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */

#define uint_fast64_t uint64_t


/*@}*/


/** \name Greatest-width integer types
   Types designating integer data capable of representing any value of
   any integer type in the corresponding signed or unsigned category */

/*@{*/






#endif /* _STDINT_H_ */
