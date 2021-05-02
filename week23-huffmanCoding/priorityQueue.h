void pQue_enque(void* item, size_t sizeOfElement, bool(*compareFunc)(const void* parent, const void* child));
void* pQue_deque(size_t sizeOfElement, bool(*compareFunc)(const void* p1, const void* p2));
void doneWith_pQue(void);

#ifdef pQue_test
bool compareFunc_min(const void* p1, const void* p2);
bool compareFunc_max(const void* p1, const void* p2);
bool (*compareFuncs[])(const void* p1, const void* p2);
void testStuff(void)
#endif // pQue_test