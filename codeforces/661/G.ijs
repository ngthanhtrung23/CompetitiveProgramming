require 'strings'

print =: 1!:2&2
read =: 1!:1[3

s =. read-.CR
t =. LF splitstring s

f =. monad define
    name =. 0 {y
    value =. 1 {y

    name =. '' joinstring name
    value =. '' joinstring value

    countss=: #@] %~ #@[ - [ #@rplc '';~]

    start =. 0 { name
    start =. toupper start
    name =. }. name

    name =. start, name

    cnt =. value countss '.'

    if. cnt > 0 do.
        name =. 'f', name
    else.
        name =. 'i', name
    end.

    print name
)

f t