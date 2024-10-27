#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <openssl/evp.h>

void encrypt_file(const std::string& file_path, const std::string& key) {
    std::ifstream in_file(file_path, std::ios::binary);
    std::ofstream out_file(file_path + ".enc", std::ios::binary);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_chacha20(), NULL, (const unsigned char*)key.c_str(), NULL);

    std::vector<unsigned char> in_buffer(1024);
    std::vector<unsigned char> out_buffer(1024 + EVP_MAX_BLOCK_LENGTH);

    int bytes_read, bytes_written;
    while ((bytes_read = in_file.read((char*)in_buffer.data(), in_buffer.size()).gcount()) > 0) {
        EVP_EncryptUpdate(ctx, out_buffer.data(), &bytes_written, in_buffer.data(), bytes_read);
        out_file.write((char*)out_buffer.data(), bytes_written);
    }

    EVP_EncryptFinal_ex(ctx, out_buffer.data(), &bytes_written);
    out_file.write((char*)out_buffer.data(), bytes_written);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    std::string key = "unique_key_for_encryption";
    encrypt_file("test.txt", key);
    return 0;
}