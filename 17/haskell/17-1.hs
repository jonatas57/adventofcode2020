{-stack script
--resolver lts-14.20
--package containers
-}

import qualified Data.Map as M
import Data.Maybe

type State = M.Map (Int, Int, Int) Bool

getState :: [String] -> State
getState ss = M.fromList [(cs, c == '#') | (cs, c) <- coords]
  where
    rows   = zip [0..] ss
    coords = concat $ map (\(x, cs) -> [((x, y, 0), c) | (y, c) <- zip [0..] cs]) rows

getAdj :: (Int, Int, Int) -> [(Int, Int, Int)]
getAdj p@(x, y, z) = filter (/= p) [(x + i, y + j, z + k) | i <- [-1..1], j <- [-1..1], k <- [-1..1]]

nextState :: State -> State
nextState st = st'
  where
    st'             = M.fromList $ map (\(p, q) -> (p, isAlive q $ fromMaybe False $ M.lookup p st)) cnt
    isAlive 3 _     = True
    isAlive 2 True  = True
    isAlive _ _     = False
    cnt             = M.toList $ foldl fcnt M.empty $ concat $ map (getAdj . fst) $ filter snd $ M.toList st
    fcnt m p        = M.insertWith (+) p 1 m

update :: Int -> State -> State
update 0 state = state
update x state = update (x - 1) $ nextState state

f 3 _ = True
f 2 True = True
f _ _ = False

main :: IO ()
main = do
  state <- getState . lines <$> getContents
  let finalState = update 6 state
      countAlive = M.foldr ((+) . fromEnum) 0
  print $ countAlive finalState
