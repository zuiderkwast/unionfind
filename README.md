unionfind.h
===========

A generic disjoint-set AKA union-find.

Implementation
--------------

The implemention is a "Disjoint-set forest" with the enhancements "union by rank" and "path compression" as described on the Wikipedia page *Disjoint-set data structure* http://en.wikipedia.org/wiki/Disjoint-set_data_structure.

Usage
-----

Copy `unionfind.h` to your project. Add an `UF_handle_t` with the name `uf_handle` to any struct to make it unifiable. Use the macros `UF_MAKESET`, `UF_UNION` and `UF_FIND`.

Example
-------

```C
include <assert.h>
include "unionfind.h"

struct foo {
	UF_handle_t uf_handle;
	/* ... */
};

int main() {
	struct foo a;
	struct foo b;
	struct foo *representative_a;
	struct foo *representative_b;

	/* Create a singleton set for each of a and b */
	UF_MAKESET(struct foo, &a);
	UF_MAKESET(struct foo, &b);

	/* Unify a and b, i.e. join their sets together */
	UF_UNION(struct foo, &a, &b);

	/* If a and b are in the same set, they have the same representative */
	UF_FIND(struct foo, representative_a, &a);
	UF_FIND(struct foo, representative_b, &b);
	assert(representative_a == representative_b);

	return 0;
}
```

See `test.c` for another example.
