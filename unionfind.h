/*
 * A generic disjoint-set implementation, AKA union-find set.
 *
 * To make a structure unifiable, add a UF_handle_t named uf_handle to the
 * structure. The first parameter to every macro is the type of your unifiable
 * structure.
 *
 * The implemention is a "Disjoint-set forest" with the enhancements "union by
 * rank" and "path compression" as described on the Wikipedia page Disjoint-set
 * data structure [http://en.wikipedia.org/wiki/Disjoint-set_data_structure].
 *
 * License: MIT
 */

typedef struct UF_handle {
	void *parent;
	unsigned int rank;
} UF_handle_t;

/*
 * Initialize a singleton set for the element pointed to by ptr.
 *
 * (This is optional if the structure has been memset to zero.)
 */
#define UF_MAKESET(uf_type, ptr) do { \
	(ptr)->uf_handle.parent = NULL; \
	(ptr)->uf_handle.rank   = 0; \
} while(0)

/*
 * Finds the representative of srcptr and assigns it to dstptr
 */
#define UF_FIND(uf_type, dstptr, srcptr) do { \
	uf_type *_iter = (srcptr); \
	while (_iter->uf_handle.parent) \
		_iter = (uf_type *)_iter->uf_handle.parent; \
	(dstptr) = _iter; \
} while(0)

/*
 * Unifies leftptr and rightptr (pointers to unifiable structures).
 */
#define UF_UNION(uf_type, leftptr, rightptr) do { \
	uf_type *_leftroot; \
	uf_type *_rightroot; \
	UF_FIND(uf_type, _leftroot, leftptr); \
	UF_FIND(uf_type, _rightroot, rightptr); \
	if (_leftroot->uf_handle.rank < _rightroot->uf_handle.rank) { \
		_leftroot->uf_handle.parent = _rightroot; \
	} else { \
		if (_leftroot->uf_handle.rank == _rightroot->uf_handle.rank) {\
			_leftroot->uf_handle.rank++; \
		} \
		_rightroot->uf_handle.parent = _leftroot; \
	} \
} while(0)
