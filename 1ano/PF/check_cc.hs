

abc = ['A','B'..'Z']

validaCheckDigit :: String -> Bool
validaCheckDigit "" = False
validaCheckDigit l = (length l == 12) && (mod (sum (valida2 (reverse (validaString l)) 1)) 10 == 0)

validaString :: String -> [Int]
validaString "" = []
validaString (h:t)  | elem h abc = [((ord(toUpper h))-55)] ++ validaString t 
                    | otherwise = [read [h]] ++ validaString t

valida2 :: [Int] -> Int -> [Int]
valida2 [] y = []
valida2 (h:t) y  | odd y = [h] ++ valida2 t (y+1)
                 | otherwise = (if ((h*2)>9) then [(h*2)-9] else [h*2]) ++ valida2 t (y+1)
