
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
{-# HLINT ignore "Use foldr" #-}
{-# HLINT ignore "Use :" #-}
{-# HLINT ignore "Use infix" #-}
import Data.List
import System.IO
import Data.Char
import Data.Either
 

--Ex1
enumFromTo1 :: Int -> Int -> [Int]
enumFromTo1 x y | y>=x = x : enumFromTo1 (x+1) y
                | otherwise = []

--Ex2
enumFromThenTo1 :: Int -> Int -> Int ->[Int]
enumFromThenTo1 x y z | z >= x = x : enumFromThenTo1 (x+y-1) y z
                | otherwise = []

--Ex3 
maismais :: [a] -> [a] -> [a]
maismais [] [] = []
maismais (y:ys) [] = y:ys
maismais [] (y:ys) = y:ys
maismais (x:y) b = x : maismais y b

--Ex4 (tratar do just)
posicao :: [a] -> Int -> a
posicao [] _     = error "Posição Inválida"
posicao (h:t) x | x > 0 = posicao t (x-1)

--Ex5
revertt :: [a] -> [a]
revertt [] = [];
revertt (h:hs) = maismais (revertt hs) [h]

--Ex6
takee :: Int -> [a] -> [a]
takee 0 l = []
takee _ [] = []
takee n (h:t) = h : takee (n-1) t

--Ex7
dropp :: Int -> [a] -> [a]
dropp n [] = []
dropp 0 l = l
dropp n (h:t) = dropp (n-1) t

--Ex8
zipp :: [a] -> [b] -> [(a,b)]
zipp l [] = []
zipp [] h = []
zipp (x:xs) (y:ys) = (x,y):zipp xs ys

--Ex9
replicatee :: Int -> a -> [a]
replicatee 0 h = []
replicatee x y = y : replicatee (x-1) y

--Ex10
interspersee :: a -> [a] -> [a]
interspersee n [] = []
interspersee n [x] = [x]
interspersee x (y:ys) = y:x: (interspersee x ys)

--Ex11
groupp :: Eq a => [a] -> [[a]]
groupp [] = []
groupp [x] = [[x]]
groupp (h:t) | h == head p = ((h:p):ps)
             | otherwise = ([h]:p:ps)
            where (p:ps) = groupp t

--Ex12
concatt :: [[a]] -> [a]
concatt [] = []
concatt (h:t) = h ++ concatt t

--Ex13
initss :: [a] -> [[a]]
initss [] = [[]]
initss a = initss (init a) ++ [a]

--Ex14
tailss :: [a] -> [[a]]
tailss [] = [[]]
tailss a = a : tailss (tail a)

--Ex15
headss :: [[a]] -> [a]
headss [] = []
headss ([]:t) = headss t
headss ((h:hs):xs) = h: headss xs

--Ex16
totall :: Eq a => [[a]] -> Int
totall [] = 0
totall ([]:t) = 0 + totall t
totall ((h:t):ts) = 1 + totall (t:ts)


--Ex17
fun :: [(a,b,c)] -> [(a,c)]
fun [(a,b,c)] = [(a,c)]
fun ((a,b,c):hs) = [(a,c)] ++ fun hs

--Ex18
cola :: [(String,b,c)] -> String
cola [(a,b,c)] = a
cola ((a,b,c):hs) = a ++ cola hs

--Ex19
idade :: Int -> Int -> [(String,Int)] -> [String]
idade aa i [] = []
idade aa i ((nome,nasc):hs) | aa - nasc >= i = [nome] ++ idade aa i hs
                            | otherwise = idade aa i hs

--Ex20
powerEnumFrom :: Int -> Int -> [Int]
powerEnumFrom n 1 = [1]
powerEnumFrom n m
        | m > 1     = powerEnumFrom n (m - 1) ++ [n^(m-1)]
        | otherwise = []
--Ex21
isPrime :: Int -> Bool
isPrime n   | divisoes n 2 == 0 =  True
            | otherwise = False

divisoes :: Int -> Int -> Int
divisoes a b | b >= a = 0
             | mod a b == 0 = 1
             | otherwise = divisoes a (b+1)
--Ex22
isPrefixOff :: Eq a => [a] -> [a] -> Bool
isPrefixOff [] [] = True
isPrefixOff [] _ = True
isPrefixOff _ [] = False
isPrefixOff (x:xs) (y:ys) | x == y = isPrefixOff xs ys
                          | otherwise = False
--Ex23
isSuffixOff :: Eq a => [a] -> [a] -> Bool
isSuffixOff [] _ = True
isSuffixOff _ [] = False
isSuffixOff (x:xs) (y:ys)| x /= y = isSuffixOff xs (y:ys)
                         |otherwise = False

--Ex24
isSubsequenceOff :: Eq a =>[a] -> [a] -> Bool
isSubsequenceOff [] x = True
isSubsequenceOff x [] = False
isSubsequenceOff (x:xs) (y:ys) | x == y = isSubsequenceOff (xs) (ys)
                               | otherwise = isSubsequenceOff (x:xs) (ys)
--Ex25
elemIndicess :: Eq a => a ->[a] -> [Int]
elemIndicess _ [] = []
elemIndicess x (h:t) | x == h = 0 : map (+1) (elemIndicess x t)
                        | otherwise =  map (+1) (elemIndicess x t)

--Ex26
nubb :: Eq a => [a] -> [a]
nubb [] = []
nubb (h:t) | elem h t = nub t
           | otherwise = h : nub t

--Ex27
deletee :: Eq a => a -> [a] -> [a]
deletee _ [] = []
deletee a (h:t) | h == a = t
                | otherwise = h : deletee a t

--Ex28
dbslash :: Eq a => [a] -> [a] -> [a]
dbslash a [] = a
dbslash (x:y) (h:t) | x == h = dbslash y t
                | otherwise = x : dbslash y (h:t)

--Ex29
unionn :: Eq a => [a] -> [a] -> [a]
unionn [] a = a
unionn a [] = a
unionn l (a:as) | elem a l = unionn l as
                | otherwise = unionn (l ++ [a]) as

--Ex30
intersectt :: Eq a => [a] -> [a] -> [a]
intersectt (h:t) (x:xs) | h == x = h : intersectt t (x:xs)
                        | otherwise = x : intersectt (x:xs) t
intersectt _ _ = []

--Ex31
insertt :: Ord a => a -> [a] -> [a]
insertt a [] = [a]
insertt a (h:t) | a >= h = h : insertt a t
                | otherwise = a:h:t

--Ex32
unwordss :: [String] -> String
unwordss [] = []
unwordss [x] = x
unwordss (h:t) = h ++ " " ++  unwordss t

--Ex33
unliness :: [String] -> String
unliness [] = []
unliness [x] = x
unliness (h:t) = h ++ "\n" ++  unliness t

--Ex34
pMaior :: Ord a => [a] -> Int
pMaior [x] = 0
pMaior (x:xs) | x == (xs !! p) = 0
              | otherwise = 1 + pMaior xs
               where p = pMaior xs

--Ex35
lookupp :: Eq a => a -> [(a,b)] -> Maybe b
lookupp _ [] = Nothing
lookupp a ((x,xs):t) | a == x = Just xs
                     | otherwise = lookupp a t

--Ex36   
preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente [x] = [x]
preCrescente (h:i:t) | h < i = h : preCrescente (i:t)
                     | otherwise = [h]

--Ex37
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort (h:t) = insertt h (iSort t)

--Ex38
menor :: String -> String -> Bool
menor "" x = True
menor x "" = False
menor (h:t) (x:xs) = menor t xs

--Ex39
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet a [] = False
elemMSet a ((x,xs):t) | a == x = True
                      | otherwise = elemMSet a t

--Ex40
converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((x,xs):t) | xs > 0 = x : converteMSet ((x,xs-1):t)
                        | otherwise = converteMSet t

--Ex41
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet a [] = []
insereMSet a ((x,xs):t) | x == a = ((x,xs+1):t)
                        | otherwise = (x,xs) :insereMSet a t

--Ex42
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet a [] = []
removeMSet a ((x,xs):t) | x == a && xs > 1= ((x,xs-1):t)
                        | x /= a = (x,xs) : removeMSet a t
                        | otherwise = t

--Ex43 mind cracker
constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (h:t) = (h,1 + length (filter (==h) t)):constroiMSet (filter (/=h) t)

--Ex44
partitionEitherss :: [Either a b] -> ([a],[b])
partitionEitherss [] = ([],[])
partitionEitherss l = (partitionLeft l, partitionRight l)
    where partitionLeft [] = []
          partitionLeft ((Left x):xs) = x : partitionLeft xs
          partitionLeft ((Right _):xs) = partitionLeft xs
          partitionRight [] = []
          partitionRight ((Right x):xs) = x : partitionRight xs
          partitionRight ((Left _):xs) = partitionRight xs

--Ex45
catMaybees :: [Maybe a ] -> [a]
catMaybees [] = []
catMaybees ((Just a): xs) = a : catMaybees xs
catMaybees (Nothing: xs) = catMaybees xs


--Ex46
data Movimento = Norte | Sul | Este | Oeste
               deriving Show
caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (a,b) (c,d)   | a > b = Oeste : caminho (a-1,c) (b,d)
                      | a < b = Este : caminho (a+1, c) (b,d)
                      | c > d = Sul : caminho (a, c-1) (b,d)
                      | c < d = Norte : caminho (a, c+1) (b,d)
                      | otherwise = []

--Ex47 todo
hasLoops :: (Int,Int) -> [Movimento] -> Bool
hasLoops (a,b) [] = False
hasLoops (a,b) x
           | elem (a,b) (aux (a,b) x) = True
           | otherwise                = False

aux :: (Int,Int) -> [Movimento] -> [(Int,Int)]
aux (a,b) [] = []
aux (a,b) (x:xs) = case x of
  Norte -> (a,b+1):aux (a,b+1) xs
  Sul -> (a,b-1):aux (a,b-1) xs
  Este -> (a+1,b):aux (a+1,b) xs
  Oeste -> (a-1,b):aux (a-1,b) xs


--Ex48
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto
contaQuadrados :: [Rectangulo] -> Int
contaQuadrados ((Rect (a,b)(c,d)): xs) | abs(a-c) == abs(b-d) = 1 + contaQuadrados xs
                                       | otherwise = contaQuadrados xs

--Ex49
areaTotal :: [Rectangulo] -> Float
areaTotal [] = 0
areaTotal ((Rect (a,b) (c,d)):t) = abs((a-b)*(c-d)) + areaTotal t

--Ex50
data Equipamento = Bom | Razoavel | Avariado
               deriving Show
naoReparar :: [Equipamento] -> Int
naoReparar [] = 0
naoReparar (Avariado:t) = naoReparar t
naoReparar (_:t) = 1+ naoReparar t