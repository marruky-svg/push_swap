*This project has been created as part of the 42 curriculum by elsouza.*

# libft

## Description

**libft** is the first project of the 42 Common Core. The goal is to re-implement a
set of functions from the C standard library, plus a few extra utilities, and package
them as a static library (`libft.a`) that can be reused in later 42 projects.

Since the standard library is not available "for free" in most 42 projects, writing it
from scratch is a way to understand what actually happens behind `strlen`, `memcpy` or
`malloc`-based helpers: how memory is laid out byte by byte, how strings are just arrays
ending in `'\0'`, how unsigned arithmetic can overflow, and who is responsible for
freeing each allocation.

The library is split into three parts, all of them mandatory:

- **Part 1 – Libc functions:** re-implementations of standard functions with the same
  prototype and behaviour as the originals (prefixed with `ft_`).
- **Part 2 – Additional functions:** utilities that are not in the libc (or exist in a
  different form) and are useful later, such as `ft_split` or `ft_itoa`.
- **Part 3 – Linked list:** a generic singly linked list (`t_list`) and the functions
  to create, traverse, transform and free it.

## Instructions

### Requirements

- A C compiler (`cc`)
- `make`
- `ar` (standard on Linux and macOS)

### Compilation

From the root of the repository:

| Command       | Effect                                                          |
|---------------|-----------------------------------------------------------------|
| `make`        | Compiles all three parts into `libft.a`                         |
| `make clean`  | Removes the object files (`.o`)                                 |
| `make fclean` | Removes the object files and `libft.a`                          |
| `make re`     | Runs `fclean` and then `all`                                    |

All files are compiled with `-Wall -Wextra -Werror`. Running `make` a second
time without changes does nothing — the library is not re-linked.

### Using the library in another project

```c
#include "libft.h"

int	main(void)
{
	char	*s;

	s = ft_itoa(-42);
	ft_putendl_fd(s, 1);
	free(s);
	return (0);
}
```

```sh
make
cc -Wall -Wextra -Werror main.c -I. -L. -lft -o demo
./demo
```

`-I.` tells the compiler where `libft.h` is, `-L.` where `libft.a` is, and `-lft` links
against `libft.a` (the linker adds the `lib` prefix and `.a` suffix automatically).

## Library description

### Part 1 – Libc functions

#### Character checks and conversions (`<ctype.h>`)

| Function     | Description                                                      |
|--------------|------------------------------------------------------------------|
| `ft_isalpha` | Returns non-zero if `c` is a letter (`A–Z`, `a–z`)               |
| `ft_isdigit` | Returns non-zero if `c` is a digit character (`'0'–'9'`)         |
| `ft_isalnum` | Returns non-zero if `c` is a letter or a digit                   |
| `ft_isascii` | Returns non-zero if `c` is in the ASCII table (0–127)            |
| `ft_isprint` | Returns non-zero if `c` is printable (32–126)                    |
| `ft_toupper` | Converts a lowercase letter to uppercase; other values unchanged |
| `ft_tolower` | Converts an uppercase letter to lowercase; other values unchanged|

#### Memory (`<string.h>`, `<stdlib.h>`)

| Function     | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `ft_memset`  | Fills `n` bytes of memory with a byte value                                 |
| `ft_bzero`   | Sets `n` bytes of memory to zero                                            |
| `ft_memcpy`  | Copies `n` bytes from `src` to `dst` (areas must not overlap)               |
| `ft_memmove` | Copies `n` bytes from `src` to `dst`, safe when the areas overlap           |
| `ft_memchr`  | Finds the first occurrence of a byte in the first `n` bytes                 |
| `ft_memcmp`  | Compares `n` bytes of two memory areas                                      |
| `ft_calloc`  | Allocates zero-initialised memory for an array; returns `NULL` on overflow  |

#### Strings (`<string.h>`, `<stdlib.h>`)

| Function     | Description                                                                   |
|--------------|-------------------------------------------------------------------------------|
| `ft_strlen`  | Returns the length of a string (without the `'\0'`)                           |
| `ft_strlcpy` | Size-bounded copy; always `'\0'`-terminates; returns the length of `src`      |
| `ft_strlcat` | Size-bounded concatenation; returns the length it tried to create             |
| `ft_strchr`  | Finds the first occurrence of a character (the `'\0'` counts)                 |
| `ft_strrchr` | Finds the last occurrence of a character                                      |
| `ft_strncmp` | Compares at most `n` characters of two strings                                |
| `ft_strnstr` | Finds a substring within the first `len` characters of a string               |
| `ft_strdup`  | Returns a newly allocated copy of a string                                    |
| `ft_atoi`    | Converts the beginning of a string to an `int` (spaces, one sign, digits)     |

### Part 2 – Additional functions

| Function        | Description                                                                  |
|-----------------|------------------------------------------------------------------------------|
| `ft_substr`     | Returns a new string of up to `len` characters starting at index `start`     |
| `ft_strjoin`    | Returns a new string made of `s1` followed by `s2`                           |
| `ft_strtrim`    | Returns a copy of `s1` without the characters of `set` at both ends          |
| `ft_split`      | Splits a string by a delimiter into a `NULL`-terminated array of strings     |
| `ft_itoa`       | Converts an `int` to a newly allocated string (handles `INT_MIN`)            |
| `ft_strmapi`    | Returns a new string by applying `f(index, char)` to each character          |
| `ft_striteri`   | Applies `f(index, &char)` to each character, modifying the string in place   |
| `ft_putchar_fd` | Writes a character to a file descriptor                                      |
| `ft_putstr_fd`  | Writes a string to a file descriptor                                         |
| `ft_putendl_fd` | Writes a string followed by a newline to a file descriptor                   |
| `ft_putnbr_fd`  | Writes an integer to a file descriptor (recursive, no allocation)            |

### Part 3 – Linked list

The list node is defined in `libft.h`:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

`content` is a `void *`, so the list can hold any type of data. The list itself only
manages the nodes; functions that need to free or transform the content receive a
function pointer (`del` or `f`) supplied by the caller, who knows the content's type.

| Function          | Description                                                                 |
|-------------------|-----------------------------------------------------------------------------|
| `ft_lstnew`       | Allocates a new node with the given content and `next = NULL`               |
| `ft_lstadd_front` | Adds a node at the beginning of the list                                    |
| `ft_lstadd_back`  | Adds a node at the end of the list                                          |
| `ft_lstsize`      | Counts the nodes in the list                                                |
| `ft_lstlast`      | Returns the last node of the list                                           |
| `ft_lstdelone`    | Frees one node's content with `del`, then the node                          |
| `ft_lstclear`     | Frees every node and its content, and sets the list pointer to `NULL`       |
| `ft_lstiter`      | Applies `f` to the content of every node                                    |
| `ft_lstmap`       | Builds a new list by applying `f` to each content; cleans up on failure     |

### Technical choices

- **One function per file**, as required by the 42 Norm, with `static` helpers kept
  private to the file that uses them (e.g. `count_words` in `ft_split.c`).
- **Byte-level access through `unsigned char *`** in all memory functions, so that bytes
  above 127 compare correctly and any data type can be handled.
- **Overflow protection in `ft_calloc`:** the check `size > SIZE_MAX / nmemb` is done
  before multiplying, because an overflowing `size_t` product would silently wrap
  around and allocate less memory than requested.
- **`ft_memmove` copies backwards when `dst` is after `src`**, so overlapping bytes are
  read before they are overwritten.
- **`long` in `ft_itoa` and `ft_putnbr_fd`**, because `-INT_MIN` does not fit in an
  `int`.
- **Functions that may change the head of a list take a `t_list **`** (`add_front`,
  `add_back`, `clear`), since C passes arguments by copy.
- **A single `all` rule builds the whole library**, including the linked-list
  functions, since in this version of the subject they are part of the mandatory part.

## Resources

### References

- Linux man pages, section 3 (`man 3 strlen`, `man 3 memmove`, …) —
  <https://man7.org/linux/man-pages/>
- cppreference, C standard library reference — <https://en.cppreference.com/w/c>
- B. W. Kernighan & D. M. Ritchie, *The C Programming Language*, 2nd ed.
- T. C. Miller & T. de Raadt, *strlcpy and strlcat — consistent, safe, string copy and
  concatenation* (USENIX 1999), the origin of `strlcpy`/`strlcat`
- GNU Make manual — <https://www.gnu.org/software/make/manual/>
- `man ar` — creating static libraries
- Valgrind documentation, for checking memory leaks — <https://valgrind.org/docs/manual/>

### Use of AI

AI (Claude) was used as a study and review aid. Specifically:

- **Explanations:** walking through how each function works (memory layout, `void *`,
  pointer-to-pointer in list functions, `size_t` overflow in `ft_calloc`), to prepare
  for the peer evaluation.
- **Testing:** writing test programs, used locally and not submitted, to compare the
  functions against the libc and check for memory leaks.
- **Subject review:** checking the repository against the subject (file names,
  prototypes, Makefile rules, files to submit).
- **README:** drafting this file.

The implementation of the library functions themselves was written by me.