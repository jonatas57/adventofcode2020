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

inf = -1000000000 :: Int

run :: Int -> Int -> M.Map Int Op -> Int
run acc id ops = run' acc id False ops M.empty
  where
    run' acc id ch ops used = case M.lookup id used of 
                                            Just _  -> inf
                                            Nothing -> caseNothing
      where
        used' = M.insert id True used
        caseNothing = case M.lookup id ops of 
                              Nothing      -> acc
                              Just (Acc x) -> run' (acc + x) (id + 1) ch ops used'
                              Just (Jmp x) -> if y == inf && not ch then y' else y
                                where
                                  y  = run' acc (id + x) ch   ops used'
                                  y' = run' acc (id + 1) True ops used'
                              Just (Nop x) -> if z == inf && not ch then z' else z
                                where
                                  z  = run' acc (id + 1) ch   ops used'
                                  z' = run' acc (id + x) True ops used'

main :: IO ()
main = do
  input <- fmap (map parse) $ fmap lines getContents
  print $ run 0 0 $ M.fromList $ zip [0..] input
