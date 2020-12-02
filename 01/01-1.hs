{- stack script 
 --resolver lts-14.18
-}

findSum :: [Int] -> Int -> (Int, Int)
findSum l x | hl + ll == x = (hl, ll)
            | hl + ll <  x = findSum (tail l) x
            | otherwise    = findSum (init l) x
  where
    hl = head l
    ll = last l

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
  let (a, b) = findSum l 2020
  print (a * b)
