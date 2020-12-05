{- stack script
--resolver lts-14.20
-}

conv2int :: String -> Int
conv2int s = conv2int' 0 s
  where
    conv2int' x []     = x
    conv2int' x (c:cs) = conv2int' (x * 2 + if c == 'B' || c == 'R' then 1 else 0) cs

main :: IO ()
main = do
  input <- fmap lines getContents
  let seats = map conv2int input
  print $ maximum seats
