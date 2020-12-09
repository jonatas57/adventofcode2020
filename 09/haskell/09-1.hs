{-stack script
--resolver lts-14.20
-}

search :: [Int] -> Int -> Bool
search [x]    sum             = False
search (x:xs) sum | null sums = search xs sum
                  | otherwise = True
  where
    sums = filter ((== sum) . snd) $ map (\y -> (y, x + y)) xs

findSum :: [Int] -> [Int] -> Int
findSum st ~(x:xs) = if search st x then findSum (init (x:st)) xs else x

main :: IO ()
main = do
  input <- fmap lines getContents
  let list = map read input :: [Int]
  print $ findSum (reverse $ take 25 list) (drop 25 list)
