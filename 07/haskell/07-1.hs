{-stack script
--resolver lts-14.20
--package containers
-}

import Data.Char
import Data.Maybe
import qualified Data.Map as Map
import qualified Data.Set as Set

type Color = String

getChilds :: [String] -> [(Int, Color)]
getChilds ss = getChilds' [] ss
  where
    getChilds' ans (q:c1:c2:_:ss) = getChilds' ((read q, c1 ++ c2) : ans) ss
    getChilds' ans _              = ans

parse :: [String] -> (Color, [(Int, Color)])
parse (x:y:cs) = (x ++ y, getChilds $ tail $ tail cs)
parse _        = ([], [])

getParents :: [(Color, [(Int, Color)])] -> [(Color, Color)]
getParents ls = getParents' [] ls
  where
    getParents' ans []                       = ans
    getParents' ans ((_, []):ls)             = getParents' ans ls
    getParents' ans ((col, (_, col2):cs):ls) = getParents' ((col2, col) : ans) ((col, cs) : ls)

build :: Map.Map Color [Color] -> [(Color, Color)] -> Map.Map Color [Color]
build mapa []            = mapa
build mapa ((c1, c2):cs) = case Map.lookup c1 mapa of
                                           Just xs -> build (Map.insert c1 (c2:xs) mapa) cs
                                           Nothing -> build (Map.insert c1 [c2]    mapa) cs

getAncestors :: Map.Map Color [Color] -> Color -> Set.Set Color
getAncestors mapa col = Set.fromList $ (:) col $ concat $ map (Set.toList . getAncestors mapa) $ fromMaybe [] $ Map.lookup col mapa

countAncestors :: Color -> Map.Map Color [Color] -> Int
countAncestors col mapa = length $ Set.toList $ getAncestors mapa col

main :: IO ()
main = do 
  input <- fmap (map (parse . words)) $ fmap lines getContents
  let par = build Map.empty $ getParents input
  print $ countAncestors "shinygold" par - 1
