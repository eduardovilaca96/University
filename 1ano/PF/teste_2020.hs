import Data.List
import System.IO
import Data.Char
import Data.Either
--1
--(a)
intersect2 :: Eq a => [a] -> [a] -> [a]
intersect2 (x:xs) l | elem x l = x : intersect2 xs l
                         | otherwise = intersect2 xs l 
intersect2 _ _ = []

--(b)
tailss :: [a] -> [[a]]
tailss [] = [[]]
tailss l = l : tailss (tail l)

--2
type ConjInt = [Intervalo]
type Intervalo = (Int,Int)

--(a)
elems :: ConjInt -> [Int]
elems [] = []
elems ((a,b):xs) = nub ([a] ++ [b] ++ elems xs)

--(b)
geraconj :: [Int] -> ConjInt
geraconj (x:y:ys) = [(x,y)] ++ geraconj ys 
geraconj _ = []

--3
data Contacto = Casa Integer | Trab Integer | Tlm Integer | Email String deriving (Show,Eq)
type Nome = String
type Agenda = [(Nome, [Contacto])]

--(a)
acrescEmail :: Nome -> String -> Agenda -> Agenda                     
acrescEmail x y [] = [(x,[Email y])];
acrescEmail nome email ((x,y):xs) | x == nome = ((x,y++[(Email email)]):xs) 
                                  | otherwise = [(x,y)] ++ (acrescEmail nome email (xs))

--(b)
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails _ [] = Nothing
verEmails nome ((x,l):xs) | nome == x = Just (selectEmails l)  
                          | otherwise = verEmails nome xs

selectEmails :: [Contacto] -> [String]
selectEmails ((Casa t):ys) = selectEmails ys
selectEmails ((Tlm t):ys)  = selectEmails ys
selectEmails ((Trab t):ys) = selectEmails ys
selectEmails ((Email t):ys) = [t] ++ selectEmails ys
selectEmails _ = []
--(c)
consulta :: [Contacto] -> ([Integer],[String])
consulta [] = ([],[])
consulta l = (telemoveis l, emails l) 
                  where telemoveis [] = []
                        telemoveis ((Casa x):xs) = x : telemoveis xs
                        telemoveis ((Tlm x):xs) = x : telemoveis xs
                        telemoveis ((Trab x):xs) = x : telemoveis xs
                        telemoveis ((Email _):xs) = telemoveis xs
                        emails [] = []
                        emails ((Email x):xs) = x : emails xs
                        emails ((Casa _):xs) = emails xs
                        emails ((Tlm _):xs) = emails xs
                        emails ((Trab _):xs) = emails xs
--(d)
verEmails2 :: Nome -> Agenda -> [String]
verEmails2 _ [] = []
verEmails2 nome ((x,l):xs) | nome == x = selectEmails l  
                           | otherwise = verEmails2 nome xs

verNumeros :: Nome -> Agenda -> [Contacto]
verNumeros _ [] = []
verNumeros nome ((x,l):xs) | nome == x = selectNum l  
                           | otherwise = verNumeros nome xs

selectNum :: [Contacto] -> [Contacto]
selectNum ((Casa t):ys) = [(Casa t)] ++ selectNum ys
selectNum ((Tlm t):ys)  = [(Tlm t)] ++ selectNum ys
selectNum ((Trab t):ys) = [(Trab t)] ++ selectNum ys
selectNum ((Email t):ys) = selectNum ys
selectNum _ = []


consultaIO :: Agenda -> IO ()
consultaIO l = 
            do
            putStrLn "Nome do Contacto:"
            nome <- getLine
            let name = read nome :: String
            let emails = (verEmails2 nome l)
            let numeros = (verNumeros nome l)
           
            if (emails == []) 
                then print ("Nao existem emails associados a " ++ nome)
            else print("Emails:")
            print emails    
            
            if (numeros == []) 
                then print ("Nao existem numeros associados a " ++ nome)
            else print("Numeros:")
            print numeros
--4
data Rtree a = R a [Rtree a] deriving (Show,Eq)
--(a)
paths :: Rtree a -> [a]
paths (R r e d) = 