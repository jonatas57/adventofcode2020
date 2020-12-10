{-stack script
--resolver lts-14.20
--package containers
-}

import Data.List
import qualified Data.Map as M
import Data.Maybe

count :: [Int] -> Int
count xs = fromJust $ M.lookup (last xs) dp
  where
    dp         = foldl f st pairs
    st         = M.fromList [(0, 1)]
    f m (x, y) = M.insert x (getVal x m + getVal y m) m
    getVal x m = fromMaybe 0 $ M.lookup x m
    pairs      = [(x, y) | x <- xs, y <- xs, x - y <= 3 && x > y]


main :: IO ()
main = do 
  input <- map read . lines <$> getContents
  let list = sort $ (3 + maximum input) : 0 : input
  print $ count list
