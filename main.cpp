//
//  main.cpp
//  AES128
//
//  Created by 蔡佳仪 on 2019/5/31.
//  Copyright © 2019 CaiJY. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "aes128.hpp"
using namespace std;

void ReadHex(ifstream &fin, ByteArray &value, const int size);
void Shift(ByteArray &reg, const unsigned char ch);

int main(int argc, char* argv[]) {
    
    
    ByteArray key(KEY_SIZE);  // key
    ByteArray pt(BLOCK_SIZE); // plain text
    ByteArray sm(BLOCK_SIZE); // secret message
    ByteArray dt(BLOCK_SIZE); // decrypted text
    
    string str;
    ifstream inFile;
    ofstream outFile;
    
    // ===   AES128 block cipher   === //
    
    if(argc == 1)
    {
    // === reading from .req file === //
        
        inFile.open("KAT/AES128_KAT.req");
        if(!inFile.is_open())
        {
            cout<<"Could not open file."<<endl;
            cout<<"Programe terminating. "<<endl;
            exit(EXIT_FAILURE);
        }
        
        getline(inFile, str);
        if(str != "key:")
        {
            cout<<"Please specify encryption key."<<endl;
            exit(EXIT_FAILURE);
        }
        ReadHex(inFile, key, KEY_SIZE);
        
        getline(inFile, str);
        getline(inFile, str);
        if(str != "plain text:")
        {
            cout<<"Please specify plain text."<<endl;
            exit(EXIT_FAILURE);
        }
        ReadHex(inFile, pt, BLOCK_SIZE);
        
        /* === Encryption === */
        aes128 cipher(key);
        cipher.encrypt(pt, sm);
        
        /* === Decryption === */
        cipher.decrypt(sm, dt);
        
        /* === writing to .rsp file === */
        outFile.open("KAT/AES128_KAT.rsp");
        str = "key:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(key[i]);
            
        }
        outFile << endl;
        str = "plain text:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(pt[i]);
            
        }
        outFile << endl;
        str = "secret message:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(sm[i]);
            
        }
        outFile << endl;
        str = "decrypted text:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(dt[i]);
            
        }
        outFile << endl;
    }
    
    // ===   AES128 CFB mode   === //
    else if(argc == 2 && strcmp(argv[1], "cfb")==0)
    {
        
        ByteArray iv(BLOCK_SIZE); // initial vector
        ByteArray s_pt;
        ByteArray s_sm;
        ByteArray s_dt;
        
        unsigned char ch;
        
        inFile.open("KAT/AES128_cfb_KAT.req");
        if(!inFile.is_open())
        {
            cout<<"Could not open file."<<endl;
            cout<<"Programe terminating. "<<endl;
            exit(EXIT_FAILURE);
        }
        
        getline(inFile, str);
        if(str != "key:")
        {
            cout<<"Please specify encryption key."<<endl;
            exit(EXIT_FAILURE);
        }
        ReadHex(inFile, key, KEY_SIZE);
        
        getline(inFile, str);
        getline(inFile, str);
        if(str != "initial vector:")
        {
            cout<<"Please specify initial vector."<<endl;
            exit(EXIT_FAILURE);
        }
        ReadHex(inFile, iv, BLOCK_SIZE);
        ByteArray shift_reg(iv);
    
        getline(inFile, str);
        getline(inFile, str);
        if(str != "plain text:")
        {
            cout<<"Please specify plain text."<<endl;
            exit(EXIT_FAILURE);
        }
        // === CFB encryption === //
        aes128 cipher(key);
        
        cipher.encrypt(shift_reg, sm);
        inFile >> noskipws >> ch;
        while(inFile.good())
        {
            s_pt.push_back(ch);
            ch = ch ^ sm[0];
            Shift(shift_reg, ch);
            s_sm.push_back(ch);
            cipher.encrypt(shift_reg, sm);
            inFile >> noskipws >> ch;
        }
        
        // === CFB decryption === //
        shift_reg.clear();
        shift_reg.assign(iv.begin(), iv.end());
        for(int i=0;i<s_sm.size();i++)
        {
            cipher.encrypt(shift_reg, sm);
            ch = sm[0] ^ s_sm[i];
            s_dt.push_back(ch);
            Shift(shift_reg, s_sm[i]);
        }
        
        /* === writing to .rsp file === */
        outFile.open("KAT/AES128_cfb_KAT.rsp");
        str = "key:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(key[i]);
            
        }
        outFile << endl;
        str = "initial vector:";
        outFile << str << endl;
        for(int i=0; i<BLOCK_SIZE; i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(iv[i]);
            
        }
        outFile << endl;
        str = "plain text:";
        outFile << str << endl;
        for(int i=0; i<s_pt.size(); i++)
        {
            outFile << s_pt[i];
            
        }
        outFile << endl;
        str = "secret message:";
        outFile << str << endl;
        for(int i=0; i<s_sm.size(); i++)
        {
            outFile << hex << setfill('0') << setw(2) << int(s_sm[i]);
            
        }
        outFile << endl;
        str = "decrypted text:";
        outFile << str << endl;
        for(int i=0; i<s_dt.size(); i++)
        {
            outFile << s_dt[i];
            
        }
        outFile << endl;
    }
    // shouldn't get here //
    else
    {
        cout << "To enter cfb mode, use ./AES128 cfb" << endl;
        exit(EXIT_FAILURE);
    }
    
    
    
    inFile.close();
    outFile.close();
    
    return 0;
}

/* Read hex value from file */
void ReadHex(ifstream &fin, ByteArray &value, const int size)
{
    unsigned char t1, t2;
    
    for(int i=0; i<size; i++)
    {
        fin >> t1;
        if('0'<= t1 && '9'>=t1)
            t1 = 0 + t1 - '0';
        else if('a'<=t1 && 'f'>=t1)
            t1 = 10 + t1 - 'a';
        else if('A'<=t1 && 'F'>=t1)
            t1 = 10 + t1 - 'A';
        else
            t1 = 0; // shouldn't get here
        
        fin >> t2;
        if('0'<= t2 && '9'>=t2)
            t2 = 0 + t2 - '0';
        else if('a'<=t2 && 'f'>=t2)
            t2 = 10 + t2 - 'a';
        else if('A'<=t1 && 'F'>=t1)
            t2 = 10 + t2 - 'A';
        else
            t2 = 0; // shouldn't get here
        
        value[i] = (t1<<4)+t2;
    }
}

/* Shift Register */
void Shift(ByteArray &reg, const unsigned char ch)
{
    int i;
    for(i=0; i<reg.size()-1; i++)
        reg[i] = reg[i+1];
    reg[i] = ch;

}
