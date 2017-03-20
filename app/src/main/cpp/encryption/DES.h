//////////////////////////////////////////////////////////////////////////  
/* 
    Provided by 朱孟斌, National University Of Technology 
    Email: zmb.tsubasa@gmail.com 
    This product is free for use. 
*/
//////////////////////////////////////////////////////////////////////////  
#ifndef Des_H
#define Des_H

//! enum    bool{false,true};   
/*!   
if bool is not supported,use this or just replace with char and use 1 for true,0 for false; 
@see enum    {ENCRYPT,DECRYPT}; 
*/
enum {
    ENCRYPT, DECRYPT
};
/*@brief  16圈子密钥*/
static bool SubKey[2][16][48];// 16圈子密钥  
/*@brief 3次DES标志*/
static bool Is3DES;// 3次DES标志  
static char Tmp[256];
static char deskey[16];
typedef bool    (*PSubKey)[16][48];

class Des {
public:
    Des();

    ~Des();
    //! Type—ENCRYPT:加密,DECRYPT:解密  
    /*!  
    输出缓冲区(Out)的长度 >= ((datalen+7)/8)*8,即比datalen大的且是8的倍数的最小正整数 
    In 可以= Out,此时加/解密后将覆盖输入缓冲区(In)的内容 
    当keylen>8时系统自动使用3次DES加/解密,否则使用标准DES加/解密.超过16字节后只取前16字节 
    @see bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT); 
    */

    bool
    Des_Go(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type = ENCRYPT);

private:
    /*! @brief 标准DES加/解密 
    @see static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type); 
    */
    static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);//标准DES加/解密  
    /*! @brief 设置密钥 
    @see static void SetKey(const char* Key, int len); 
    */
    static void SetKey(const char *Key, int len);// 设置密钥
    /*! @brief 设置子密钥 
    @see static void SetSubKey(PSubKey pSubKey, const char Key[8]); 
    */
    static void SetSubKey(PSubKey pSubKey, const char Key[8]);// 设置子密钥  
    /*! @brief f 函数 
    @see static void F_func(bool In[32], const bool Ki[48]); 
    */
    static void F_func(bool In[32], const bool Ki[48]);// f 函数  
    /*! @brief S 盒代替 
    @see static void S_func(bool Out[32], const bool In[48]); 
    */
    static void S_func(bool Out[32], const bool In[48]);// S 盒代替  
    /*! @brief 变换 
    @see static void Transform(bool *Out, bool *In, const char *Table, int len); 
    */
    static void Transform(bool *Out, bool *In, const char *Table, int len);// 变换  
    /*! @brief 异或 
    @see static void Xor(bool *InA, const bool *InB, int len); 
    */
    static void Xor(bool *InA, const bool *InB, int len);// 异或  
    /*! @brief 循环左移 
    @see static void RotateL(bool *In, int len, int loop); 
    */
    static void RotateL(bool *In, int len, int loop);// 循环左移  
    /*! @brief 字节组转换成位组 
    @see static void ByteToBit(bool *Out, const char *In, int bits); 
    */
    static void ByteToBit(bool *Out, const char *In, int bits);// 字节组转换成位组  
    /*! @brief 位组转换成字节组 
    @see static void BitToByte(char *Out, const bool *In, int bits); 
    */
    static void BitToByte(char *Out, const bool *In, int bits);// 位组转换成字节组  

};
//////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////  
#endif  