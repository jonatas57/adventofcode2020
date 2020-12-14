{-stack script
--resolver lts-14.20
--package containers
-}

import Data.Bits
import Data.Char
import qualified Data.Map as M

data Ins = Mask Int Int | Memo Int Int deriving (Show)

getMask :: String -> Ins
getMask s = Mask one zero
  where
    (one, zero)         = getMask' s 0 0
    getMask' []     o z = (o, z)
    getMask' (c:cs) o z = getMask' cs (2 * o + (fromEnum $ c == '1')) (2 * z + (fromEnum $ c /= '0'))

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

apply :: M.Map Int Int -> Int -> Int -> [Ins] -> M.Map Int Int
apply m _   _    []              = m
apply m one zero ((Mask x y):is) = apply m x y is
apply m one zero ((Memo p v):is) = apply (M.insert p (v .&. zero .|. one) m) one zero is

main :: IO ()
main = do
  ins <- map parse . lines <$> getContents
  print $ sum $ map snd $ M.toList $ apply M.empty 0 0 ins
