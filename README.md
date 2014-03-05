Broadcasting---Low-Exponent-RSA-Attack
======================================

In this project we are dealing with decrypting a cipher which was encrypted using RSA. 
We are employing the Chinese remainder theorem to decrypt the ciphertext.
 To study RSA algorithm in detail.
 To understand the Chinese remainder theorem. 
 To be able to successfully decrypt the ciphertext using the Chinese remainder theorem. 
 To be able to use the public exponents and moduli from the given certificates of the three business partners.
 Suggest methods that can be implemented in order to avoid attacks.

// Instruction To Run
find the following files in this folder 

CRT_RSA.c file contains the main program of this challenge
and remaining files are used to invoke the bigdigits functions

so to compile and execute use following commands in the terminal

gcc CRT_RSA.c bigd.c bigd.h bigdigits.c bigdigits.h bigdtypes.h

./a.out


// INTRODUCTION

RSA algorithm is a public key cryptosystem [named after the inventors Rivest, Shamir and Adleman], like other public key cryptosystem this is also based on a complex mathematical problem. This algorithm is based on the factoring problem where a public and a private key pair are selected.

* Cube Root Attack:
When a small encryption exponent such as e=3 is used and if M < N1/3.
The Ciphertext C = Me mod N
Since M < N1/3 mod N has no effect.
C = Me = M3
M = 3√C (the cube root of Ciphertext will give the message).

* Chinese Remainder Theorem:
Chinese remainder theorem is a result about congruencies in number theory. Using the theorem we can determine a number n that when divided by some given divisors leaves given remainders.

Using the theorem can find that the value of number n is 23, that when divided by 3 leaves a remainder of 2, when divided by 5 leaves a remainder of 3, and when divided by 7 leaves a remainder of 2.
Theorem: Let n1,n2,...,nr be positive integers such that gcd(ni,nj)=1 for i ≠ j. Then the system of linear congruence’s
x ≡ c1 (mod n1); x ≡ c2 (mod n2); ... ; x ≡ cr (mod nr)
has a simultaneous solution which is unique modulo n1n2...nr.


