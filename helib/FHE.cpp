#include "FHE.h"
#include "src/FHE.h"
#include "src/EncryptedArray.h"

GoFHEContext *newFHEContext(long p, long r, long m, long L, long c, long w) {
  vector<long> gens, ords;
  GoFHEContext *fheContext = new GoFHEContext();
  FHEcontext *context = new FHEcontext(m, p, r, gens, ords);
  fheContext->context = context;
  buildModChain(*context, L, c);

  FHESecKey *secretKey = new FHESecKey(*context);
  fheContext->secretKey = secretKey;
  // construct a secret key structure
  FHEPubKey *publicKey = secretKey;
  fheContext->publicKey = publicKey;
  // an "upcast": FHESecKey is a subclass of FHEPubKey

  ZZX G = context->alMod.getFactorsOverZZ()[0];
  EncryptedArray *ea = new EncryptedArray(*context, G);
  fheContext->encArr = ea;
  fheContext->nslots = ea->size();
  fflush(stdout);
  // constuct an Encrypted array object ea that is
  // associated with the given context and the polynomial G

  secretKey->GenSecKey(w);
  // actually generate a secret key with Hamming weight w

  addSome1DMatrices(*secretKey);

  return fheContext;
}

void freeFHEContext(GoFHEContext *ctx) {
    delete (FHEcontext*)ctx->context;
    delete (FHESecKey*)ctx->secretKey;
    delete (EncryptedArray*)ctx->encArr;
    delete ctx;
}

void *ctxtFromArray(GoFHEContext *ctx, long *arr, int n) {
   vector<long> v1;
   for(int i = 0 ; i < n; i++) {
       v1.push_back(arr[i]);
   }
   Ctxt *ct1 = new Ctxt(*(FHEPubKey*)ctx->publicKey);
   EncryptedArray *ea = (EncryptedArray*)ctx->encArr;
   ea->encrypt(*ct1, *(FHEPubKey*)ctx->publicKey, v1);
   return ct1;
}

void* addCtx(void *ct1, void *ct2) {
   Ctxt *ctSum = (Ctxt*)ct1;
   (*ctSum) += *(Ctxt*)ct2;
   return ctSum;
}

void* mulCtx(void *ct1, void *ct2) {
   Ctxt *ctProd = (Ctxt*)ct1;
   (*ctProd) *= *(Ctxt*)ct2;
   return ctProd;
}

void decryptCtx(GoFHEContext *ctx, void *ct1, long *result) {
   vector<long> res;
   EncryptedArray *ea = (EncryptedArray*)ctx->encArr;
   ea->decrypt(*(Ctxt*)ct1, *(FHESecKey*)ctx->secretKey, res);

   for(int i = 0; i < res.size(); i ++) {
       result[i] = res[i];
   }
}

long getSlots(GoFHEContext *ctx) {
   return ctx->nslots;
}
