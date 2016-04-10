require 'strings'

print =: 1!:2&2
read =: 1!:1[3

s =: (read-.CR)-.LF

fff =. monad define
    a =. ". y
    n =. # a
    res =. 0

    for_x. i. n do.
        good =. 1

        big =. x { a

        for_y. i. n do.
            small =. y { a

            rem =. big |~ small

            if. rem > 0
                do. good =. 0
            end.
        end.

        if. good > 0
            do. res =. 1
        end.
    end.

    print res
)

fff s
