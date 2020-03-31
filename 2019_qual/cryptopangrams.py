#Adapted from how-you-doin'-lewin's solution at
#https://codingcompetitions.withgoogle.com/codejam/submissions/0000000000051705/aG93LXlvdS1kb2luJy1sZXdpbg

#import libraries
from sortedcontainers import SortedSet

#Get number of test cases
t = int(raw_input())

#Find GCD of two numbers
def gcd(a,b):
    if b == 0:
        return a
    return gcd(b, a%b)

#Add primes to set and dict
def add_primes(message,primes,ptp,pr,i):

    #Set
    primes.add(pr)

    #Dict
    ptp[i] = pr

#Iterate left through ciphertext
def step_left(message,primes,ptp,pr,n,i):

    #Find new prime and verify validity
    new_pr = message[i+1]/pr
    assert new_pr <= n

    #Store primes
    add_primes(message,primes,ptp,new_pr,i)

    #Step if necessary
    if i>=0: step_left(message,primes,ptp,new_pr,n,i-1)

#Iteratre right through ciphertext
def step_right(message,primes,ptp,pr,n,i,l):

    #Find new prime and verify validity
    new_pr = message[i]/pr
    assert new_pr <= n

    #Store primes
    add_primes(message,primes,ptp,new_pr,i)

    #Step if necessary
    if i<=l-2: step_right(message,primes,ptp,new_pr,n,i+1,l)

#Iterate through ciphertext
def step(message,primes,ptp,pr,n,i,l):

    #Iterate right through ciphertext
    if i<=l-2: step_right(message,primes,ptp,pr,n,i+1,l)

    #Iterate left through ciphertext
    if i>=0: step_left(message,primes,ptp,pr,n,i-1)

def solve():

    #Get ciphertext info
    n,l = map(int, raw_input().split())
    message = map(int, raw_input().split())

    #Variable declaration
    primes = SortedSet()
    entry = False
    ptp = {}      #Used to maintain order of primes in ciphertext (Plaintext Primes)
    primesAndChars = {}
    pt = ""
    prime = 0

    #Look for entry-point
    for i in xrange(l-1):
        if message[i] != message[i+1]:
            
            #Control end of loop
            entry = True

            #Find gcd and verify validity
            pr = gcd(message[i], message[i+1])
            assert pr <= n

            #Add primes to set and dict
            primes.add(pr)
            ptp[i] = pr
            
            #Step through ciphertext
            step(message,primes,ptp,pr,n,i,l)

        #End loop    
        if entry: i = l-1

    #Pair letters with primes
    letter = "A"
    for p in primes:
        primesAndChars[p] = letter
        letter = chr(ord(letter[0]) + 1)

    #Create plaintext using Index-Prime pairs and Prime-Char pairs
    for i in xrange(l+1):
        prime = ptp[i-1]
        pt += primesAndChars[prime]

    return pt
    
for __ in xrange(t):
    print "Case #%d: %s" % (__+1, solve())

#Produced a Runtime Error on Code Jam server with hidden test sets
