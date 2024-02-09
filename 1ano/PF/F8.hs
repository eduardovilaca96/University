data Movimento = Credito Float | Debito Float
data Data = D Int Int Int 
    deriving Ord
data Extracto = Ext Float [(Data, String, Movimento)]
data Frac = F Int Int

normalize :: Frac -> Frac
normalize (F n d) |(n' < 0) && (d' < 0) = F (abs n') (abs d')
                  | otherwise = F (-n') (abs d')
                    where n' = div n (gcd (abs n) (abs d))
                          d' = div d (gcd (abs n) (abs d))

instance Show Data where
    show (D d m a) = show d ++ "/" ++ show m ++ "/" ++ show a

instance Eq Data where
    (==) (D d1 m1 a1) (D d2 m2 a2) =  d1 == d2 && m1 == m2 && a1 == a2
