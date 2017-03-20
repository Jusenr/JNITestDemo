//! SHA1 动态链接库实现   H文件  
/*！ 
 @author 朱孟斌 
 @e-mail  zmb.tsubasa@gmail.com 
 @version 1.0 
 @date 2011-03
*/
#ifndef SHA1_H
#define SHA1_H

#include "stdint.h"  
//! #定义SHA 中的返回ENUM  
/*！ 
   @see enum 
*/
#ifndef _SHA_enum_
#define _SHA_enum_
enum {
    shaSuccess = 0,
    /*! <空指示参量 */
            shaNull,
    /*! < 输入数据太长提示 */
            shaInputTooLong,
    /*! <called Input after Result --以输入结果命名之 */
            shaStateError
};
#endif
//! SHA1HashSize定义的是SHA1哈希表的大小  
#define SHA1HashSize 20
//!   #能够进行动态链接库编译的SHA1类  
/*!
      @see class _declspec(dllexport) SHA_1
      将SHA1算法写成动态链接库的形式方便调用，生成消息使用
*/
class SHA_1 {
public:
    //! #定义数据结构控制上下文消息 SHA1Context  
    /*! 
        以下这种结构将会控制上下文消息 for the SHA-1 
        hashing operation 
        @see struct SHA1Context 
    */
    typedef struct SHA1Context {
        uint32_t Intermediate_Hash[SHA1HashSize / 4]; /*! <Message Digest  */

        uint32_t Length_Low;            /*! <Message length in bits      */
        uint32_t Length_High;           /*! <Message length in bits      */

        /*! <Index into message block array   */
        int_least16_t Message_Block_Index;
        uint8_t Message_Block[64];      /*! <512-bit message blocks      */

        int Computed;               /*! <Is the digest computed?         */
        int Corrupted;             /*! <Is the message digest corrupted? */
    } SHA1Context;

public:
    //! #SHA_1 的构造函数  
    /*! 
     @see SHA_1() 
      其中应该对SHA_1类中的一些变量进行相应的初始化 
    */
    SHA_1();
    //! #SHA_1的析构函数  
    /*! 
    @see ~SHA_1() 
      释放内存 
    */
    ~SHA_1(void);

    /*----------------------------------函数原型----------------------------------*/
    //! #SHA1算法中的数据填充模块  
    /*! 
      @see void SHA1PadMessage(SHA1Context *); 
      @param[SHA1Context*  定义填充信息指针]
      @return[void] 不返回任何值 
    */
    void SHA1PadMessage(SHA1Context *);    /*  定义填充信息指针  */
    //! #SHA1的消息块描述函数  
    /*! 
      @see void SHA1ProcessMessageBlock(SHA1Context *); 
      @param[SHA1Context*  定义填充信息指针]
      @param[in] 消息块长度为固定之512比特 
      @return[void] 不返回任何值 
    */
    void SHA1ProcessMessageBlock(SHA1Context *);
    //! #SHA1的数据初始化操作函数  
    /*! 
      @see int SHA1Reset(  SHA1Context *); 
      @param[SHA1Context*  定义填充信息指针]
      @return[int] 成功返回shaSuccess，失败返回shaNull
      @see SHA1 enum 
    */
    int SHA1Reset(SHA1Context *);
    //! #SHA1的输入描述函数  
    /*! 
      @see int SHA1Input(  SHA1Context *, const uint8_t *, unsigned int); 
      @param[SHA1Context*  定义填充信息指针]
      @param[uint8_t 接收单位长度为8字节倍数的消息]
      @return[enum] 成功返回shaSuccess，失败返回shaNull，错误返回shaStateError
      @see SHA1 enum 
    */
    int SHA1Input(SHA1Context *, const uint8_t *, unsigned int);
    //! #SHA1的结果描述函数  
    /*! 
      @see int SHA1Result( SHA1Context *, uint8_t Message_Digest[SHA1HashSize]); 
      @param[SHA1Context*  定义填充信息指针]
      @param[uint8_t 160比特的消息摘要队列]
      @attention 返回一个160比特的消息摘要队列 
      @return[enum] 成功返回shaSuccess，失败返回shaNull，错误返回shaStateError
      @see SHA1 enum 
    */
    int SHA1Result(SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);

private:
};

#endif // SHA1_H  