{- stack script 
 --resolver lts-14.18
-}

import Data.Int 
import Data.Char 
import Text.Read

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

checkNum :: String -> Int -> Int -> Bool
checkNum s l r = case readMaybe s of Nothing -> False
                                     Just x  -> l <= x && x <= r

checkHgt :: String -> Bool
checkHgt str = checkNum num l r
  where
    (num, t)       = split [] str
    l              = if t == "in" then 59 else 150
    r              = if t == "in" then 76 else 193
    split n (c:cs) | isDigit c = split (c:n) cs
                   | otherwise = (reverse n, c:cs)
    split _ _                  = ("", "")

checkHex :: String -> Bool
checkHex [] = True
checkHex cs = and $ map (\c -> (isDigit c) || ((isLower c) && (c <= 'f'))) cs

checkHcl :: String -> Bool
checkHcl ('#':cs) = checkHex cs
checkHcl _        = False

checkEcl :: String -> Bool
checkEcl "amb" = True
checkEcl "blu" = True
checkEcl "brn" = True
checkEcl "gry" = True
checkEcl "grn" = True
checkEcl "hzl" = True
checkEcl "oth" = True
checkEcl _     = False

valid :: (String, String) -> Bool
valid ("byr", val) = checkNum val 1920 2002
valid ("iyr", val) = checkNum val 2010 2020
valid ("eyr", val) = checkNum val 2020 2030
valid ("hgt", val) = checkHgt val
valid ("hcl", val) = checkHcl val
valid ("ecl", val) = checkEcl val
valid ("pid", val) = checkNum val 0 999999999 && length val == 9
valid (_    , val) = False

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
