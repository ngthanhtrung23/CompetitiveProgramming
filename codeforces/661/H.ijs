require 'strings'

print =: 1!:2&2
read =: 1!:1[3
countss=: #@] %~ #@[ - [ #@rplc '';~]

s =. read-.CR

f =. monad define
    n =. y countss LF

    t =: ' ' joinstring LF splitstring y
    t =. ". t

    for_i. i. n do.
        cur =. n # 0

        for_j. i. n do.
            col =. i
            row =. (n - j) - 1

            id =. (row * n) + col

            elem =. id { t

            cur =. elem j } cur
        end.

        print cur
    end.
)

f s