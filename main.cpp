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

int main() {
    
    
    ByteArray key(KEY_SIZE);  // key
    ByteArray pt(BLOCK_SIZE); // plain text
    ByteArray sm(BLOCK_SIZE); // secret message
    ByteArray dt(BLOCK_SIZE); // decrypted text
    
    string str;
    ifstream inFile;
    ofstream outFile;
    
    /* === reading from .req file === */
    inFile.open("AES128_KAT.req");
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
    outFile.open("AES128_KAT.rsp");
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
