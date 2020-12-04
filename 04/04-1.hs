{- stack script 
 --resolver lts-14.18
-}

words' :: String -> [String]
words' [] = [[]]
words' xs = words xs

getPasses :: [String] -> [[String]]
getPasses s = getPasses' [] [] s
  where
    getPasses' ans at []     = at : ans
    getPasses' ans at (x:xs) | x == ""   = getPasses' (at : ans) [] xs
                             | otherwise = getPasses' ans (x : at) xs

parse :: String -> (String, String)
parse str = (a, tail b)
  where
    (a, b) = splitAt 3 str

valid :: (String, String) -> Bool
valid ("byr", _) = True 
valid ("iyr", _) = True 
valid ("eyr", _) = True
valid ("hgt", _) = True
valid ("hcl", _) = True
valid ("ecl", _) = True
valid ("pid", _) = True
valid (_    , _) = False

check :: [(String, String)] -> Bool
check pass = check' 0 pass == 7
  where
    check' x []     = x
    check' x (p:ps) | valid p   = check' (x + 1) ps
                    | otherwise = check' x ps

main :: IO ()
main = do
  input <- fmap lines getContents
  let passes = map (map parse) $ getPasses $ concat $ map words' input
  print $ sum [if check p then 1 else 0 | p <- passes] 
