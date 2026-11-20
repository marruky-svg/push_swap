*This project has been created as part of the 42 curriculum by gbaccell, elsouza.*

<div align="center">

# 🔢 push_swap

**Sorting integers with two stacks, eleven moves and as few operations as possible.**

![Language](https://img.shields.io/badge/language-C-blue)
![School](https://img.shields.io/badge/school-42%20Porto-black)
![Group](https://img.shields.io/badge/group-2%20learners-green)
![Strategies](https://img.shields.io/badge/strategies-4-orange)

</div>

---

## 📑 Table of Contents

- [Description](#-description)
- [Instructions](#-instructions)
- [The Rules of the Game](#-the-rules-of-the-game)
- [Disorder Metric](#-disorder-metric)
- [Algorithms](#-algorithms)
- [Adaptive Strategy](#-adaptive-strategy)
- [Performance](#-performance)
- [Bonus — checker](#-bonus--checker)
- [Project Structure](#-project-structure)
- [Contributions](#-contributions)
- [Resources](#-resources)

---

## 📖 Description

`push_swap` is an algorithm project from the 42 Common Core. The program receives a list of integers, loads them into **stack `a`** (with **stack `b`** empty), and prints the **shortest sequence of operations** it can find that leaves `a` sorted in ascending order, with the smallest number on top.

The goal is not just to sort, but to **think about algorithmic complexity in a concrete way**: the cost of each algorithm is measured in the number of push_swap operations it generates, not in CPU time.

The program embeds **four sorting strategies**:

| Strategy | Technique | Complexity (in operations) |
|---|---|---|
| `--simple` | Cheapest insertion ("Turk") | **O(n²)** |
| `--medium` | Chunk-based sorting (√n chunks) | **O(n√n)** |
| `--complex` | Three-way quicksort over four stack ends | **O(n log n)** |
| `--adaptive` *(default)* | Chooses one of the above based on the measured disorder | depends on the regime |

It also includes a **benchmark mode** (`--bench`) that reports the disorder, the strategy used, its complexity class and the count of every operation, and, as a bonus, a **`checker`** program that verifies a sequence of operations.

---

## 🛠 Instructions

### Compilation

```bash
make          # builds libft and then push_swap
make bonus    # builds the checker (bonus)
make clean    # removes object files
make fclean   # removes object files, libft.a, push_swap and checker
make re       # rebuilds everything from scratch
```

Compiled with `cc -Wall -Wextra -Werror`. The project's `Makefile` builds `libft` with its own `Makefile` and does not relink.

### Usage

```bash
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <numbers...>
```

- The **first number is the top** of stack `a`.
- Numbers can be passed as separate arguments or in a single quoted string: `./push_swap 3 2 1` or `./push_swap "3 2 1"`.
- Flags must come **before** the numbers. Only **one** strategy flag is allowed; `--bench` can be combined with any of them.
- With no arguments, the program prints nothing and gives the prompt back.

### Examples

```bash
# Default (adaptive) strategy
$ ./push_swap 2 1 3 6 5 8

# Force a strategy
$ ./push_swap --simple 5 4 3 2 1

# Count the operations
$ ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# Verify the result with the provided checker (or our own: ./checker)
$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK

# Large random input
$ ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' '); ./push_swap $ARG | ./checker_linux $ARG
OK
```

### Benchmark mode

`--bench` prints the metrics to **stderr** after sorting, so the operations on stdout stay clean and can still be piped to the checker.

```bash
$ ./push_swap --bench $ARG 2>&1 >/dev/null
[bench] disorder: 51.36%
[bench] strategy: Adaptive / O(n log n)
[bench] total_ops: 4158
[bench] sa: 133 sb: 0 ss: 0 pa: 950 pb: 950 ra: 515 rb: 506 rr: 199 rra: 447 rrb: 444 rrr: 14
```

For the adaptive strategy, the name shows the strategy that was **requested** and the complexity shows the class of the strategy that was **actually used**.

### Error handling

The program prints `Error` followed by `\n` on **stderr** when:

- an argument is not a valid integer (`one`, `12a`, `-`, `""`);
- a number is outside the `int` range;
- a number appears more than once;
- an unknown flag is given, or more than one strategy flag is given.

```bash
$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

---

## 🎮 The Rules of the Game

| Operation | Effect |
|---|---|
| `sa` / `sb` | Swap the first two elements of `a` / `b` |
| `ss` | `sa` and `sb` at the same time |
| `pa` / `pb` | Move the top of `b` to `a` / the top of `a` to `b` |
| `ra` / `rb` | Rotate up: the first element becomes the last |
| `rr` | `ra` and `rb` at the same time |
| `rra` / `rrb` | Rotate down: the last element becomes the first |
| `rrr` | `rra` and `rrb` at the same time |

### Data structure

Each stack is a **circular doubly linked list**:

```
          ┌──────────────────────────────────┐
          ▼                                  │
 top → [ 3 ] ⇄ [ 0 ] ⇄ [ 4 ] ⇄ [ 1 ] ⇄ [ 2 ] ─┘
          ▲                              │
          └──── top->previous = bottom ──┘
```

Because the list is circular, `top->previous` is always the bottom element. This makes **`rotate` and `reverse rotate` O(1)**: they only move the `top` pointer. `swap` and `push` only relink a few pointers, so every operation runs in constant time.

---

## 📐 Disorder Metric

Before any move is made, the program measures how far stack `a` is from being sorted:

```
disorder = inversions / total_pairs
```

An **inversion** is any pair `(i, j)` with `i < j` and `a[i] > a[j]`.

- `0` → already sorted
- `1` → sorted in reverse order
- random input → around `0.5`

The computation compares every pair once, so it costs **O(n²) time and O(1) space**. It does not generate any push_swap operation.

---

## 🧠 Algorithms

### Normalization (preparation step)

Before sorting, the values are replaced by their **rank** (0 … n‑1):

```
[ 42, -7, 1000, 3 ]  →  [ 2, 0, 3, 1 ]
```

The relative order does not change, so the generated operations are identical. It removes negative and very large values, which makes chunks easy to define and gives the quicksort exact pivots without searching. It uses a temporary array (O(n) space) and is not counted as push_swap operations.

### Small inputs (2 to 5 numbers)

For very small stacks, all strategies use dedicated routines:

- **2 numbers**: at most one `sa`.
- **3 numbers**: put the largest at the bottom (`ra` or `rra`), then `sa` if needed. **At most 2 operations** for all 6 permutations.
- **4–5 numbers**: push the one or two smallest to `b`, sort the remaining 3, push them back.

### 1️⃣ Simple — Cheapest insertion ("Turk") · O(n²)

An insertion sort in which every element is inserted at the place where it costs the fewest operations:

1. `pb` two elements, so that `b` has a maximum and a minimum.
2. While `a` has more than 3 elements: for **every** element of `a`, compute how many rotations are needed to bring it to the top of `a` **and** to bring its target position to the top of `b` (`b` is kept in **descending** order). Four combinations are tried (up/down in each stack); when both stacks rotate in the same direction the shared rotations become `rr`/`rrr`, so the cost is the larger of the two and not the sum. Apply the cheapest one and `pb`.
3. Sort the last 3 elements of `a` with `sort_three`.
4. Bring every element of `b` back to its place in `a` (`pa`).
5. Rotate `a` until its minimum is at the top.

**Upper bound:** there are `n` insertions and each one costs at most `n` rotations plus one push, so `ops = O(n²)`. Choosing the cheapest element evaluates `n` candidates for each insertion, which is O(n²) evaluations per insertion in CPU time, but this does not generate operations.

**Why it fits low disorder:** when the input is almost sorted, most elements already have their target right next to them, so most insertions cost 0 or 1 rotation.

**Space:** O(1) auxiliary (only stack `b`).

> **First version.** The simple strategy was first a minimum extraction (an adaptation of selection sort). Testing showed it does not take advantage of partial order: with 500 numbers each moved a few dozen positions away from their place (disorder ≈ 15%), it reached **21 000 operations**, because each displaced element forces a rotation of almost the whole stack. It was replaced by the cheapest insertion, which uses about 4 300 operations on the same inputs.

### 2️⃣ Medium — Chunk sort · O(n√n)

The ranks `0 … n‑1` are split into ranges of size `k ≈ 2√n`. A counter `i` tracks how many numbers have already been pushed to `b`.

**Phase 1: push by chunks.** For the element on top of `a`:

| Condition | Action | Why |
|---|---|---|
| `top ≤ i` | `pb` + `rb` | very small → goes to the **bottom** of `b` |
| `top ≤ i + k` | `pb` | in the current chunk → stays on **top** of `b` |
| otherwise | `ra` | too big, not its turn yet |

As `i` grows, the accepted range moves forward, so every element is eventually pushed. Stack `b` ends up **almost sorted**, with the largest values near the top.

**Phase 2: push back the maximum.** While `b` is not empty, bring its maximum to the top (shortest path with `rb` / `rrb`) and `pa`.

**Upper bound:**
- Phase 1: there are about `n/k` chunks, and each chunk needs at most one full pass over `a` (≤ `n` rotations). That gives `(n/k) · n = O(n√n)`.
- Phase 2: the maximum of `b` is always within about `k` positions of the top or bottom, so each `pa` costs `O(k)`, which gives `n · k = O(n√n)`.

The factor 2 in `k = 2√n` is a constant, so it reduces the number of operations without changing the complexity class.

**Space:** O(1) auxiliary. √n is computed with an integer loop, without `math.h`.

### 3️⃣ Complex — Three-way quicksort · O(n log n)

A **segment** is a set of consecutive ranks (`lo … lo+k−1`) sitting together at one of the four ends of the stacks: top of `a`, bottom of `a`, top of `b`, bottom of `b`. A segment of `k` elements is split into **thirds by rank**, with limits `p1 = lo + k/3` and `p2 = lo + 2k/3`, and each element goes straight to the end where its third will be processed:

| Segment at | upper third → | middle third → | lower third → |
|---|---|---|---|
| top of `a` | bottom of `a` (`ra`) | top of `b` (`pb`) | bottom of `b` (`pb rb`) |
| bottom of `a` | top of `a` (`rra`) | top of `b` (`rra pb`) | bottom of `b` (`rra pb rb`) |
| top of `b` | top of `a` (`pa`) | bottom of `a` (`pa ra`) | bottom of `b` (`rb`) |
| bottom of `b` | top of `a` (`rrb pa`) | bottom of `a` (`rrb pa ra`) | top of `b` (`rrb`) |

Every move takes two steps: bring the element to the top of its own stack (`rra`/`rrb` if it is at a bottom), then send it from that top to the destination. The three thirds are then sorted recursively, **upper first, then middle, then lower**, so each one ends sorted on top of the previous one in `a`.

- A segment at the bottom of a stack that occupies the **whole** stack is treated as being on top (saves one reverse rotation per element).
- Segments of **at most 3** elements are brought to the top of `a` and sorted with a short fixed sequence: a 3-element bubble sort using `sa` and `pb sa pa` (at most 5 operations, optimal by exhaustive search), or `sort_three` when `a` holds only those 3.

**Upper bound:** because the stack is normalized, every third again has consecutive ranks, so the pivots are always **exact**: the quadratic worst case of the classic quicksort cannot happen. Each recursion level moves every element once with at most 3 operations, and each level divides the size by 3:

| n | sizes of the largest segment | levels | bound (3 · n · levels) | measured (mean) |
|---|---|---|---|---|
| 100 | 100 → 34 → 12 → 4 | 4 | 1 200 | ≈ 617 |
| 500 | 500 → 167 → 56 → 19 → 7 | 5 | 7 500 | ≈ 4 146 |

```
ops ≤ 3 · n · ⌈log₃ n⌉  =  O(n log n)
```

**Space:** O(log n) for the recursion.

### Operation buffer and peephole pass

The operations are not printed immediately: `record_op` stores their codes in a buffer that **doubles** its capacity when full (each code is copied fewer than two times on average; `realloc` is not allowed). When the sort ends, `flush_ops` rewrites adjacent pairs and only then prints and counts:

| Pair | Becomes |
|---|---|
| `ra rb` / `rb ra` | `rr` |
| `rra rrb` / `rrb rra` | `rrr` |
| `sa sb` / `sb sa` | `ss` |
| `pa pb`, `pb pa`, `ra rra`, `rb rrb`, `rr rrr`, `sa sa`, `sb sb`, `ss ss` | nothing (they cancel) |

Every rule keeps the final state unchanged. The `--bench` counts are taken **after** this pass, so they describe what is actually printed. It saves about 6–9 % on the quicksort and about 3 % on the chunk sort.

---

## 🎯 Adaptive Strategy

The default strategy measures the disorder first, then picks the method whose complexity fits that regime, as required by the subject:

| Disorder | Method used | Complexity |
|---|---|---|
| `< 0.2` | Simple (cheapest insertion) | O(n²) |
| `0.2 ≤ d < 0.5` | Medium (chunks) | O(n√n) |
| `≥ 0.5` | Complex (three-way quicksort) | O(n log n) |

### Rationale for the thresholds

- **Low disorder (< 0.2):** most elements are already close to their final position, so inserting each one into its place costs very few rotations. The cheapest insertion exploits this directly: it always picks the element that is nearest to its target. *Measured: 500 numbers with ≈ 15% disorder → about 4 300 operations (max 4 523 over 25 runs); 100 numbers → about 500 (max 559).*
- **Medium disorder (0.2 – 0.5):** the input is partially ordered. Chunks exploit this structure: elements of the same range tend to be close to each other, so fewer `ra` are spent skipping elements.
- **High disorder (≥ 0.5):** the input behaves like random data, or worse. The three-way quicksort has exact pivots, so its bound of `3n·⌈log₃ n⌉` operations holds **regardless of the initial order**, and in practice it uses about 4 150 operations for 500 numbers whatever the disorder.

The thresholds `0.2` and `0.5` are the ones defined by the subject. They split the range between "almost sorted", "partially sorted" and "random or reversed" input.

> **Note.** On random input of 500 numbers, the disorder is almost always between 0.45 and 0.55, so about half of the official benchmarks use the chunk sort and half the quicksort. Both stay under the "excellent" threshold in our measurements: the chunk sort reached at most 5 385 operations in 60 random runs (a narrow margin), the quicksort at most 4 192. If the chunk sort's margin is considered too small, the medium regime can use the quicksort instead (an O(n log n) method also respects the O(n√n) ceiling); it is a one-line change in `resolve_strat`.
---

## 📊 Performance

Random distinct integers. Every output was replayed by an independent verifier and checked with `checker`.

| Input size | `--simple` | `--medium` | `--complex` | Default (adaptive) | Excellent |
|---|---|---|---|---|---|
| 3 | ≤ 2 | ≤ 2 | ≤ 2 | ≤ 2 | — |
| 5 | ≤ 10 | ≤ 10 | ≤ 10 | ≤ 10 | — |
| 100 | ~558 (max 620) | ~581 (max 633) | ~618 (max 645) | ~596 (max 643) | < 700 ✅ |
| 500 | ~5 093 (max 5 350) | ~5 160 (max 5 385) | ~4 145 (max 4 192) | ~4 600 (max 5 386) | < 5 500 ✅ |

(Maxima measured over 300 runs for 100 numbers and 60 runs for 500 numbers.)

**Low-disorder input** (each number moved a few dozen positions from its place, disorder ≈ 15%), where the default strategy uses the simple method:

| Input size | Default (adaptive) | Excellent |
|---|---|---|
| 100 | ~504 (max 559) | < 700 ✅ |
| 500 | ~4 289 (max 4 523) | < 5 500 ✅ |

All permutations of 1 to 6 numbers were tested exhaustively with every strategy: all `OK`.

---

## ✅ Bonus — checker

```bash
make bonus
$ ./push_swap 3 2 1 0 | ./checker 3 2 1 0
OK
$ printf 'sa\nrra\npb\n' | ./checker 3 2 1 0
KO
$ ./checker 3 2 one 0
Error
```

`checker` takes the same list of integers (same parsing and errors as `push_swap`, without flags), reads one instruction per line from stdin and executes it with the **primitives** (so nothing is printed). At the end it prints `OK` if `a` is sorted and `b` is empty, `KO` otherwise. An unknown instruction, an empty line or a last line without `\n` prints `Error` on stderr. With no arguments it prints nothing.

---

## 🗂 Project Structure

```
push_swap/
├── Makefile
├── push_swap.h          # types, enums and prototypes
├── main.c               # program flow
├── parse_flags.c        # --simple, --medium, --complex, --adaptive, --bench
├── parse_args.c         # number validation, overflow and duplicates
├── errors.c             # "Error\n" on stderr + cleanup
├── stack_utils.c        # node creation, insertion, duplicate check, free
├── stack_query.c        # is_sorted, find_min_pos, find_max_pos, get_max
├── primitives.c         # swap, push, rotate, rev_rotate (no output)
├── ops_swap_push.c      # sa, sb, ss, pa, pb
├── ops_rotate.c         # ra, rb, rr
├── ops_rev_rotate.c     # rra, rrb, rrr
├── record.c             # stores each operation in a growable buffer
├── optimize.c           # peephole pass, then prints and counts the operations
├── moves.c              # bring_to_top_a / bring_to_top_b (shortest path)
├── disorder.c           # disorder metric
├── index.c              # normalization to ranks 0 … n-1
├── sort_small.c         # 2, 3, 4 and 5 elements
├── sort_simple.c        # O(n²)       cheapest insertion (Turk)
├── turk_target.c        # Turk: target position in a and in b
├── turk_rot.c           # Turk: cost of the 4 rotation combinations, rr/rrr
├── sort_medium.c        # O(n√n)      chunk sort
├── sort_complex.c       # O(n log n)  three-way quicksort (partition + recursion)
├── quick_loc.c          # quicksort: read / move an element between the 4 ends
├── dest_loc.c           # quicksort: destination of each third, normalization
├── quick_base.c         # quicksort: segments of at most 3 elements
├── dispatch.c           # strategy selection and sorting flow
├── bench.c              # --bench output
├── checker_bonus.h      # bonus: checker prototypes
├── checker_bonus.c      # bonus: checker main
├── checker_utils_bonus.c # bonus: read a line, map it to an operation, execute it
└── libft/               # our own C library
```

---

## 👥 Contributions

This project was developed by two learners. Both of us took part in the design discussions, reviewed each other's code and are able to explain every part of the project.

### elsouza
- Initial architecture: `push_swap.h`, data types and the circular doubly linked list
- Stack primitives (`swap`, `push`, `rotate`, `rev_rotate`) and the 11 official operations
- Operation recording and counting (`record.c`)
- Argument and flag parsing, input validation and error handling
- Disorder metric (`disorder.c`)
- Base of `main.c` and the stack utilities
- Quicksort location helpers: reading and moving an element between the four ends (`quick_loc.c`), destinations of the thirds and normalization of a location (`dest_loc.c`)
- Integration of the three-way quicksort, the cheapest insertion (simple strategy), the operation buffer and the bonus checker

### gbaccell
- Normalization (`index.c`)
- Sorting algorithms: small cases, first version of simple (minimum extraction), medium (O(n√n)) and first version of complex (radix sort)
- Movement helpers and stack queries (`moves.c`, `stack_query.c`)
- Strategy dispatch and adaptive logic (`dispatch.c`)
- Benchmark mode (`bench.c`)
- Testing with the checker, performance measurement and this README

---

## 📚 Resources

### References
- [Big O notation — Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation)
- [Inversion (discrete mathematics) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)) — the basis of the disorder metric
- [Insertion sort — Wikipedia](https://en.wikipedia.org/wiki/Insertion_sort) — the idea behind the cheapest insertion
- [Selection sort — Wikipedia](https://en.wikipedia.org/wiki/Selection_sort) — used in our first version of the simple strategy
- [Bucket sort — Wikipedia](https://en.wikipedia.org/wiki/Bucket_sort) — the idea behind chunk sorting
- [Radix sort — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort) — used in our first version
- [Quicksort — Wikipedia](https://en.wikipedia.org/wiki/Quicksort) and C. A. R. Hoare, "Quicksort", *The Computer Journal* 5(1), 1962
- J. L. Bentley, M. D. McIlroy, "Engineering a sort function", *Software: Practice and Experience* 23(11), 1993 — three-way partitioning
- [Peephole optimization — Wikipedia](https://en.wikipedia.org/wiki/Peephole_optimization)
- [Doubly linked list — Wikipedia](https://en.wikipedia.org/wiki/Doubly_linked_list)
- [Bitwise operations in C — Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)
- The push_swap subject (v1.2) and the `checker_linux` binary provided by 42

### Use of AI

We used **Claude** (Anthropic) as a learning assistant, in line with the AI guidelines of the subject:

- **Organization:** splitting the project into files and functions, setting the order of implementation, and keeping track of what was done and what was left.
- **Help with reasoning:** explanations of concepts we had not used before, such as bitwise operations (`>>` and `&`), traversing a circular list, the idea behind chunk sorting and radix sort, and complexity arguments. Each function was explained with its idea, its steps and an incomplete skeleton, which **we filled in ourselves**. The errors we made were explained to us so that we could fix them and understand why they were wrong.
- **Testing:** running the program against the checker with random inputs of different sizes, every strategy and edge cases (already sorted input, duplicates, invalid arguments, `int` limits), and measuring the number of operations for the benchmarks.

- **Code generation (later stage):** after the mandatory part was working with radix sort, the three-way quicksort (partition, recursion and base case in `sort_complex.c` and `quick_base.c`), the cheapest insertion used by the simple strategy (`sort_simple.c`, `turk_target.c`, `turk_rot.c`, after testing showed the minimum extraction failed on low-disorder input), the operation buffer and peephole pass (`record.c`, `optimize.c`) and the bonus `checker` (`checker_*_bonus.*`) were generated with Claude, then integrated, tested and studied by us. The location helpers they rely on (`quick_loc.c`, `dest_loc.c`) were written by elsouza, step by step, with explanations and reviews.

Everything else was written by us. We reviewed all of it together, including the generated parts, and can explain and defend every part of it.
