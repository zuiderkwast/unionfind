#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "unionfind.h"

struct num {
	UF_handle_t uf_handle;
	int number;
};

/* A helper to print the sets of n struct nums containing numbers 0...(n-1) */
void print_sets(int n, struct num nums[]) {
	int i, j, numsets = 0, num_in_set_i;
	struct num * found_num;
	for (i = 0; i < n; i++) {
		/* Print the set with i as the representative, if any */
		num_in_set_i = 0;
		for (j = 0; j < n; j++) {
			UF_FIND(struct num, found_num, &nums[j]);
			if (found_num->number == i) {
				/* found */
				if (!num_in_set_i && numsets > 0) {
					printf(", ");
				}
				printf(num_in_set_i++ ? ", " : "{");
				printf("%d", j);
			}
		}
		if (num_in_set_i) {
			printf("}");
			numsets++;
		}
	}
}

/* Returns 1 if a and b are in the same set, 0 otherwise */
int in_same_set(struct num *a, struct num *b) {
	struct num *representant_a, *representant_b;
	UF_FIND(struct num, representant_a, a);
	UF_FIND(struct num, representant_b, b);
	return representant_a == representant_b;
}

/*
 * This is a zero-based version for the example in the Wikipedia article
 * http://en.wikipedia.org/wiki/Disjoint-set_data_structure
 *
 * 1. Create 8 singleton sets {0}, {1}, ..., {7}.
 * 2. After some operations of Union, some sets are grouped together.
 */
int main(int argc, char *argv[]) {
	/* Make singleton sets {0}, {1}, ..., {7} */
	struct num nums[8];
	int i;
	int verbose = argc > 1 && strcmp(argv[1], "-v") == 0;

	for (i = 0; i < 8; i++) {
		nums[i].number = i;
		UF_MAKESET(struct num, &nums[i]);
	}

	/* Print the representative for each number */
	if (verbose) {
		printf("Before: ");
		print_sets(8, nums);
		printf("\n");
	}

	/* Unify into {0, 1, 4, 5, 7}, {2, 3}, {6} */
	UF_UNION(struct num, &nums[0], &nums[1]);
	UF_UNION(struct num, &nums[1], &nums[4]);
	UF_UNION(struct num, &nums[1], &nums[5]);
	UF_UNION(struct num, &nums[7], &nums[5]);
	UF_UNION(struct num, &nums[2], &nums[3]);

	/* Print the representative for each number */
	if (verbose) {
		printf("After:  ");
		print_sets(8, nums);
		printf("\n");
	}

	/* Assert that we have what we expected */
	assert(in_same_set(&nums[0], &nums[0]));
	assert(in_same_set(&nums[0], &nums[1]));
	assert(in_same_set(&nums[0], &nums[4]));
	assert(in_same_set(&nums[0], &nums[5]));
	assert(in_same_set(&nums[0], &nums[7]));
	assert(in_same_set(&nums[0], &nums[7]));
	assert(in_same_set(&nums[2], &nums[2]));
	assert(in_same_set(&nums[2], &nums[3]));
	assert(in_same_set(&nums[6], &nums[6]));
	assert(!in_same_set(&nums[0], &nums[2]));
	assert(!in_same_set(&nums[0], &nums[6]));
	assert(!in_same_set(&nums[2], &nums[6]));

	return 0;
}
