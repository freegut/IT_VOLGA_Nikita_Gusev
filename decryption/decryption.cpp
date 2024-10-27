#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <openssl/evp.h>

void decrypt_file(const std::string& file_path, const std::string& key) {
    std::ifstream in_file(file_path, std::ios::binary);
    std::ofstream out_file(file_path.substr(0, file_path.size() - 4), std::ios::binary);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_chacha20(), NULL, (const unsigned char*)key.c_str(), NULL);

    std::vector<unsigned char> in_buffer(1024);
    std::vector<unsigned char> out_buffer(1024 + EVP_MAX_BLOCK_LENGTH);

    int bytes_read, bytes_written;
    while ((bytes_read = in_file.read((char*)in_buffer.data(), in_buffer.size()).gcount()) > 0) {
        EVP_DecryptUpdate(ctx, out_buffer.data(), &bytes_written, in_buffer.data(), bytes_read);
        out_file.write((char*)out_buffer.data(), bytes_written);
    }

    EVP_DecryptFinal_ex(ctx, out_buffer.data(), &bytes_written);
    out_file.write((char*)out_buffer.data(), bytes_written);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    std::string key = "unique_key_for_encryption";
    decrypt_file("test.txt.enc", key);
    return 0;
}