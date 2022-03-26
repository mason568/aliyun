//sm4_x4.h
#ifndef SM4_X4_H
#define SM4_X4_H

#include"sm4.h"

/**
 * @brief SM4 4�鲢�м���
 * @param plaintext 128x4bit����
 * @param ciphertext 128x4bit����
 * @param sm4_key SM4��Կ
 */
void SM4_Encrypt_x4(uint8_t* plaintext, uint8_t* ciphertext, SM4_Key* sm4_key);


/**
 * @brief SM4 4�鲢�н���
 * @param ciphertext 128x4bit����
 * @param plaintextt 128x4bit����
 * @param sm4_key SM4 ��Կ
 */
void SM4_Decrypt_x4(uint8_t* ciphertext, uint8_t* plaintext, SM4_Key* sm4_key);
#endif
