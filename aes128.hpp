//
//  aes128.hpp
//  AES128
//
//  Created by 蔡佳仪 on 2019/5/31.
//  Copyright © 2019 CaiJY. All rights reserved.
//

#ifndef aes128_hpp
#define aes128_hpp

#include <stdio.h>
#include <vector>
#include <iomanip>
#endif /* aes128_hpp */

typedef std::vector<unsigned char> ByteArray;

#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NB 4
#define NR 10

class aes128
{
    public:
        aes128(const ByteArray& key);
        //~aes128();
        void encrypt(const ByteArray &pt, ByteArray &sm);
        void decrypt(const ByteArray &sm, ByteArray &pt);
    
    private:
        unsigned char m_state[4][NB];
        unsigned char m_rkey[(NR+1)*4][4];
        unsigned char m_inv_rkey[(NR+1)*4][4];
        ByteArray m_key;
    
        void AddRoundKey(const int round);
        void KeyExpansion();
        void SubBytes();
        void Shiftrows();
        void MixColumns();
    
        void InvShiftRows();
        void InvSubBytes();
        void InvMixColumns();
    
        void get_state();
    
    
    
};
