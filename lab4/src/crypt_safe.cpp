#include "crypt_safe.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

namespace cryptsafe {

CryptSafe::CryptSafe() {
    // Constructor implementation
}

CryptSafe::~CryptSafe() {
    // Destructor implementation
}

void CryptSafe::generate_key(const std::string& file_name) {
    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    rng.GenerateBlock(key, key.size());
    // Save key to file
    FileSink file(file_name.c_str());
    file.Put(key, key.size());
}

void CryptSafe::generate_keys_asymm(const std::string& private_key_path, const std::string& public_key_path) {
    using namespace CryptoPP;
    AutoSeededRandomPool rng;

    // Generate private key
    InvertibleRSAFunction privateKey;
    privateKey.Initialize(rng, 2048);
    RSA::PrivateKey rsaPrivateKey(privateKey);
    FileSink privFile(private_key_path.c_str());
    privateKey.DEREncode(privFile);

    // Generate public key
    RSA::PublicKey rsaPublicKey(rsaPrivateKey);
    FileSink pubFile(public_key_path.c_str());
    rsaPublicKey.DEREncode(pubFile);
}

void CryptSafe::encrypt_key_asymm(const std::string& file_path, const std::string& public_key_path) {
    
    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    // Load public key
    RSA::PublicKey publicKey;
    FileSource pubFile(public_key_path.c_str(), true);
    publicKey.Load(pubFile);

    // Load key
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    FileSource keyFile(file_path.c_str(), true);
    keyFile.Get(key, key.size());

    // Encrypt key
    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
    size_t encSize = encryptor.CiphertextLength(key.size());
    SecByteBlock encKey(encSize);
    encryptor.Encrypt(rng, key, key.size(), encKey);

    // Save encrypted key to file
    FileSink encFile((file_path + ".enc").c_str());
    encFile.Put(encKey, encKey.size());
} 


void CryptSafe::decrypt_key_asymm(const std::string& file_path, const std::string& private_key_path) {
    

    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    // Load private key
    RSA::PrivateKey privateKey;
    FileSource privFile(private_key_path.c_str(), true);
    privateKey.Load(privFile);

    // Load encrypted key
    SecByteBlock encKey;
    FileSource encFile(file_path.c_str(), true);
    encKey.resize(encFile.MaxRetrievable());
    encFile.Get(encKey, encKey.size());

    // Decrypt key
    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
    size_t decSize = decryptor.MaxPlaintextLength(encKey.size());
    SecByteBlock decKey(decSize);
    decryptor.Decrypt(rng, encKey, encKey.size(), decKey);
    size_t decLength=decKey.size();
    // Save decrypted key to file
    FileSink decFile((file_path + ".dec").c_str());
    decFile.Put(decKey, decLength);
}

void CryptSafe::encrypt_file_symm(const std::string& file_path, const std::string& key_path) {
    return;
}

void CryptSafe::decrypt_file_symm(const std::string& file_path, const std::string& key_path) {
    return;
} // namespace cryptsafe