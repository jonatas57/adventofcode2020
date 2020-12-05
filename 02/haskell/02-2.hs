{- stack script 
 --resolver lts-14.18
 --package text
-}

import Data.Text (split, pack, unpack)

parse :: String -> (Int, Int, Char, String)
parse s = (read $ unpack a, read $ unpack b, head $ unpack c, unpack d)
  where
    [ab, c, d] = split (== ' ') $ pack s
    [a, b] = split (== '-') $ ab

isValid :: (Int, Int, Char, String) -> Bool
isValid (l, r, c, s) = unique pos 
  where
    cs = filter (\(x, _) -> x == l || x == r) $ zip [1..] s
    pos = filter (\(_, y) -> y == c) cs
    unique [x] = True
    unique  _  = False

main :: IO ()
main = do
  input <- getContents
  let ps = map parse $ lines input
  print $ sum [if isValid p then 1 else 0 | p <- ps]
