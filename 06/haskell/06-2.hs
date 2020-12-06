{-stack script
--resolver lts-14.20
-}

import Data.Bits
import Data.Char

toInt :: String -> Int
toInt str = foldr (.|.) 0 $ map toBit str
  where
    toBit c = shiftL 1 $ ord c - ord 'a'

words' :: String -> [String]
words' [] = [[]]
words' xs = words xs

parse :: [String] -> [[String]]
parse s = parse' [] [] s
  where
    parse' ans at []     = at : ans
    parse' ans at (x:xs) | x == ""   = parse' (at : ans) [] xs
                         | otherwise = parse' ans (x : at) xs

popcount :: Int -> Int
popcount = popcount' 0
  where
    popcount' x 0 = x
    popcount' x y = popcount' (x + (.&.) y 1) $ shiftR y 1

main :: IO ()
main = do
  input <- fmap lines getContents
  let ans = sum $ map popcount $ map (foldr (.&.) (shiftL 1 26 - 1)) $ map (map toInt) $ parse input
  print ans
