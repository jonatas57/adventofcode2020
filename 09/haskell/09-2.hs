{-stack script
--resolver lts-14.20
-}

type Queue a = ([a], [a])

emptyQueue = ([], []) :: Queue a

push :: Queue a -> a -> Queue a
push (ls, rs) x = (ls, x:rs)

pop :: Queue a -> Queue a
pop ([], rs)   = pop (reverse rs, [])
pop (x:xs, rs) = (xs, rs)

front :: Queue a -> a
front ([], rs)   = front (reverse rs, [])
front (x:ls, rs) = x

toList :: Queue a -> [a]
toList (ls, rs) = ls ++ reverse rs

search :: [Int] -> Int -> Bool
search [x]    sum             = False
search (x:xs) sum | null sums = search xs sum
                  | otherwise = True
  where
    sums = filter ((== sum) . snd) $ map (\y -> (y, x + y)) xs

findSum :: [Int] -> [Int] -> Int
findSum st ~(x:xs) = if search st x then findSum (init (x:st)) xs else x

getLimits :: [Int] -> (Int, Int)
getLimits ls = (minimum ls, maximum ls)

findSubArray :: Int -> [Int] -> [Int]
findSubArray s ls = findSubArray' s ls 0 emptyQueue
  where
    findSubArray' s ls@(x:xs) acc q | acc < s   = findSubArray' s xs (acc + x) $ push q x 
                                    | acc > s   = findSubArray' s ls (acc - front q) $ pop q
                                    | otherwise = toList q

main :: IO ()
main = do
  input <- fmap lines getContents
  let list = map read input :: [Int]
  let s = findSum (reverse $ take 25 list) (drop 25 list)
  print $ uncurry (+) $ getLimits $ findSubArray s list
