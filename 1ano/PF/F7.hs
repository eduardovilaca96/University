data Frac = F Int Int

normalize :: Frac -> Frac
normalize (F n d) = F n' d'
                    where n' = div n (gcd (abs n) (abs d))
                          d' = div d (gcd (abs n) (abs d))

instance Show Frac where
    show (F a b) = show a ++ " / " ++ show b

instance Eq Frac where
    (==) (F a b) (F x y) =  a == x && b == y

instance Ord Frac where
    (<=) (F a b) (F x y) | b * y > 0 = a * y <= b * x
                         | otherwise = b * x <= a * y

instance Num Frac where
  (+) (F a b) (F x y) = normalize(F n' d')
                        where n' = a * y + x * b
                              d' = b * y

  (*) (F a b) (F x y) = normalize(F n' d')
                        where n' = a * x
                              d' = b * y
  abs (F x y) = F (abs x) (abs y)
  signum (F x y) | x == 0 = F 0 1
                 | x < 0 && y < 0 = F 1 1
                 | x < 0 || y < 0 = F (-1) 1
                 | otherwise = F 1 1

  fromInteger x = F (fromInteger x ) 1
  negate (F x y) = F (x * (-1) )y


dobros :: Frac -> [Frac] -> [Frac]
dobros f [] = []
dobros f (h:t) | h > (f * 2) = h : dobros f t
               | otherwise = dobros f t

data Exp a = Const a
            | Simetrico (Exp a)
            | Mais (Exp a) (Exp a)
            | Menos (Exp a) (Exp a)
            | Mult (Exp a) (Exp a)



instance Show a => Show (Exp a) where
    show (Const a) = show a
    show (Simetrico a) = "-" ++ show a
    show (Mais a b) = "(" ++ show a ++ " + " ++ show b ++ ")"
    show (Menos a b) = "(" ++ show a ++ " - " ++ show b ++ ")"
    show (Mult a b) = "(" ++ show a ++ " * " ++ show b ++ ")"