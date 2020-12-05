{- stack script 
 --resolver lts-14.18
-}

findSum :: [Int] -> Int -> (Int, Int)
findSum [x] _              = (-1, -1)
findSum l x | hl + ll == x = (hl, ll)
            | hl + ll <  x = findSum (tail l) x
            | otherwise    = findSum (init l) x
  where
    hl = head l
    ll = last l

findSum2 :: [Int] -> Int -> (Int, Int, Int)
findSum2 (x:xs) val | p == -1   = findSum2 xs val
                    | otherwise = (x, p, q)
  where
    (p, q) = findSum xs $ val - x

quicksort :: Ord a => [a] -> [a]
quicksort []      = []
quicksort [x]     = [x]
quicksort (x:xs)  = quicksort l ++ [x] ++ quicksort r
  where
    l = filter (x >) xs
    r = filter (x <=) xs

main :: IO ()
main = do
  input <- getContents
  let l = quicksort [read x :: Int | x <- lines input]
  let (a, b, c) = findSum2 l 2020
  print (a * b * c)
