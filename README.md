[![Build Status](https://travis-ci.org/nikofil/helib-go.svg?branch=master)](https://travis-ci.org/nikofil/helib-go)
[![GoDoc](https://godoc.org/github.com/nikofil/helib-go?status.svg)](https://godoc.org/github.com/nikofil/helib-go)
# HELib-Go
HELib-Go is a Golang wrapper for [HELib](https://github.com/shaih/HElib)

### Sample Usage

```golang
ctx := helib.NewFHEContext()
defer ctx.Free()
arr1 := []int64{1,2,5,1,2,5,1,2,5,3}
arr2 := []int64{3,4,5,1,2,3,5,6,7,2}
ctx1 := ctx.CtxFromArr(arr1)
ctx2 := ctx.CtxFromArr(arr2)
helib.AddCtxs(ctx1, ctx2)
res := ctx.DecryptCtx(ctx1)
for i := range arr1 {
  fmt.Printf("%d + %d = %d\n", arr1[i], arr2[i], res[i])
}
```
