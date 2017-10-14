typedef struct GoFHEContext {
    void *context;
    void *secretKey;
    void *publicKey;
    void *encArr;
    long nslots;
} GoFHEContext;

#ifdef __cplusplus
extern "C" {
#endif
GoFHEContext *newFHEContext(long, long, long, long, long, long);
void *ctxtFromArray(GoFHEContext*, long*, int n);
void freeFHEContext(GoFHEContext*);
void* addCtx(void*, void*);
void* mulCtx(void*, void*);
void decryptCtx(GoFHEContext*, void*, long*);
long getSlots(GoFHEContext*);
#ifdef __cplusplus
}
#endif
