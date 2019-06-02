# AES128 -CFB

## Description

A C++ implementation of AES128 CFB mode.

## run

Simply run "make" to build the target with g++. 

To use the block cipher, run "./AES128" and KAT file will be generated;

To use the CFB mode, run "./AES128 cfb" and KAT file will be generated.

## KAT

Known-Answer-Tests

note: the .req files which contains key, plain text, iv, etc. should be specified beforehand.



key:
000102030405060708090a0b0c0d0e0f
initial vector:
08070605040302010099aabbccddeeff
plain text:
AES became effective as a federal government standard after approval by the Secretary of Commerce. It is the first publicly accessible cipher approved by the National Security Agency for top secret information.
secret message:
9441c1ec2bb9db9a6bf0d2cdd923d918d012f5052d4379bd859b1bd86d849ba46ea1ad56064439830ac6996e740f3449f3480d7622f0ce0d2d743fe6516e4515d2d5006e9f2961e834ebaa95444d07e80c058cb612262cdbe16fdf7da5916e61bdea24052a20ee976b0898abd7c60d70f746ccf2d605f59b389b9d6fe607636bad32b07a3d442595856a999cc138df813966c747e451892dac9720cdf71d8e3830360e68de67bde3b44d1850a4ff0f81681a29450bedf534852bf2f74526e1234a2e9ea546961151256479069c229862d1ee
decrypted text:
AES became effective as a federal government standard after approval by the Secretary of Commerce. It is the first publicly accessible cipher approved by the National Security Agency for top secret information.





