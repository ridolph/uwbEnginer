// AES.h: interface for the AES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AES_H__55AEC974_E8A4_42E8_A905_D6661EB014D4__INCLUDED_)
#define AFX_AES_H__55AEC974_E8A4_42E8_A905_D6661EB014D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AES  
{
public:
	AES(unsigned char* key);
	virtual ~AES();
    void Cipher(unsigned char* input, unsigned char* out);//加密
    void InvCipher(unsigned char* input,  unsigned char* out);//解密
	
private:
	unsigned char Sbox[256];//S盒
	unsigned char InvSbox[256];//逆S盒
	unsigned char w[11][4][4];//密钥
	
	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);//密钥扩充
	unsigned char FFmul(unsigned char a, unsigned char b);//求异或
	
	void SubBytes(unsigned char state[][4]);//字节代替变换
	void ShiftRows(unsigned char state[][4]);//行移位
	void MixColumns(unsigned char state[][4]);//列混淆
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);//轮密钥加
	
	void InvSubBytes(unsigned char state[][4]);//逆字节代替
	void InvShiftRows(unsigned char state[][4]);//逆行移位
	void InvMixColumns(unsigned char state[][4]);//逆列混淆

};

int test_aes();

#endif // !defined(AFX_AES_H__55AEC974_E8A4_42E8_A905_D6661EB014D4__INCLUDED_)
