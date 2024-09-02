#include "crypt_safe.h"
#include "../../lab5/include/certify_me.h"
#include <iostream>
#include <string>
#include "../../lab5/include/certificate.h"  // Include your certificate handling classes/headers

int main() {
    cryptsafe::CryptSafe cryptSafe;
    certifyme::CertifyMe certifyMe;
    Certificate certA;
    Certificate certB;
    // Generate a symmetric key and save it to a file
    cryptSafe.setup(1024,160);
    cryptSafe.gen_priv();
    cryptSafe.gen_pub();
    certifyMe.generate_CA_pub_priv_key("CA");

    certA.certificateSign("devamA_cert.cert","CA_priv.key","2002-12-10","2025-10-10","iiita","devamydesai@gmail.com","publicKeyA.bin");
    certA.certificateSign("devamB_cert.cert","CA_priv.key","2002-12-10","2025-10-10","iiita","nitu@gmail.com","publicKeyB.bin");

    Certificate cert_A_rec;
    Certificate cert_B_rec;

    std::string jsonDataA;
    CryptoPP::FileSource file1("devamB_cert.cert",true,new CryptoPP::StringSink(jsonDataA));
    cert_A_rec=cert_A_rec.Deserialize(jsonDataA);

    std::string jsonDataB;
    CryptoPP::FileSource file2("devamA_cert.cert",true,new CryptoPP::StringSink(jsonDataB));
    cert_B_rec=cert_B_rec.Deserialize(jsonDataB);


    if(!cert_A_rec.verify("devamB_cert.cert","CA_pub.key")){
        std::cout<<"Not Verified A"<<std::endl;
        return -1;
    }
    if(!cert_B_rec.verify("devamA_cert.cert","CA_pub.key")){
         std::cout<<"Not Verified B"<<std::endl;
         return -1;
    }
    
    std::cout<<"Verified"<<std::endl;

    cryptSafe.GenerateSharedSecretKeyB(cert_A_rec.data.publicKey,"privatekeyB.bin","KA.bin");
    cryptSafe.GenerateSharedSecretKeyA(cert_B_rec.data.publicKey,"privatekeyA.bin","KB.bin");
    
    return 0;
}