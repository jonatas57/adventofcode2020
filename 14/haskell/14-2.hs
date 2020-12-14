{-stack script
--resolver lts-14.20
--package containers
-}

import Data.Bits
import Data.Char
import qualified Data.Map as M

data Ins = Mask Int Int Int | Memo Int Int deriving (Show)

getMask :: String -> Ins
getMask s = Mask one zero var
  where
    (one, zero, var)      = getMask' s 0 0 0
    getMask' []     o z v = (o, z, v)
    getMask' (c:cs) o z v = getMask' cs (2 * o + (fromEnum $ c == '1')) (2 * z + (fromEnum $ c == '0')) (2 * v + (fromEnum $ c == 'X'))

getMemo :: String -> Ins
getMemo s = Memo pos val
  where
    (pos, val) = getMemo' False 0 0 s
    getMemo' _     x y []       = (x, y)
    getMemo' _     x y (']':cs) = getMemo' True x y cs
    getMemo' _     x y (' ':cs) = getMemo' True x y cs
    getMemo' _     x y ('=':cs) = getMemo' True x y cs
    getMemo' False x y (c:cs)   = getMemo' False (10 * x + (ord c - ord '0')) y cs
    getMemo' True  x y (c:cs)   = getMemo' True x (10 * y + (ord c - ord '0')) cs

parse :: String -> Ins
parse ('m':'e':'m':'[':xs)             = getMemo xs
parse ('m':'a':'s':'k':' ':'=':' ':xs) = getMask xs

getPos :: Int -> Int -> Int -> Int -> [Int]
getPos p ori one var = [p .&. ori .|. one .|. mask | mask <- getSubmasks var var []]
  where
    getSubmasks v 0 ms = 0 : ms
    getSubmasks v m ms = getSubmasks v ((m - 1) .&. v) $ m : ms

insertAll :: [Int] -> Int -> M.Map Int Int -> M.Map Int Int
insertAll [] _ m     = m
insertAll (x:xs) v m = insertAll xs v $ M.insert x v m

apply :: M.Map Int Int -> Int -> Int -> Int -> [Ins] -> M.Map Int Int
apply m _   _    _   []                = m
apply m one zero var ((Mask x y z):is) = apply m x y z is
apply m one zero var ((Memo p v):is)   = apply (insertAll (getPos p zero one var) v m) one zero var is

main :: IO ()
main = do
  ins <- map parse . lines <$> getContents
  print $ sum $ map snd $ M.toList $ apply M.empty 0 0 0 ins
