#include "certificate.h"
#include "certify_me.h"
#include <iostream>

int main() {
    certifyme::CertifyMe certifyMe;
    Certificate cert;
    // Generate a symmetric key and save it to a file
    certifyMe.generate_CA_pub_priv_key("CA");
    certifyMe.generate_CA_pub_priv_key("Fake_CA");
    certifyMe.generate_user_pub_priv_key("devam");

    cert.SetIssuerDistinguishedName("iiita");
    cert.SetSubjectDistinguishedName("devamydesai@gmail.com");
    
    cert.certificateSign("devam.cert","CA_priv.key");
    if(cert.verify("devam.cert","Fake_CA_pub.key")){
        std::cout<<"YES"<<std::endl;
    }
    else std::cout<<"NO"<<std::endl;
    std::cout << "PKI Exited" << std::endl;

    return 0;
}