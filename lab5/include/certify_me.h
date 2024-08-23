#ifndef CERTIFY_ME_H
#define CERTIFY_ME_H

// Include necessary libraries
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

// Namespace declaration if needed
namespace certifyme {

// Class declaration
class CertifyMe {
public:
    // Constructor
    CertifyMe();

    // Destructor
    ~CertifyMe();

    // Member functions
    void generate_CA_pub_priv_key(std::string& file_name);
    void generate_user_pub_priv_key(std::string& file_name);
    void generate_cert(const std::string& file_name);
    void sign_cert(const std::string& file_name,const std::string& priv_key_CA);
    void verify_signature(const std::string& file_name, const std::string& pub_key_CA);
};

} // namespace cryptsafe

#endif // CRYPT_SAFE_H