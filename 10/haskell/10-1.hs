{-stack script
--resolver lts-14.20
-}

import Data.List

diff :: Int -> Int -> Int -> [Int] -> (Int, Int)
diff d1 d3 _ []     = (d1, d3)
diff d1 d3 y (x:xs) | x - y == 1 = diff (d1 + 1) d3 x xs
                    | x - y == 3 = diff d1 (d3 + 1) x xs
                    | otherwise  = diff d1 d3 x xs

main :: IO ()
main = do 
  input <- map read . lines <$> getContents
  let list = sort $ (3 + maximum input) : input
  print $ uncurry (*) $ diff 0 0 0 list
