{- stack script 
 --resolver lts-14.18
-}

count :: [a] -> (a -> Bool) -> Int
count xs f = count' xs f 0
  where
    count' []     _ acc = acc
    count' (y:ys) f acc | f y       = count' ys f $ acc + 1
                        | otherwise = count' ys f acc

countTree :: [String] -> Int -> Int -> Int
countTree tobo right down = count positions (== '#')
  where
    width      = length $ head tobo
    positions  = [(!!) y $ x `mod` width | (x, y) <- zip [0, right..] indexLines]
    indexLines = map snd $ filter (\(x, _) -> mod x down == 0) $ zip [0..] tobo

main :: IO ()
main = do
  input <- fmap lines getContents
  let dels = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
  print $ product $ map (uncurry (countTree input)) dels
