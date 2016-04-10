print =: 1!:2&2
read =: 1!:1[3

in =. (read-.LF)-.CR

season =. monad define
if. 0 { y = 'D'
    do. 'winter'
end.

if. 0 { y = 'J'
    do. if. 1 { y = 'a'
        do. 'winter'
    end.
end.

if. 0 { y = 'F'
    do. 'winter'
end.

if. 0 { y = 'M'
    do. 'spring'
end.

if. 0 { y = 'A'
    do. if. 1 { y = 'p'
        do. 'spring'
    end.
end.

if. 0 { y = 'J'
    do. if. 1 { y = 'u'
        do. 'summer'
    end.
end.

if. 0 { y = 'A'
    do. if. 1 { y = 'u'
        do. 'summer'
    end.
end.

if. 0 { y = 'S'
    do. 'autumn'
end.
if. 0 { y = 'O'
    do. 'autumn'
end.
if. 0 { y = 'N'
    do. 'autumn'
end.
)

print season in
