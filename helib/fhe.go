package helib
// #cgo CXXFLAGS: -std=c++11 -fPIE
// #cgo LDFLAGS: -L/usr/lib -L/usr/local/lib -lfhe -lntl -lgmp -lm -fPIE -fpie
// #include "FHE.h"
import "C"
import "unsafe"

type FHEContext struct {
	realContext unsafe.Pointer
}

func NewFHEContext() *FHEContext {
	return &FHEContext{ unsafe.Pointer(C.newFHEContext(C.long(19), C.long(1), C.long(7781), C.long(6), C.long(2), C.long(64))) }
}

func (context *FHEContext) CtxFromArr(arr []int64) unsafe.Pointer {
	return C.ctxtFromArray((*C.struct_GoFHEContext)(context.realContext), (*C.long)(unsafe.Pointer(&arr[0])), C.int(len(arr)))
}

func AddCtxs(c1, c2 unsafe.Pointer) unsafe.Pointer {
	return C.addCtx(c1, c2)
}

func MulCtxs(c1, c2 unsafe.Pointer) unsafe.Pointer {
	return C.mulCtx(c1, c2)
}

func (context *FHEContext) DecryptCtx(c1 unsafe.Pointer) (res []int64) {
	res = make([]int64, context.GetSlots())
	C.decryptCtx((*C.struct_GoFHEContext)(context.realContext), c1, (*C.long)(unsafe.Pointer(&res[0])))
	return
}

func (context *FHEContext) GetSlots() int64 {
	return int64(C.getSlots((*C.struct_GoFHEContext)(context.realContext)))
}

func (context *FHEContext) Free() {
	C.freeFHEContext((*C.struct_GoFHEContext)(context.realContext))
}
