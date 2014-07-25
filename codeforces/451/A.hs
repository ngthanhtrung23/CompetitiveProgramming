getResult m n = if (min m n) `mod` 2 == 1
                then "Akshat"
                else "Malvika"

main = do
    [n, m] <- fmap (map read . words) getLine :: IO [Int]
    putStrLn $ (getResult m n)
