/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
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
      not allowed to use big constants such as 0xffffffff.
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
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x&~y)&~(~x&y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int y=x>>31;
  return (~x+1)&y;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int ss= src<<3;
  int sd= dst<<3;
  int byte=(x>>ss)&0xFF;
  int delete = x&~(0xFF<<sd);
  return delete | (byte <<sd);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int arith = x >> n;
  int mask = ~((1 << 31) >> n << 1);
  return arith & mask;
} 

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
    int mask = 0x0F;
    mask = (mask << 8) | mask;
    mask = (mask << 16) | mask;
    return ((x & mask) << 4) |(((x >> 4) & mask));}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int inv = ~x;
 int low1 = inv & (~inv + 1);
  int inv2 = inv ^ low1;
  return inv2 & (~inv2 + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
 x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1); 
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
    int s = n & 31;
    int left = (~s + 1) & 31;
    int mask = ~((1 << 31) >> s << 1);
    return ((x >> s) & mask) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int exp) {
    int mask = (1 << exp) + ~0;
    int frac = x & mask;
    int base = x & ~mask;
    int half = 1 << (exp + ~0);
    int greater = (half + (~frac + 1)) >> 31;
    int equal = !(frac ^ half);
    int odd = (base >> exp) & 1;
    int up = (greater & 1) | (equal & odd);
    return base + (up << exp);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int sx = x >> 31;
    int sy = y >> 31;
    int diffSign = sx ^ sy;
    int greater = (diffSign & !sx) |(!diffSign & !((x + (~y + 1)) >> 31));
    int mid = (x & y) + ((x ^ y) >> 1);
    int half = (x ^ y) & 1;
    return mid + (half & greater);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int d1 = x + ~a + 1;
    int d2 = x + ~b + 1;
    int diff = d1 ^ d2;
    int cond2 = (diff >> 31) & 1;
    int cond1 = !d1 | !d2;
    return cond1 | cond2;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int x4 = x << 2;
    int s = x >> 31;
    int ov1 = !!((x4 >> 2) ^ x);
    int result = x4 + x;
    int sr = result >> 31;
    int s4 = x4 >> 31;
    int ov2 = !(s4 ^ s) & (s ^ sr);
    int overflow = ov1 | ov2;
    int max = ~(1 << 31);
    int min = 1 << 31;
    int sat = (~s & max) | (s & min);
    int mask = !overflow + ~0;
    return (mask & sat) | (~mask & result);}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int s1 = x + y;
    int s2 = s1 + z;

    int sx = x >> 31;
    int sy = y >> 31;
    int sz = z >> 31;
    int s1s = s1 >> 31;
    int s2s = s2 >> 31;

    int ov1 = (~(sx ^ sy)) & (sx ^ s1s);
    int ov2 = (~(s1s ^ sz)) & (s1s ^ s2s);

    int p1 = ov1 & ~sx;
    int n1 = ov1 & sx;
    int p2 = ov2 & ~s1s;
    int n2 = ov2 & s1s;

    int pos = p1 | p2;
    int neg = n1 | n2;

    return (!!pos) + ~(!!neg) + 1;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & (1 << 31);
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & ~((~0) << 23);
    unsigned sig, prod, q, rem, inc;

    if (exp == 0xFF)
        return uf;

    if (exp == 0) {
        sig = frac;
    } else {
        sig = (1 << 23) | frac;
    }
    prod = sig * 3;
    q = prod >> 1;
    rem = prod & 1;
    inc = rem & (q & 1);
    q = q + inc;

    if (exp == 0) {
        if (q >= (1 << 23)) {
            exp = 1;
            frac = q - (1 << 23);
        } else {
            frac = q;
        }
    } else {
        if (q >= (1 << 24)) {
            unsigned rem2 = q & 1;
            q = q >> 1;
            if (rem2 && (q & 1))
                q = q + 1;
            exp = exp + 1;
        }

        if (exp >= 0xFF)
            return sign | (0xFF << 23);

        frac = q & ~((~0) << 23);
    }

    return sign | (exp << 23) | frac;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf >> 31;
    int exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & ((1 << 23) - 1);
    int e = exp - 127;

    if (exp == 0xFF)
        return uf;

    if (exp == 0) {
        return sign << 31;
    }

    if (e >= 23) {
        return uf;
    }

    if (e < 0) {
        if (e < -1) {
            return sign << 31;
        } else {
            if (frac == 0) {
                return sign << 31;
            } else {
                return (sign << 31) | (127 << 23);
            }
        }
    }

    unsigned shift = 23 - e;
    unsigned half = 1U << (shift - 1);
    unsigned mask = (1U << shift) - 1;
    unsigned frac_low = frac & mask;
    unsigned frac_int = frac & ~mask;

    unsigned round_up = 0;
    if (frac_low > half) {
        round_up = 1;
    } else if (frac_low == half) {
        round_up = ((1 << e) + (frac_int >> shift)) & 1;
    }

    frac_int = frac_int + (round_up << shift);
    if (frac_int & (1 << 23)) {
        exp = exp + 1;
        frac_int = frac_int & ((1 << 23) - 1);
    }
    if (exp >= 0xFF) {
        return (sign << 31) | (0xFF << 23);
    }
    return (sign << 31) | (exp << 23) | frac_int;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned absX;
    unsigned exp, frac;
    int shift;
    unsigned mant;
    int shiftAmt;

    if (x == 0) return 0;

    if (x < 0) {
        sign = 1;
        absX = -x;
    } else {
        absX = x;
    }

    shift = 31;
    while (!(absX & (1U << shift))) {
        shift = shift + ~0;
    }
    exp = shift + 127;

    shiftAmt = shift - 23;
    if (shiftAmt > 0) {
        mant = absX >> shiftAmt;
        unsigned rem = absX & ((1U << shiftAmt) - 1);
        unsigned half = 1U << (shiftAmt - 1);
        if (rem > half || (rem == half && (mant & 1))) {
            mant = mant + 1;
            if (mant & (1U << 24)) {
                mant = mant >> 1;
                exp = exp + 1;
            }
        }
    } else {
        mant = absX << (23 - shift);
    }
    frac = mant & ((1U << 23) - 1);
    return (sign << 31) | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int mask1 = 0x55 | (0x55 << 8);
    mask1 = mask1 | (mask1 << 16);

    int mask2 = 0x33 | (0x33 << 8);
    mask2 = mask2 | (mask2 << 16);

    int mask4 = 0x0F | (0x0F << 8);
    mask4 = mask4 | (mask4 << 16);

    int mask8 = 0xFF | (0xFF << 16);

    int mask16 = 0xFF | (0xFF << 8);

    x = (x & mask1) + ((x >> 1) & mask1);
    x = (x & mask2) + ((x >> 2) & mask2);
    x = (x & mask4) + ((x >> 4) & mask4);
    x = (x & mask8) + ((x >> 8) & mask8);
    x = (x & mask16) + ((x >> 16) & mask16);
    return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
    int mask4 = 0x0F | (0x0F << 8);
    mask4 = mask4 | (mask4 << 16);
    int mask2 = mask4 ^ (mask4 << 2);
    int mask1 = mask2 ^ (mask2 << 1);
    int mask8 = 0xFF | (0xFF << 16);
    int mask16 = 0xFF | (0xFF << 8);

    x = ((x >> 1) & mask1) | ((x & mask1) << 1);
    x = ((x >> 2) & mask2) | ((x & mask2) << 2);
    x = ((x >> 4) & mask4) | ((x & mask4) << 4);
    x = ((x >> 8) & mask8) | ((x & mask8) << 8);
    x = ((x >> 16) & mask16) | (x << 16);
    return x;
}
