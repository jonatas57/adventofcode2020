{-stack script 
--resolver lts-14.20
-}

type Ins = (Char, Int)

parse :: [String] -> [(Char, Int)]
parse []     = []
parse (x:xs) = (head x, read $ tail x) : parse xs

dirs = "ESWN" :: String

run :: (Int, Int, Int) -> Ins -> (Int, Int, Int)
run (x, y, d) ('N', del) = (x, y + del, d)
run (x, y, d) ('S', del) = (x, y - del, d)
run (x, y, d) ('E', del) = (x + del, y, d)
run (x, y, d) ('W', del) = (x - del, y, d)
run (x, y, d) ('L', del) = (x, y, mod (4 + d - div del 90) 4)
run (x, y, d) ('R', del) = (x, y, mod (d + div del 90) 4)
run (x, y, d) ('F', del) = run (x, y, d) $ (dirs !! d, del)

runAll :: (Int, Int, Int) -> [Ins] -> (Int, Int, Int)
runAll ans []     = ans
runAll ans (x:xs) = runAll (run ans x) xs

getAns :: (Int, Int, Int) -> Int
getAns (x, y, _) = abs x + abs y

main :: IO ()
main = do
  input <- parse . lines <$> getContents
  print $ getAns $ runAll (0, 0, 0) input
