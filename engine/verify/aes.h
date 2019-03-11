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
    void Cipher(unsigned char* input, unsigned char* out);//����
    void InvCipher(unsigned char* input,  unsigned char* out);//����
	
private:
	unsigned char Sbox[256];//S��
	unsigned char InvSbox[256];//��S��
	unsigned char w[11][4][4];//��Կ
	
	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);//��Կ����
	unsigned char FFmul(unsigned char a, unsigned char b);//�����
	
	void SubBytes(unsigned char state[][4]);//�ֽڴ���任
	void ShiftRows(unsigned char state[][4]);//����λ
	void MixColumns(unsigned char state[][4]);//�л���
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);//����Կ��
	
	void InvSubBytes(unsigned char state[][4]);//���ֽڴ���
	void InvShiftRows(unsigned char state[][4]);//������λ
	void InvMixColumns(unsigned char state[][4]);//���л���

};

int test_aes();

#endif // !defined(AFX_AES_H__55AEC974_E8A4_42E8_A905_D6661EB014D4__INCLUDED_)
