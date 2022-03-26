//sm4_x4.h
#ifndef SM4_X4_H
#define SM4_X4_H

#include"sm4.h"

/**
 * @brief SM4 4组并行加密
 * @param plaintext 128x4bit明文
 * @param ciphertext 128x4bit密文
 * @param sm4_key SM4密钥
 */
void SM4_Encrypt_x4(uint8_t* plaintext, uint8_t* ciphertext, SM4_Key* sm4_key);


/**
 * @brief SM4 4组并行解密
 * @param ciphertext 128x4bit密文
 * @param plaintextt 128x4bit明文
 * @param sm4_key SM4 密钥
 */
void SM4_Decrypt_x4(uint8_t* ciphertext, uint8_t* plaintext, SM4_Key* sm4_key);
#endif
