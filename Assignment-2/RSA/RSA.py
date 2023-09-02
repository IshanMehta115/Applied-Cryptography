'''
    Name: Ishan Mehta
    Roll: 2019309
    Implementation of RSA
'''
import sys
import random
import math
sys.setrecursionlimit(1500)
primes = []
# find all primes which are not more than limit, using Sieve of Eratosthenes.
def generate_primes(limit):
    global primes
    is_prime = []
    for i in range(limit + 1):
        is_prime.append(True)
    
    for i in range(2,limit + 1):
        if(is_prime[i]):
            j = (i*i)
            while j<=limit:
                is_prime[j] = False
                j+=i
    
    for i in range(2,limit + 1):
        if(is_prime[i]):
            primes.append(i)

# returns a random odd integer of 'bits' bitlength.
def get_prime_candidate(bits):
        prime_candidate = random.randint(2**(bits-1),(2**bits) - 1)
        if(prime_candidate%2==0):
            prime_candidate+=1
        return prime_candidate

# return False if prime_candidate is divisible by any pre computed prime, True otherwise
def initial_check(prime_candidate):
    for prime in primes:
        if prime_candidate%prime==0:
            return False
    return True


# return true if a is a witness, false otherwise
def witness(a,k,m,p):
    b = pow(a, m, p)
    if b == 1:
        return False
    
    for i in range(k):
        if((-1%p)==(b%p)):
            return False
        b = (b*b)%p
    return True

# returns true if prime_candidate passes miller_rabin_test, false otherwise
def miller_rabin_test(prime_candidate):
    if not initial_check(prime_candidate):
        return False

    temp = prime_candidate - 1
    k = 0
    while temp%2==0:
        temp//=2
        k+=1
    m = temp

    # testing for 50 witnesses
    for j in range(70):
        a = random.randint(2,prime_candidate-2)
        if witness(a,k,m,prime_candidate):
            return False
    return True     

# returns a probable prime of 'bits' bitlength using miller-rabin test
def get_prime(bits):
    prime_candidate = get_prime_candidate(bits)
    while not miller_rabin_test(prime_candidate):
        prime_candidate = get_prime_candidate(bits)
    return prime_candidate

def extended_euclidean_algo(a,b):
    if b==0:
        return a,1,0
    g_dash,s_dash,t_dash = extended_euclidean_algo(b,a%b)
    return g_dash, t_dash, s_dash - t_dash*(a//b)
def Keys():
    generate_primes(10**7)
    random.seed(117)
    p = get_prime(1024)
    q = get_prime(1024)
    n = p*q
    phi_n = (p-1)*(q-1)
    e = random.randint(1,phi_n)
    while math.gcd(e,phi_n)!=1:
        e = random.randint(1,phi_n)
    gcd,s,t = extended_euclidean_algo(phi_n,e)
    d = t%phi_n    
    return ((n,e), d)

# encryptes message m using public key
def Enc(public_key, m):
    n = public_key[0]
    e = public_key[1]
    return pow(m,e,n)

# encryptes cipher c using private key. It also has access to public key
def Dec(private_key,public_key,c):
    d = private_key
    n = public_key[0]
    return pow(c,d,n)



public_key, private_key = Keys()
m = random.randint(0,2**32-1)
c = Enc(public_key, m)
d = Dec(private_key,public_key, c)

print("\nmessage ->\n",m)
print("\nencrypted ->\n",c)
print("\ndecrypted ->\n",d)

if m==d:
    print("original message and decrypted message are same")
else:
    print("original message and decrypted message are not same")
