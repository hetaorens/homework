def rsa(bits):
    proof = (bits <= 1024)
    p = next_prime(ZZ.random_element(2**(bits//2+1)),
                   proof=proof)
    q = next_prime(ZZ.random_element(2**(bits//2+1)),
                   proof=proof)
    n = p*q
    phi_n = (p-1)*(q-1)
    while True:
        e = ZZ.random_element(1,phi_n)
        if gcd(e,phi_n) == 1: break
    d = lift(Mod(e,phi_n)^(-1))
    return e, d, n
def encode(s):
     s = str(s)
     return sum(ord(s[i])*256^i for i in range(len(s)))

def decode(n):
     n = Integer(n)
     v = []
     while n != 0:
         v.append(chr(n % 256))
         n //= 256     # this replaces n by floor(n/256)
     return ''.join(v)
def encrypt(m, e, n):
     return lift(Mod(m,n)^e)

def decrypt(c, d, n):
     return lift(Mod(c,n)^d)
