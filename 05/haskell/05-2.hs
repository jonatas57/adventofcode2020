{- stack script
--resolver lts-14.20
-}

import Data.List

conv2int :: String -> Int
conv2int s = conv2int' 0 s
  where
    conv2int' x []     = x
    conv2int' x (c:cs) = conv2int' (x * 2 + if c == 'B' || c == 'R' then 1 else 0) cs

main :: IO ()
main = do
  input <- fmap lines getContents
  let seats = sort $ map conv2int input
  print $ snd $ last $ filter (\(x, y) -> x + 1 == y) $ zip seats [head seats + 1..]
