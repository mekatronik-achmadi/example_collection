package main

// #include "pwr.c"
import "C"
import (
    "fmt"
)

func main() {
    vx := 4
    vy := 3

    result := C.calc_pwr(C.int(vx),C.int(vy))

    fmt.Printf("Power C in Go: %d\n",result)
}
