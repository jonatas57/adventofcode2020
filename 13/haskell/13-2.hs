{-stack script
--resolver lts-14.20
-}

import Data.Char

parse :: String -> [Integer]
parse s = map fromIntegral $ parse' [] 0 s
  where
    parse' ans x []     = x : ans
    parse' ans x (c:cs) | c == ','  = parse' (x : ans) 0 cs
                        | c == 'x'  = parse' ans 0 cs
                        | otherwise = parse' ans (x * 10 + ord c - ord '0') cs

xp :: Integer -> Integer -> Integer -> Integer
xp _ 0 _ = 1
xp b e m | mod e 2 == 0 = c
         | otherwise    = mod (c * b) m
  where
    c' = xp b (div e 2) m
    c  = mod (c' * c') m

inv :: Integer -> Integer -> Integer
inv x m = xp x (m - 2) m

chinese :: [(Integer, Integer)] -> Integer
chinese ls = mod (sum $ zipWith (*) aux invs) mmc
  where
    mmc  = foldl lcm 1 $ map snd ls
    aux  = map (\(x, y) -> mod (x * div mmc y) mmc) ls
    invs = map (\(_, y) -> inv (div mmc y) y) ls

main :: IO ()
main = do
  _ <- getLine
  ids <- map (\(x, y) -> (mod (y + mod x y) y, y)) <$> filter ((/= 0) . snd) <$> zip [0,-1..] <$> reverse <$> parse <$> getLine
  let mmc = foldl lcm 1 $ map snd $ tail ids
      d   = snd $ head ids
      ans = chinese $ tail ids
  print $ head $ filter (\x -> mod x d == 0) [ans + i * mmc | i <- [0..d]]
