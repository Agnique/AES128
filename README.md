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
9420d4d5a8c4eedd4b68024d454e2cada56be094c182c35002a93eb458600ba83827c38f86436cd97d084308ddc60b8b33b8ec7fa35f5af66f6dcbc830205bfbbea7e999ab4d2e466d14a32148feabbf5e7f82547867ae974f2e4616c585e5dde9a86fafad614ac52d22e68d69a8b4c8f68dfdd5906b008b3a6632d4e2d924963aa5a9b4a0642a8031154957d4e83ed6f9ce6aba1c4ccf99712a0251573416a050dc32c1b8ecd01b6f6ff62eca1159113fc94fdc3837495c652a9b6feb40301fb1c7d9357e807130f065cf4b3207033dca6f75c50e73340cd243839b4e79cdb0
decrypted text:
AES became effective as a federal government standard after approval by the Secretary of Commerce. It is the first publicly accessible cipher approved by the National Security Agency for top secret information.





