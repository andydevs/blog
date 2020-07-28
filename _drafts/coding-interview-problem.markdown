---
layout: post
title: "A Coding Interview Problem with a Brilliant Solution"
---

I found this problem on LeetCode. It was labeled hard, but a friend and I decided to take
it on. However, the solution that I came up with was so beautiful, I was inspired to make 
this post about it.

The Problem
---------------------------------------------------------------------------------------

Given an integer `n`, find the number of times the digit 1 appears in all non-negative 
numbers up to and including `n`.

_Example_

    Input (n): 13
    Output: 6
    Explanation: 1 appears once in 1, 10, 12, and 13 and twice in 11

The Brute-Force Approach
---------------------------------------------------------------------------------------

I always start with what is called a "brute force approach". In coding questions, there
often is an obvious but inefficient "brute force approach", and then there is the cool
solution that the interviewer is really looking for. I use the "brute force approach" 
just to get a baseline for how to approach the problem. After that, I would find the 
redundancies, places where the code is doing unnecessary work that I can shave off to 
make it more efficient. To do this, I look for patterns, which I will explore in the 
later sections.

For now, the brute force approach. The problem asks to count the number of times the
digit 1 appears in every number from 0 to `n`. So, the first instinct, brute force
approach would be to loop through each number from 0 to `n`, then loop through each 
digit in the number and increment a counter everytime we encounter a `1`.

__[explain how to isolate a digit]__

Some nomenclature, I'm using `i` as a prefix to indicate linear increments, `q` to
indicate logarithmic (multiplicative) increments, and `c` to indicate
a count.

```c++
class Solution {
public:
    int countDigitOnes(int n) {
        int cOnes = 0; // Total count of 1's
        int iNumber; // Current number being checked
        int qOrdMag, digit; // Current digit being analyzed

        // Loop through every number
        for (iNumber = 0; iNumber < n; ++iNumber) {
            // Loop through every digit
            for (qOrdMag = 1; qOrdMag <= n; qOrdMag *= 10) {
                // Get digit
                digit = iNumber / qOrdMag % 10;

                // If digit equals 1, increment count
                if (digit == 1) {
                    ++cOnes;
                }
            }
        }

        // Return final count
        return cOnes;
    }
}
```

Again this solution works, but it won't get you the job, because it's too costly, and,
depending on where this code is needed, it won't even be able to run. This code has
what is known in the business as an `O(n)` time complexity, which means that the time
it takes to complete the problem is directly proportional to the size of the number we
give it. It may be quick for, say, 13, but give it a big number like 231645 and it starts
to struggle a little bit. Do that thousands of times every second and those "little bits"
start to add up. Realistically, code like this would be running in these high-demand 
positions


The Pattern
-------------------------------------------------------------------------------------

So, as you start doing some counting, you might notice some patterns.

For example, you reason that _Every_ number from 10 to 19 must have a 1 in it
(because, you know, 10)

    [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] 20 ...

We also got another pattern, if you start at 1 and count up by 10, every number
has a 1 in it.

    [1] [11] [21] [31] [41] [51] [61] [71] [81] [91] ...

It's a time saver, but it still feels a bit random. There's also that pesky 11 that 
seems to break the pattern by having two 1's in it. How do we account for that?

### The Hidden Geometry

__[find a way to generate images for what I'm talking about]__

The pure genius of this problem comes from something you might do to save space while
counting to 99: arranging the numbers in a 10 by 10 grid.

      0  [ 1]   2    3    4    5    6    7    8    9
    [10] [11] [12] [13] [14] [15] [16] [17] [18] [19]
     20  [21]  22   23   24   25   26   27   28   29
     30  [31]  32   33   34   35   36   37   38   39
     40  [41]  42   43   44   45   46   47   48   49
     50  [51]  52   53   54   55   56   57   58   59
     60  [61]  62   63   64   65   66   67   68   69
     70  [71]  72   73   74   75   76   77   78   79
     80  [81]  82   83   84   85   86   87   88   89
     90  [91]  92   93   94   95   96   97   98   99

Right away you notice the pattern, all the 1's appearing from 10 to 19 appear
in a line, and all the 1's appearing from 1 to 91 counting up by 10 appear in
a line. There are two lines, each with 10 numbers in them. You may consider just
adding 10 + 10 to your count for every 100 for the two lines. Then you notice that 
11 appears in both lines, right where they intersect, so you'd end up counting it 
twice if you did that.

But 11 also has two 1's in it...

Let's try going up to 999. You may try stacking an extra grid on top of the previous 
one for each 100, making a cube of numbers.

![Image of 0 to 999 3D Grid]()

You reason that, for every digit in the 100's place, the same 10 to 19 and 1 to 
91 rows are repeated. This creates two vertical 2D planes that intersect at the line 
from 11 to 911

![Image of 0 to 999 3D Grid with Vertical Planes]()

But then you realize that every number from 100 to 199 has a 1 in it, so that creates
an entire horizontal plane as well.

![Image of 0 to 999 3D Grid With all Planes]()

Then you notice that these planes intersect each other forming 3 lines, so those lines of 
numbers will be counted twice. Guess what? Each of those numbers has two 1's. Check the 
cube and see for yourself! Furthermore, all three planes intersect at a single point, a 
single number that would be counted three times.

That number is 111.

Let's expand it to 0 to 9999. Here we would need to expand each plane that we've discovered 
to account for every digit in the 1000's place, creating 3 3D cubes. What's more, we get an extra
cube for every number from 1000 to 1999. All four of these cubes intersect at, you guessed it,
1111.

As you continue to do this you discover _another_ pattern, a meta-pattern, I would say:

From 0 to 9, we create a single 1D line of numbers, and we get 1 point (the number 1) that 
contains a 1. From 0 to 99, we get a 2D grid of numbers, which contains 2 1D lines, each 
are 10 numbers long, containing 1's. These two lines intersect at the number 11. From 0 to 
999, we get a 3D cube with 3 2D planes, each with 100 numbers containing 1's, that all 
intersect at 111. From 0 to 9999, a 4D hypercube containing 4 3D cubes of 1s intersecting 
at 1111.

And there's our solution. Reframing the problem in a visual manner let's us see hidden 
patterns that we would not expect.

### For Every Other Number

That is, still, only part of the solution. The problem asks for every one up to an 
arbitrary number `n`. So far we are assuming `n` was 9, 99, 999, etc. What if it wasn't. 
What if it was, say, 53.

Well, let's count up to 53.

      0  [ 1]   2    3    4    5    6    7    8    9
    [10] [11] [12] [13] [14] [15] [16] [17] [18] [19]
     20  [21]  22   23   24   25   26   27   28   29
     30  [31]  32   33   34   35   36   37   38   39
     40  [41]  42   43   44   45   46   47   48   49
     50  [51]  52   53

One thing that I didn't mention yet is the symmetry with which this pattern emerges. 
Every 10 numbers, the same pattern repeats. Same with every 100 numbers, every 1000 
numbers, etc..

This means we can break the problem down into individual digits!

      0  [ 1]   2    3    4    5    6    7    8    9
    [10] [11] [12] [13] [14] [15] [16] [17] [18] [19]
     20  [21]  22   23   24   25   26   27   28   29      +     50  [51]  52  53
     30  [31]  32   33   34   35   36   37   38   39
     40  [41]  42   43   44   45   46   47   48   49

So, let's consider each individual digit. How many ones appear from 0 to `n` if `n` 
was less than 10? The answer is dead simple, if `n` is greater than or equal to 1, 
there is only one 1, else there are none.

The Elegant Solution
-------------------------------------------------------------------------------------

```c++
class Solution {
public:
    int countDigitOne(int n) {
        // Declare variables
        int cOnes = 0;             // Total count of ones
        unsigned iOrdMag, qOrdMag; // Current order of magnitude being analyzed
        unsigned digit;            // Current digit being analyzed
        
        // Loop through each order of magnitude until we go above our number
        for (iOrdMag = 0, qOrdMag = 1; qOrdMag <= n; iOrdMag++, qOrdMag *= 10) {
            // Get current digit
            digit = n / qOrdMag % 10;

            // First off, if the digit is greater than 1, that 
            // means we got a special plane of ones to add
            // Add the current order of magnitude of ones
            // To account for the special plane
            if (digit > 1) { cOnes += qOrdMag; }
            // If the digit is EQUAL to 1, then we have a partial 
            // special plane that's equal in size to the number below this
            // digit (plus 1 for the zero). So we need to retroactively
            // get the size of the extra partial plane by finding the number
            // below our current order of magnitude (which can be done with
            // the mod operator)
            else if (digit == 1) { cOnes += n % qOrdMag + 1; }

            // Lastly, we add the remaining partial plane to in this dimension. 
            // The size of the partial plane equals the previous order of 
            // magnitude times the current order of magnitude number, times 
            // the digit. If the digit is 0, this entire expression is 0
            cOnes += digit * iOrdMag * (qOrdMag / 10);
        }

        // Return our final count
        return cOnes;
    }
};
```

This can work with any radix

```c++
class Solution {
public:
    int countDigitOne(int n) {
        // We are working with numbers of base 10
        // But this would work with any base number
        int radix = 10;
        
        // Declare variables
        int nOne = 0;
        unsigned int iOrdMag, qOrdMag;
        unsigned int digit;
        
        // Loop through each order of magnitude until we get to our max number
        for (iOrdMag = 0, qOrdMag = 1; qOrdMag <= n; iOrdMag++, qOrdMag *= radix) {
            // Get current digit
            digit = n / qOrdMag % radix;

            // First off, if we're greater than or equal to 1
            // That means we got a special plane of ones to add
            // Add the current order of magnitude of ones
            // To account for the special plane
            if (digit > 1) { nOne += qOrdMag; }
            // If we're EQUAL to 1, then we have a partial special
            // plane that's equal in size to the number below this
            // digit (plus 1 for the zero). So we need to retroactively
            // get the size of the extra partial plane by finding the number
            // below our current order of magnitude (which can be done with
            // the mod operator)
            else if (digit == 1) { nOne += n % qOrdMag + 1; }

            // Lastly if we are also greater than 0, we have a
            // remaining partial plane to add in this dimension. 
            // The size of the partial plane equals the previous 
            // order of magnitude times the current order of 
            // magnitude number,  times the digit
            if (digit > 0) { nOne += digit * iOrdMag * (qOrdMag / radix); }
        }

        // Return our final count
        return nOne;
    }
};
```

Conclusion
-------------------------------------------------------------------------------------