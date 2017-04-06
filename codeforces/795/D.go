package main

import (
    "fmt"
    "bufio"
    "os"
)

func main() {
    var n int
    var l int
    var r int
    in := bufio.NewReader(os.Stdin)

    fmt.Fscan(in, &n)
    fmt.Fscan(in, &l)
    fmt.Fscan(in, &r)

    l -= 1
    r -= 1

    a := make([]int, 100111)
    b := make([]int, 100111)

    for i := 0; i < n; i++ {
        fmt.Fscan(in, &a[i])
    }
    for i := 0; i < n; i++ {
        fmt.Fscan(in, &b[i])
    }

    a2 := make([]int, 100111)
    b2 := make([]int, 100111)

    var ok bool = true
    for i := 0; i < n; i++ {
        if l <= i && i <= r {
            a2[a[i]] += 1
            b2[b[i]] += 1
        } else {
            if (a[i] != b[i]) {
                ok = false
            }
        }
    }

    for i := 0; i < 100111; i++ {
        if a2[i] != b2[i] {
            ok = false
        }
    }

    if ok {
        fmt.Printf("TRUTH\n");
    } else {
        fmt.Printf("LIE\n");
    }
}
