import Data.Char
import Data.Text (splitOn)

--1
unliness :: [String] -> String
unliness [] = ""
unliness [x] = x ++ "\n"
unliness (x:xs) = x ++ "\n" ++ unliness xs 

--2
--(a)
type Mat = [[Int]]

stringToMat :: String -> Mat
stringToMat [] = [[]]
stringToMat str = map stringToVector (lines str)

stringToVector :: String -> [Int]
stringToVector s = map read (dropCommas s)


dropCommas ::  String -> [String]
dropCommas str =  case dropWhile (==',') str of
                      "" -> []
                      str' -> x : dropCommas str''
                            where (x, str'') = break (==',') str'

--(b)
transposta :: String -> Mat
transposta str = matToString (stringToMat str)

matToString :: [[a]] -> [[a]]
matToString [] = []
matToString ([] : xss) = matToString xss

matToString ((x : xs) : xss) = firstCol : matToString restOfRows
                               where firstCol = x : [h | (h:_) <- xss]
                                     restOfRows = xs : [t | (_:t) <- xss]

--3
data Lista a = Esq a (Lista a) | Dir (Lista a) a | Nula

--(a)
semUltimo :: Lista a -> Lista a
semUltimo Nula = Nula
semUltimo (Esq x Nula) = Nula
semUltimo (Dir Nula x) = Nula
semUltimo (Esq x xs) = Esq x (semUltimo xs)
semUltimo (Dir xs x) = xs

--(b)
instance Show a => Show (Lista a) where
    show (Nula) = []
    show (Esq a xs) = ((show a) ++ show xs)
    show (Dir xs a) = (show xs ++ (show a))
