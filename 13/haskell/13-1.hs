{-stack script
--resolver lts-14.20
-}

import Data.Char

parse :: String -> [Int]
parse s = parse' [] 0 s
  where
    parse' ans x []     = x : ans
    parse' ans x (c:cs) | c == ','  = parse' (x : ans) 0 cs
                        | c == 'x'  = parse' ans 0 cs
                        | otherwise = parse' ans (x * 10 + ord c - ord '0') cs

getTime :: Int -> Int -> (Int, Int)
getTime t x = (mod (x - mod t x) x, x)

main :: IO ()
main = do
  t <- read <$> getLine
  ids <- filter (/= 0) <$> parse <$> getLine
  print $ uncurry (*) $ minimum $ map (getTime t) ids
