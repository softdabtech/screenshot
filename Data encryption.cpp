#include <openssl/aes.h>
#include <fstream>
#include <vector>
#include <string>

void encryptFile(const std::string& inputPath, const std::string& outputPath, const unsigned char* key) {
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream outputFile(outputPath, std::ios::binary);

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    unsigned char encryptedBuffer[buffer.size()];

    AES_KEY aesKey;
    AES_set_encrypt_key(key, 256, &aesKey);
    AES_encrypt(buffer.data(), encryptedBuffer, &aesKey);

    outputFile.write(reinterpret_cast<char*>(encryptedBuffer), buffer.size());
}