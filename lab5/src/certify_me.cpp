#include "certify_me.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

namespace certifyme {

CertifyMe::CertifyMe() {
    // Constructor implementation
}

CertifyMe::~CertifyMe() {
    // Destructor implementation
}

void CertifyMe::generate_CA_pub_priv_key(std::string& file_name) {
    using namespace CryptoPP;
     AutoSeededRandomPool rng;
    // Generate private key
    InvertibleRSAFunction privateKey;
    privateKey.Initialize(rng, 2048);
    RSA::PrivateKey rsaPrivateKey(privateKey);
    FileSink privFile((file_name+"_priv.key").c_str());
    privateKey.DEREncode(privFile);

    // Generate public key
    RSA::PublicKey rsaPublicKey(rsaPrivateKey);
    FileSink pubFile((file_name+"_pub.key").c_str());
    rsaPublicKey.DEREncode(pubFile);
}
void CertifyMe::generate_user_pub_priv_key(std::string& file_name) {
    using namespace CryptoPP;
     AutoSeededRandomPool rng;
    // Generate private key
    InvertibleRSAFunction privateKey;
    privateKey.Initialize(rng, 1024);
    RSA::PrivateKey rsaPrivateKey(privateKey);
    FileSink privFile((file_name+"_priv.key").c_str());
    privateKey.DEREncode(privFile);

    // Generate public key
    RSA::PublicKey rsaPublicKey(rsaPrivateKey);
    FileSink pubFile((file_name+"_pub.key").c_str());
    rsaPublicKey.DEREncode(pubFile);
}
void CertifyMe::generate_cert(const std::string& file_name) {
    
}
void CertifyMe::verify_signature(const std::string& file_path, const std::string& public_key_path) {
    
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


void CertifyMe::sign_cert(const std::string& file_path, const std::string& private_key_path) {
    

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

}