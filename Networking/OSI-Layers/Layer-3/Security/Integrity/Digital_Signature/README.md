## DIGITAL SIGNATURE
- **What?** This is Hash encrypted by PVT-KEY.
- **DS Provides?**
  - *a.* Integrity
  - *b.* Nonrepudiation(only sender has pvt key and no one else)
  - *c.* Authentication
```console
    message > |Hash(MD5)| > |Encrypt| >    Digital-Signature    >     |Decrypt| > Hash
                              /\                                         /\
                             Pvt-key                                  Public-key
```

### Algorithms for Generating DS
- **1. DSA(DIGITAL SIGNATURE ALGO):**
  - Based on the algebraic properties of the modular exponentiations, together with the discrete logarithm problem
- **2. ECDSA(ECLIPTIC CURVE DSA):** 
  - Variant of DSA which uses ECC. Suppose Alice wants to sends signed message to Bob.
```console
Step-1: Both agree on Curve parameters.(CURVE,G,n)
    CURVE: equation to be used. ECC(y2 = x3 + ax +b) Alice and bob chooses curve(y2 = x3 + 7)
    G(Base point): (x0,y0) on chosen curve (y2 = x3 + 7)
    n(Prime No): Multiplier of G. n X G = O. O is identity element.
Step-2-n: Alice calculates Key using ECC, encypts Hash of message using ECC and sends.
```
