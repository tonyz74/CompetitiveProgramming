## Brute Force:

**ABC319 (C) - False Hope**

Iterate through all possible combinations (9!), then list out all bad ones.

**ABC321 (C) - 321 Searcher**

List out all possible 321 numbers, sort them, then index. There are only 1023 possibilities (this is because 0 to 9, no repeats, has at max $2^{10} - 1$ possibilites).

## Greedy:

**ABC319 (D) - Minimum Width**

Convert into a subproblem of finding the minimum lines required for a given width W. This subproblem is greedy: it's best to just keep putting words until you exceed W.

Use this in a binary search.

## Implementation:

**ABC319 (C) - False Hope**

Use `next_permutation` on an array specifying order of each element (`order[a] > order[b]` means that `a` appears after `b`).

Iterate through all possible lines, checking if the order makes it disappointing.


**ABC320 (C) - Slot Strategy (Easy)**

Just simulate. Keep a `visited` array and an `order` array. Generate `order` of picking (because there's only 6 total orderings of which to pick) with `next_permutation`.

Add things into an array based on if they exist in `S[1|2|3]` at that moment in time (if not visited), and sort that using a custom sort function based on `order`.

Pick the top of the sorted array, and mark it as visited.

## Math:

## Preprocessing:

**ABC319 (E) - Bus Stops**

Notice periodicity of the buses arriving. $P_{i}$ has max value of 8, so we can preprocess to include all the cases and do modulo on each query time.

**CF 895 (E) - Data Structures Fan**

Use a prefix XOR array. Notice that flipping the bits in a certain region just means XOR-ing by the values of that region (XOR 'adds' or 'removes' the element).

## Graphs & Trees

**ABC321 (E) - Complete Binary Tree**

Left child of node $\rightarrow$ $2 \times \text{self} $.
Right child of node $\rightarrow$ $2 \times \text{self} + 1 $.

Using this, we can solve the subproblem of finding nodes of a distance `K` that are strictly in the subtree of any node.

Then, just repeatedly do this while going up and decreasing the required distance, finding the valid nodes in the other half next to the original subtree.

There will be $\log_2(\text{max N})$ or roughly 60 operations at most. Discard when greater than this, to prevent overflow.

## Harder Data Structures:

## Binary Search:

## Dynamic Programming:

## Shortest Path:
