{-stack script 
--resolver lts-14.20
-}

type Ins = (Char, Int)

parse :: [String] -> [(Char, Int)]
parse []     = []
parse (x:xs) = (head x, read $ tail x) : parse xs

dirs = "ESWN" :: String

rotate :: (Int, Int, Int, Int) -> Int -> (Int, Int, Int, Int)
rotate ans 0 = ans
rotate ans@(x, y, wx, wy) rot | rot < 0   = rotate ans $ rot + 4 
                              | otherwise = rotate (x, y, -wy, wx) $ rot - 1

run :: (Int, Int, Int, Int) -> Ins -> (Int, Int, Int, Int)
run (x, y, wx, wy) ('N', del) = (x, y, wx, wy + del)
run (x, y, wx, wy) ('S', del) = (x, y, wx, wy - del)
run (x, y, wx, wy) ('E', del) = (x, y, wx + del, wy)
run (x, y, wx, wy) ('W', del) = (x, y, wx - del, wy)
run (x, y, wx, wy) ('L', del) = rotate (x, y, wx, wy) $ div del 90
run (x, y, wx, wy) ('R', del) = rotate (x, y, wx, wy) $ div del (-90)
run (x, y, wx, wy) ('F', del) = (x + del * wx, y + del * wy, wx, wy)

runAll :: (Int, Int, Int, Int) -> [Ins] -> (Int, Int, Int, Int)
runAll ans []     = ans
runAll ans (x:xs) = runAll (run ans x) xs

getAns :: (Int, Int, Int, Int) -> Int
getAns (x, y, _, _) = abs x + abs y

main :: IO ()
main = do
  input <- parse . lines <$> getContents
  print $ getAns $ runAll (0, 0, 10, 1) input
