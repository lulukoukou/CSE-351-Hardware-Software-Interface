/*
 * CSE 351 Lab 1 (Data Lab )
 *
 *QIHAN ZHAO (1726473)
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>. The included file, "common.c" contains a function declaration
 * that should prevent a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xFFFFFFFF.
     However you are allowed to add constants to values greater
     than 255. e.g. 250+250 = 500.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, ?, ==, or !=:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
  greater than or equal to the number of bits in the value being shifted.
  e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
  e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
  Undefined means you do not know what result you will get from the operation.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */

// Rating: 1
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
// based on the DeMorgan's Law. a & b = not(not a or not b)
int bitAnd(int x, int y) {
       int res = ~((~x) | (~y));
  return res;
}
// based on the DeMorgan's Law. a ^ b = (not (a and b)) and not (not a and not b)
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //int res = (~(~x & y) & (~(x & ~y))); 
  int res = (~(x & y))&(~(~x & ~y));
  return res;
}
/*
 * thirdBits - return 32-bit quantity with every third bit
 * (starting from the least significant bit) set to 1 (other bits set to zero).
 * Further clarification: for every bit from and including the least significant 
 * bit, each bit at an index that is a multiple of three should be set to 1.
 * This is represented by the set {0, 3, 6, 9,...}. All other bits should be
 * set to 0.
 *   Example: ....1001001
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */

// res = 1
// res = 1 00 1
// res = 1001 00 1001
// res = 1001001001001 00 1001001001
int thirdBits(void) {
  int res = 1;
  res = 1   + (res << 3);
  res = res + (res << 6);
  res = res + (res << 12);
  res = res + (res << 24);
  return res;
}
// Rating: 2
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
// ~0 = -1
// can be represented => -pow(2, n-1) <= x <= pow(2, n-1)-1
// if the most significant bit is different from the (n-1)th bit, it will be outside the range, shoud return false
int fitsBits(int x, int n) {
  int pow = n + (~0);
  int res = (x >> pow) ^ (x >> 31);
  return !res;
}
/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
// !!x check zero by returing all zeros, nonzero by returing 1
// if res return 0, it could be positive or zero,
// if res return 1, it could only be negaitve nonzero
int sign(int x) {
  int res = (x >> 31) ^ 0;
  return (res | !!x);
}
/*
 * getByte - Extract byte n from int x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
// 1 byte = 8 bits, pow = power(2,3)
// bitmask will mask all the other bits by doing & with 0
int getByte(int x, int n) {
  int pow = n << 3;
  int mask = 0xff;
  int res = (x >> pow) & mask; 
  return res;
}
// Rating: 3
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
// logicalshift will append 0 at the beginning instead of MSB
// do right arithmetic shift at first
// bitmask 0111 1111...
// & 0 will focus bits to be zero
int logicalShift(int x, int n) {
  int res;
  int mask = 0x7f;
  mask = (mask << 8) + 0xff;
  mask = (mask << 8) + 0xff;
  mask = (mask << 8) + 0xff;
  //print_binary ((mask>>n));
  //print_binary (mask >> (n + (~0)));
  mask = ((mask >> n) << 1) + 1;
  res = (x >> n) & mask;
  return res;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
// if sign1 return 1, x and sum in opposite sign,
// then if x and y is the same sign, overflow happens
// if sign1 return 0, x and sum in same sign,
// then if x and y is the same sign, does not overflow
// if sign2 return 1, x and y in opposite sign, it will not cause overflow anyway
int addOK(int x, int y) {
  int sum = x + y;
  int sign1 = (x >> 31) ^ (sum >> 31);
  int sign2 = (x >> 31) ^ (y >> 31);
  int res = !((sign1) & (~sign2));
  return res;
}
/*
 * invert - Return x with the n bits that begin at position p inverted
 *          (i.e., turn 0 into 1 and vice versa) and the rest left
 *          unchanged. Consider the indices of x to begin with the low-order
 *          bit numbered as 0.
 *   Can assume that 0 <= n <= 31 and 0 <= p <= 31
 *   Example: invert(0x80000000, 0, 1) = 0x80000001,
 *            invert(0x0000008e, 3, 3) = 0x000000b6,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
// pow = -1
// xor 1 will invert 1 to 0, invert 0 to 1
// bitmask from p to p+n should be 1, others should be 0
int invert(int x, int p, int n) {
  int pow = ~0;
  //print_binary((pow << p));
  //print_binary((pow << (p+n)));
  int mask = (pow << (p + n)) ^ (pow << p);
  return x ^ mask;
}
// Rating: 4
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
// logical not
// 0 -> 1, other -> 0
// if sign of x and -x are 0, x should be zero
// else if x should be nonzero
int bang(int x) {
  //print_binary(x >> 31);
  //print_binary( (x >> 31) & 1);
  int sign1 = (x >> 31) & 1;
  int sign2 = ((~x + 1) >> 31) & 1;
  int res = sign1 | sign2;
  return res ^ 1;
}
// Extra Credit: Rating: 4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
// sign1: if x and x - 1 returns 0 (no same bits), it is power of 2 (has to be positive)
// sign2: return 0 if negative, which is not power of 2, else if return 1
// sign3: !!x return 0, if x is zero, which is not power of 2
// sign: if sign2 return 0, not power of 2; if sign2 return 1 and sign3 return 0, x is 0 and is not power of 2; if sign2 return 1 and sign3 return 1,it depends on sign1
 
int isPower2(int x) {
  int sign1 = !(x & (x + ~0));
  int sign2 = (x >> 31) ^ 1;
  //print_binary(!!1);
  int sign3 = !!x;
  int sign = sign2 & sign3;
  return (sign1 & sign);
}

