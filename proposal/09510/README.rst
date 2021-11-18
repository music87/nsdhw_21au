========================
Encryption Acceleration 
========================


Basic Information
========================
Code repository: https://github.com/09510/Encryption-Acceleration

Problem to solve
=======================
Message encryption is an important technology to protect information security. 
However, if you want to ensure the encryption strength, the encryption/decryption takes a lot of time.
Encryption Acceleration is a tool to accelerate encryption and decryption by GPU. 



Perspective users 
=========================
Anyone who wants to use GPU to accelerate encryption and decryption.


 
System architecture 
=============================
1. Calling encrypt/decrypt function by Python.
2. Doing encrypt/decrypt by gpu.
3. Return encrypted/decrypted msg. 
    


API description 
================================
Python API : 
    1. encrypt(input_file ,algo ,seed) : Return key, and encrypted file.
    2. decrypt(encrypted_file, algo, key) : Return decrypted file.
- input_file : The file you want to encrypt.
- algo : setting encrypt/decrypt algo. For example: DES.
- seed : the seed used to generate random key.


 
Engineering infrastructure 
=================================

-Build System : 
    Make
-Version Control : 
    Git
-Test : 
    C+++ : Google Tesr
    
    Python : pytest

Schedule 
====================================
- Week 1: Implement algo. part on C++
- Week 2: implement cuda part on C++
- Week 3: implement cuda part on C++
- Week 4: implement cuda part on C++
- Week 5: Integrate the c++ and python code
- Week 6: Test the system
- Week 7: Prepare presentation
- Week 8: Prepare presentation
