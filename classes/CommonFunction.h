#ifndef __COMMON_FUNCTION_H__
#define __COMMON_FUNCTION_H__

#include <string>

#include <openssl\evp.h>
#include <openssl\aes.h>

#define BUFSIZE 16384

std::string gen_pw(unsigned int length)
{
	unsigned int i, j;
	unsigned int nrand;
	unsigned int ns_latin, ns_glatin, ns_esc;
	std::string result;

	char s_latin[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char s_glatin[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char s_esc[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_' };

	result.resize(length);
	
	for ( auto& ch : result)
	{
		nrand = rand() % 100;

		if (nrand > 50)
		{
			ch = s_latin[rand() % sizeof(s_latin)];
		}
		else if (nrand > 20 && nrand <= 50)
		{
			ch = s_glatin[rand() % sizeof(s_glatin)];
		}
		else
		{
			ch = s_esc[rand() % sizeof(s_esc)];
		}
	}

	result[length] = '\0';

	return result;
}

void toClipBoard(const std::string& string)
{
	const size_t len = string.length() + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), string.c_str(), len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

std::string getHesh(const std::string& str)
{
	unsigned long hash = std::hash<std::string>()(str);

	char* buffer = static_cast<char*>(malloc(255));

	std::string hashStr(ultoa(hash, buffer, 255));

	free(buffer);

	for (int i = 0 ; i < hashStr.length() ; i++)
	{
		unsigned char ch = hashStr[i];
		ch = ch % 26 + 97;
		hashStr[i] = ch;
	}

	return hashStr;
}


void saveBufferToFile(void* buffer, unsigned size, const std::string& fileName, const std::string& key)
{
	int outlen;
	FILE *out = fopen((fileName + ".data").c_str(), "wb");
	if (out)
	{
		unsigned char outbuf[BUFSIZE];
		unsigned char cKey[256] = ""; /* 256-битный ключ */
		unsigned char iv[8]; /* вектор инициализации */

		memcpy(cKey, key.c_str(), key.length());

		const EVP_CIPHER * cipher;
		EVP_CIPHER_CTX ctx;
		/* обнуляем структуру контекста */
		EVP_CIPHER_CTX_init(&ctx);
		/* выбираем алгоритм шифрования */
		cipher = EVP_bf_ofb();
		/* инициализируем контекст алгоритма */
		EVP_EncryptInit(&ctx, cipher, cKey, iv);
		/* шифруем данные */

		unsigned char* cBuffer = static_cast<unsigned char*>(buffer);

		EVP_EncryptUpdate(&ctx, outbuf, &outlen, cBuffer, size);
		fwrite(outbuf, 1, outlen, out);

		EVP_EncryptFinal(&ctx, outbuf, &outlen);
		fwrite(outbuf, 1, outlen, out);
		EVP_CIPHER_CTX_cleanup(&ctx);

		fclose(out);
	}
}

void loadBufferFromFile(void** buffer, unsigned& size, std::string fileName, std::string key)
{
	size = 0;
	int inlen, outlen;
	FILE *in = fopen((fileName + ".data").c_str(), "rb");

	if (in)
	{
		*buffer = malloc(BUFSIZE);

		unsigned char inbuf[BUFSIZE], outbuf[BUFSIZE];
		unsigned char cKey[32] = ""; /* 256- битный ключ */
		unsigned char iv[8]; /* вектор инициализации */

		memcpy(cKey, key.c_str(), key.length());

		const EVP_CIPHER * cipher;
		EVP_CIPHER_CTX ctx;
		/* обнуляем структуру контекста */
		EVP_CIPHER_CTX_init(&ctx);
		/* выбираем алгоритм шифрования */
		cipher = EVP_bf_ofb();
		/* инициализируем контекст алгоритма */
		EVP_DecryptInit(&ctx, cipher, cKey, iv);
		/* шифруем данные */


		for (;;)
		{
			inlen = fread(inbuf, 1, BUFSIZE, in);
			if (inlen <= 0) break;
			EVP_DecryptUpdate(&ctx, outbuf, &outlen, inbuf, inlen);
			//fwrite(outbuf, 1, outlen, out);

			memcpy(static_cast<char*>(*buffer) + size, outbuf, outlen);
			size += outlen;
		}
		EVP_DecryptFinal(&ctx, outbuf, &outlen);
		//fwrite(outbuf, 1, outlen, out);
		memcpy(static_cast<char*>(*buffer) + size, outbuf, outlen);
		size += outlen;

		EVP_CIPHER_CTX_cleanup(&ctx);
		fclose(in);
	}
}


#endif