require 'strings'

print =: 1!:2&2
read =: 1!:1[3

s =: (read-.CR)-.LF

fff =. monad define
    a =. ". y
    n =. # a

    res =. 0
    n1 =. n - 1

    for_x. i. n1 do.
        u =. x { a
        v =. (x+1) { a

        t =. 0

        if. u > v
            do. t =. u - v
        end.
        if. v > u
            do. t =. v - u
        end.

        if. t > res
            do. res =. t
        end.
    end.

    print res
)

fff s
