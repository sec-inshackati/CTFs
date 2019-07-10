## Secure Login (Easy - Pwn)



### Description

I found this portal on internet...

It seems that Admin privileges are required...

How can you bypass authentication?

### Compile

```bash
chmod +x compile.sh
./compile.sh
```

### Execute
```bash
chmod +x dist/SecureLogin
cd dist
./SecureLogin
```

---

#### Hints
- Have you noticed that buffer is allocated before `is_guest` variable?

#### Copyright
Rights reserved for aes.c and aes.h (https://github.com/B-Con/crypto-algorithms)
