// sm4.h
#ifndef SM4_H
#define SM4_H

#include <stdint.h>

/**
 * @brief SM4 ��Կ
 */
typedef struct _SM4_Key {
    uint32_t rk[32];//32����Կ
} SM4_Key;

/**
 * @brief ��ʼ�� SM4 ����Կ
 * @param key 128bit������Կ
 * @param sm4_key SM4 ��Կ
 */
void SM4_KeyInit(uint8_t* key, SM4_Key* sm4_key);

#endif
