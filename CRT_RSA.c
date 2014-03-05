
#include <stdio.h>
#include "bigd.h"
#include <string.h>
#include<ctype.h>


int main(void)
{
	BIGD m, e, n1, n2, n3, c1, c2, c3, N, N1, N2, N3, d1, d2, d3, s, t, x;
unsigned char *s2;
            int i;	
        m = bdNew();
	e = bdNew();
	n1 = bdNew();
	n2 = bdNew();
	n3 = bdNew();
	c1 = bdNew();
	c2 = bdNew();
	c3 = bdNew();
	N = bdNew();
	N1 = bdNew();
	N2 = bdNew();
	N3 = bdNew();
	d1 = bdNew();
	d2 = bdNew();
	d3 = bdNew();
	s = bdNew();
	t = bdNew();
	x = bdNew();

 
 size_t smax;
	/* Read in modulus values for three 512-bit public keys */

	bdConvFromHex(n1, "009623511e6769644d693e89f692ffc2558eef121d42ca98699781e139e29c2e1aa58d8883bbdba41165fdeb85a9a5648fc29a65d59e9401694dd11ae205f0ce3b");
	bdConvFromHex(n2, "00ad4bc0f980f4523f490fc40c12efcecc1e8af67890b6562449876e8e091e861cda699e5a8eb309b0a9d6b293100c1229fbd18a5951f33b6fbab1fd8d90f7c829");
	bdConvFromHex(n3, "00b7223364d88353ec02b0850e8a01d2ba9ca2663c32c15df7b596406c6fc1c171ac965a554b8b338f4bb046c543937b4b19c699864f1d0dd4be0177eccce0bb57");
	
	printf("Three public modulus values, 512 bits each...\n");
	bdPrintDecimal("n1=", n1, "\n");
	bdPrintDecimal("n2=", n2, "\n");
	bdPrintDecimal("n3=", n3, "\n");
	
	/* The three public keys all have public exponent e = 3 */
	bdSetShort(e, 3);
	bdPrintHex("e=", e, "\n");
	
	
        bdConvFromHex(c1, "34d2fc2fa4785e1cdb1c09c9a5db98317d702aaedd2759d96e8938f740bf982e2a42b904e54dce016575142f1b0ed112cc214fa8378b0d5eebc036dc7df3eeea");
	bdConvFromHex(c2, "3ddd68eeff8be9fee7d667c3c0ef21ec0d56cefab0fa10199c933cffbf0924d486296c604a447f48b9f30905ee49dd7ceef8fc689a1c4c263c1b3a9505091b00");
	bdConvFromHex(c3, "956f7cbf2c9da7563365827aba8c66dc83c9fb77cf7ed0ca225e7d155d2f573d6bd18e1c18044cb14c59b52d3d1f6c38d8941a1d58942ed7f13a52caccc48154");
		


        printf("Three ciphertexts...\n");
	bdPrintHex("c1=", c1, "\n");
	bdPrintHex("c2=", c2, "\n");
	bdPrintHex("c3=", c3, "\n");

	/* An eavedropper has the public values n1, n2, n3, c1, c2 and c3 */

	/* Check that n1, n2, n3 are coprime in pairs */
	bdGcd(t, n1, n2);
	bdPrintDecimal("gcd(n1,n2)=", t, "\n");
	bdGcd(t, n2, n3);
	bdPrintDecimal("gcd(n2,n3)=", t, "\n");
	bdGcd(t, n3, n1);
	bdPrintDecimal("gcd(n3,n1)=", t, "\n");

	/* Compute N = n1 * n2 * n3 */
	bdMultiply(t, n1, n2);
	bdMultiply(N, t, n3);
	 bdPrintHex("N=", N, "\n");

	/* Compute N_i = N/n_i for i = 1,2,3 */
	bdMultiply(N1, n2, n3);
        bdPrintHex("N1=", N1, "\n");
        bdMultiply(N2, n1, n3);
	bdPrintHex("N2=", N2, "\n");
        bdMultiply(N3, n1, n2);
	bdPrintHex("N3=", N3, "\n");

        if (0) bdPrintDecimal("N1=", N1, "\n");
	if (0) bdPrintDecimal("N2=", N2, "\n");
	if (0) bdPrintDecimal("N3=", N3, "\n");

	/* Compute d_i = N_i^{-1} mod n_i for i = 1,2,3  */
	bdModInv(d1, N1, n1);
	bdModInv(d2, N2, n2);
	bdModInv(d3, N3, n3);
	bdPrintHex("d1=", d1, "\n");
	bdPrintHex("d2=", d2, "\n");
	bdPrintHex("d3=", d3, "\n");

	/* Compute x = c_1 N_1 d_1 + c_2 N_2 d_2 + c_3 N_3 d_3 (mod N) */
	bdModMult(s, c1, N1, N);
	bdModMult(x, s, d1, N);
	bdModMult(s, c2, N2, N);
	bdModMult(t, s, d2, N);
	bdAdd_s(x, x, t);
	bdModMult(s, c3, N3, N);
	bdModMult(t, s, d3, N);
	bdAdd_s(s, x, t);
	bdModulo(x, s, N);
	printf("Computed value of x = c_1 N_1 d_1 + c_2 N_2 d_2 + c_3 N_3 d_3 (mod N)...\n");
	bdPrintHex("x=", x, "\n");

	/* Compute the integer cube root of x */
	bdCubeRoot(t, x);
        	
/* Converting BigDigit Hex value into String */
bdPrintHex("cuberoot(x)=", t, "\n");

char *s1 = (char*)malloc(128);
bdConvToHex(t,s1,127);

 unsigned char *src;

  src=s1;
  char buffer[63];
    char *dst = buffer;
    char *end = buffer + sizeof(buffer);
    unsigned int u;

 printf("plaintext = ");
   while (dst < end && sscanf(src, "%2x", &u) == 1)
    {
        *dst++ = u;
        src += 2;
    }

    for (dst = buffer; dst < end; dst++)
        printf("%c",
               (isprint(*dst) ? *dst : '.'));
   printf("\n");
//clean_up:
	bdFree(&m);
	bdFree(&e);
	bdFree(&n1);
	bdFree(&n2);
	
        bdFree(&n3);
	bdFree(&c1);
	bdFree(&c2);
	bdFree(&c3);
	bdFree(&N);
	bdFree(&N1);
	bdFree(&N2);
	bdFree(&N3);
	bdFree(&d1);
	bdFree(&d2);
	bdFree(&d3);
	bdFree(&s);
	bdFree(&t);
	bdFree(&x);
	
	return 0;
}


