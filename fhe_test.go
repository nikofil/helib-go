package helib

import (
	"fmt"
	"testing"
)

func TestContext(t *testing.T) {
	ctx := NewFHEContext()
	defer ctx.Free()
}

func TestAdd(t *testing.T) {
	ctx := NewFHEContext()
	defer ctx.Free()
	arr1 := []int64{1, 2, 5, 1, 2, 5, 1, 2, 5, 3}
	arr2 := []int64{3, 4, 5, 1, 2, 3, 5, 6, 7, 2}
	ctx1 := ctx.CtxFromArr(arr1)
	ctx2 := ctx.CtxFromArr(arr2)
	AddCtxs(ctx1, ctx2)
	res := ctx.DecryptCtx(ctx1)
	for i := range arr1 {
		if arr1[i]+arr2[i] != res[i] {
			t.Fatalf("Got %d, expected %d\n", res[i], arr1[i]+arr2[i])
		}
	}
}

func TestMult(t *testing.T) {
	ctx := NewFHEContext()
	defer ctx.Free()
	arr1 := []int64{1, 2, 5, 1, 2, 5, 1, 2, 5, 3}
	arr2 := []int64{3, 4, 5, 1, 2, 3, 5, 6, 7, 2}
	ctx1 := ctx.CtxFromArr(arr1)
	ctx2 := ctx.CtxFromArr(arr2)
	MulCtxs(ctx1, ctx2)
	res := ctx.DecryptCtx(ctx1)
	for i := range arr1 {
		fmt.Printf("%d * %d = %d\n", arr1[i], arr2[i], res[i])
		if arr1[i]*arr2[i] != res[i] {
			t.Fatalf("Got %d, expected %d\n", res[i], arr1[i]*arr2[i])
		}
	}
}
