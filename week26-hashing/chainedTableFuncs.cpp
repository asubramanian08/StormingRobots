#include <stdlib.h>
#include <assert.h>
#include<string.h>
#define TESTING

class chainedTable {
public:
	chainedTable(unsigned int buckets, unsigned int (*hash)( void* id),
		bool (*sameId)(void* id1, void* id2), void freeItem(void* id, void* info)) {
		h_tbl_buckets = buckets;
		h_tbl_hash = hash;
		h_tbl_sameId = sameId;
		h_tbl_freeItem = freeItem;
		h_tbl = (chain * *)calloc(sizeof(chain*), buckets);
		assert(h_tbl);
#ifdef TESTING
		chainLength = (unsigned int*)calloc(buckets, sizeof(unsigned int));
		assert(chainLength);
#endif // TESTING
	}
	~chainedTable() {
		free_h_tbl();
#ifdef TESTING
		free(chainLength);
#endif // TESTING
	}
	bool reset(unsigned int buckets) {
		h_tbl_buckets = buckets;
		free_h_tbl();
#ifdef TESTING
		memset(chainLength, 0, sizeof(unsigned int) * h_tbl_buckets);
#endif // TESTING
		return (h_tbl = (chain * *)calloc(sizeof(chain*), buckets)) != NULL;
	}
	bool add(void* id, void* info) {
		chain** curr = &(h_tbl[h_tbl_hash(id)]);
#ifdef TESTING
		chainLength[h_tbl_hash(id)]++;
#endif // TESTING
		while (*curr)
			curr = &((*curr)->nextChain);
		if ((*curr = (chain*)malloc(sizeof(chain))) == NULL)
			return false;
		(*curr)->id = id;
		(*curr)->info = info;
		(*curr)->nextChain = NULL;
		return true;
	};
	bool dsty(void* id) {
		chain** curr = findItem(id);
		if (*curr) {
#ifdef TESTING
			chainLength[h_tbl_hash(id)]++;
#endif // TESTING
			h_tbl_freeItem((*curr)->id, (*curr)->info);
			chain* toFree = *curr;
			*curr = (*curr)->nextChain;
			free(toFree);
			return true;
		}
		return false;
	}
	void* updt(void* id, void* info) {
		chain** curr = findItem(id);
		if (*curr == NULL)
			return NULL;
		if (info) {
			free((*curr)->info);
			(*curr)->info = info;
		}
		return (*curr)->info;
	};
#ifdef TESTING
	unsigned int maxChain(void) {
		unsigned int max = 0;
		for (unsigned int i = 0; i < h_tbl_buckets; i++)
			if (chainLength[i] > max)
				max = chainLength[i];
		return max;
	}
	const unsigned int* listofChains(void) {
		return chainLength;
	}
#endif // TESTING
private:
	struct chain {
		void* id;
		void* info;
		chain* nextChain;
	}**h_tbl;
#ifdef TESTING
	unsigned int* chainLength;
#endif // TESTING
	unsigned int h_tbl_buckets;
	unsigned int (*h_tbl_hash)(void* id);
	bool (*h_tbl_sameId)(void* id1, void* id2);
	void (*h_tbl_freeItem)(void* id, void* info);
	void free_h_tbl() {
		chain* curr, * toFree;
		for (unsigned int i = 0; i < h_tbl_buckets; i++) {
			curr = h_tbl[i];
			while (curr) {
				h_tbl_freeItem(curr->id, curr->info);
				toFree = curr;
				curr = curr->nextChain;
				free(toFree);
			}
		}
	}
	chain** findItem(void* id) {
		chain** curr = &(h_tbl[h_tbl_hash(id)]);
		while (*curr && !h_tbl_sameId((*curr)->id, id))
			curr = &((*curr)->nextChain);
		return curr;
	}
};