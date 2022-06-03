import math
from random import randint
import sys
import libnum
import random

class my_rsa:
    debug = False

    def __init__(self, limit=sys.maxsize):
        self.limit = limit
        self.n = 0
        self.phi = 0
        self.e = 0
        self.d = 0
        self.create_keys(self.limit)
        self.public_key = (self.n, self.e)
        self.private_key = (self.n, self.d)

    '''公钥、私钥计算和存储的主要方法
        它们作为对象类的字段'''

    # 针对随机取得p，q两个数的素性检测

    def miller_rabin_test(self,n):  # p为要检验得数
        p = n - 1
        r = 0
        # P110定理5.17 P108定理5.3.6
        # 寻找满足n-1 = 2^s  * m 的s,m两个数
        #  n -1 = 2^r * p
        while p % 2 == 0:  # 最后得到为奇数的p(即m)
            r += 1
            p /= 2
        b = random.randint(2, n - 2)  # 随机取b=（0.n）
        # 如果情况1    b得p次方  与1  同余  mod n
        if self.fastExpMod(b, int(p), n) == 1:
            return True  # 通过测试,可能为素数
        # 情况2  b得（2^r  *p）次方  与-1 (n-1) 同余  mod n
        for i in range(0, 7):  # 检验六次
            if self.fastExpMod(b, (2 ** i) * p, n) == n - 1:
                return True  # 如果该数可能为素数，
        return False  # 不可能是素数

    # 生成大素数：
    def create_prime_num(self,keylength):  # 为了确保两素数乘积n  长度不会太长，使用keylength/2
        while True:
            # Select a random number n
            # n = random.randint(0, 1<<int(halfkeyLength))
            n = random.randint(0, keylength)
            if n % 2 != 0:
                found = True
                # 如果经过10次素性检测，那么很大概率上，这个数就是素数
                for i in range(0, 10):
                    if self.miller_rabin_test(n):
                        pass
                    else:
                        found = False
                        break
                if found:
                    return n

    # 随机在（1，fn）选择一个E，  满足gcd（e,fn）=1
    def selectE(self,fn, halfkeyLength):
        while True:
            # e and fn are relatively prime
            e = random.randint(0, fn)
            if math.gcd(e, fn) == 1:
                return e
    # # 生成密钥（包括公钥和私钥）
    def create_keys(self, keylength):
        self.p = self.create_prime_num(keylength / 2)
        self.q = self.create_prime_num(keylength / 2)
        assert self.p!=self.q
        self.n = self.p * self.q
        # euler函数值
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = self.selectE(self.phi, keylength / 2)
        self.d = self.modulo_mult_inverse(self.e, self.phi)
        # return (n, e, d)/

        print("public key", (self.n, self.e))
        print("private key", (self.n, self.d))


    # 计算两个整数的扩展最大公约数的方法
    # a and b.
    def extended_gcd(self, b, a):
        x, lastx, y, lasty = 0, 1, 1, 0
        while a != 0:
            quotient = b // a
            remainder = b % a
            if self.debug:
                print("quotient", quotient)
                print("remainder", remainder)
            m = x - lastx * quotient
            n = y - lasty * quotient
            if self.debug:
                print("m = x - lastx*quotient:", x, "-", lastx, "*", quotient, "=", m)
                print("n = y = lasty*quotient: ", y, "-", lasty, "*", quotient, "=", n)
            b = a
            a = remainder
            if self.debug:
                print("b = a: b =", a)
                print("a = remainder: a =", remainder)
            x = lastx
            y = lasty
            if self.debug:
                print("x = lastx: x=", lastx)
                print("y = lasty: y=", lasty)
            lastx = m
            lasty = n
            if self.debug:
                print("lastx = m: lastx = ", m)
                print("lasty = n: lasty = ", n)
                print("--------------------------------------")
        return (b, x, y)

    # 模N大数的幂乘的快速算法
    @staticmethod
    def fastExpMod(b, e, m):  # 底数，幂，大数N
        result = 1
        e = int(e)
        while e != 0:
            if e % 2 != 0:  # 按位与
                e -= 1
                result = (result * b) % m
                continue
            e >>= 1
            b = (b * b) % m
        return result


    ''' 
    方程
    d*e mod(phi(n)) = 1  
    式中，d为模乘逆，e为待考虑参数，
    phi(n)是n的欧拉函数 (n=p*q = (p-1)*(q-1) = phi(n))
    '''

    def modulo_mult_inverse(self, e, phi):
        b, x, y = self.extended_gcd(phi, e)
        if b == 1:
            return x % phi
        return None

    '''	
        使用Karatsuba乘法算法将两个数字相乘
        时间复杂度:O(n^1.585). 
        这比传统的O(n²)要快得多正常的乘法运算方法。
    '''

    def karatsuba(self, x, y, b):
        num_half_bitsX = len(str(x)) / 2
        num_half_bitsY = len(str(y)) / 2
        if num_half_bitsX < num_half_bitsY:
            m = num_half_bitsX
        else:
            m = num_half_bitsY
        coeff = b ** m
        if min(x, y) < (b ** (len(str(x)))):
            return x * y
        x1 = x / coeff
        x0 = x % (x1 * coeff)
        y1 = y / coeff
        y0 = y % (y1 * coeff)

        p0 = self.karatsuba(x0, y0, b)
        p2 = self.karatsuba(x1, y1, b)
        q = self.karatsuba((x0 + x1), (y0 + y1), b)
        p1 = q - p0 - p2
        sum_first = self.karatsuba(p2, coeff, b) + p1
        sum_final = self.karatsuba(sum_first, coeff, b) + p0
        return sum_final

    '''

        使用Atkins筛算法计算所有的质数直到满足“limit”参数。
    '''

    def sieve_atkins(self, limit):
        result = [2, 3, 5]
        is_prime = [False] * (limit + 1)
        factor = int(math.sqrt(limit)) + 1
        for x in range(1, factor):
            for y in range(1, factor):
                n = 4 * (x ** 2) + (y ** 2)
                if (n <= limit) and ((n % 12 == 1) or (n % 12 == 5)):
                    is_prime[n] = not is_prime[n]
                n = 3 * (x ** 2) + (y ** 2)
                if (n <= limit) and ((n % 12) == 7):
                    is_prime[n] = not is_prime[n]
                if x > y:
                    n = 3 * (x ** 2) - (y ** 2)
                    if (n <= limit) and ((n % 12 == 11)):
                        is_prime[n] = not is_prime[n]
        for i in range(5, factor):
            if is_prime[i]:
                jump = i ** 2
                for j in range(i ** 2, limit, jump):
                    is_prime[j] = False
        for index in range(7, limit):
            if is_prime[index]:
                result.append(index)
        return result

    def encryption(self, message: bytes):
            # print(message)
            n=libnum.s2n(message)
            print(n)
            c_num=self.fastExpMod(n,self.e,self.n)

            return libnum.n2s(c_num)
    def decryption(self,cipher:bytes):
        c_num=libnum.s2n(cipher)
        m_num=self.fastExpMod(c_num,self.d,self.n)
        print(m_num)
        return libnum.n2s(m_num)


'''
库的使用
>>> import my_rsa
>>> enc =my_rsa.my_rsa(23)
public key (1472, 29)
private key (1472, 914)

>>> import my_rsa
>>> enc =my_rsa.my_rsa(1000000)

public key (2104893971370, 308193614463)
private key (2104893971370, 699515598545)

>>> enc =my_rsa.my_rsa() 
public key (10468427810168432640, 9554926832143394029)
private key (10468427810168432640, 15581655766859127013)
'''
enc = my_rsa(1<<64)

x=enc.encryption(b'this demo')
print(x)
y=enc.decryption(x)
print(y)
#
