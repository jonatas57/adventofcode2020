{-stack script
--resolver lts-14.20
--package containers
-}

import Data.Char
import Data.Maybe
import qualified Data.Map as Map

type Color = String

getChilds :: [String] -> [(Int, Color)]
getChilds ss = getChilds' [] ss
  where
    getChilds' ans (q:c1:c2:_:ss) = getChilds' ((read q, c1 ++ c2) : ans) ss
    getChilds' ans _              = ans

parse :: [String] -> (Color, [(Int, Color)])
parse (x:y:cs) = (x ++ y, getChilds $ tail $ tail cs)
parse _        = ([], [])

countChildren :: Map.Map Color [(Int, Color)] -> Color -> Int
countChildren mapa color = countChildren' mapa [(1, color)] 0
  where
    countChildren' :: Map.Map Color [(Int, Color)] -> [(Int, Color)] -> Int -> Int
    countChildren' _    []          ans = ans
    countChildren' mapa ((q, c):cs) ans = countChildren' mapa cs (ans + q * countChildren' mapa (fromJust $ Map.lookup c mapa) 1)

main :: IO ()
main = do 
  input <- fmap (map (parse . words)) $ fmap lines getContents
  let mapa = Map.fromList input
  print $ countChildren mapa "shinygold" - 1
