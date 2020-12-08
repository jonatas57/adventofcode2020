{-stack script
--resolver lts-14.20
--package containers
-}

import qualified Data.Map as M
import Data.Maybe

data Op       = Acc Int | Jmp Int | Nop Int deriving (Show)

parse :: String -> Op
parse str = case head x of
                    'a' -> Acc y
                    'j' -> Jmp y
                    'n' -> Nop y
  where
    str' = words str
    x    = head str'
    y    = read $ if head y' == '-' then y' else tail y'
    y'   = last str'

run :: Int -> Int -> M.Map Int Op -> Int
run acc id z = run' acc z id M.empty
  where
    run' acc z id used = case M.lookup id used of
                                          Just True  -> acc
                                          Nothing -> case fromJust $ M.lookup id z of 
                                                      Acc x -> run' (acc + x) z (id + 1) used'
                                                      Jmp x -> run' acc z (id + x) used'
                                                      Nop x -> run' acc z (id + 1) used'
                                                      where 
                                                        used' = M.insert id True used


main :: IO ()
main = do
  input <- fmap (map parse) $ fmap lines getContents
  print $ run 0 0 $ M.fromList $ zip [0..] input
