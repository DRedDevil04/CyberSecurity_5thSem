#!/bin/bash

# Function to display the menu
display_credits() {
    clear
    echo -e "\033[1;31m$(figlet -w 500 -f cybermedium 'Certify-Me  PKI INFRASTRUCTURE')\033[0m"
    echo -e "\033[1;32m$(figlet -w 500 -f digital 'Created By:-
    Devam Desai (IIT2022035)
    Jatin Soni (IIT2022003)
    Arpit Gupta (IIT2022014)
    Sweety Solanki (IIT2022056)
    Nitu Sherawat (IIT2022073)')\033[0m"
}

display_menu() {
    # clear
    echo -e "\033[1;34m=============================\033[0m"
    echo -e "\033[1;32m   Certify-Me PKI INFRASTRUCTURE  \033[0m"
    echo -e "\033[1;34m=============================\033[0m"
    echo -e "\033[1;36m1. Generate CA Keys\033[0m"
    echo -e "\033[1;36m2. Generate User Keys\033[0m"
    echo -e "\033[1;36m3. Sign Certificate\033[0m"
    echo -e "\033[1;36m4. Verify Certificate\033[0m"
    echo -e "\033[1;36m5. Exit\033[0m"
    echo -e "\033[1;34m=============================\033[0m"
}

# Function to handle user input
read_input() {
    read -p $'\033[1;33mSelect an option [1-5]: \033[0m' choice
    case $choice in
        1) generate_ca_keys ;;
        2) generate_user_keys ;;
        3) sign_certificate ;;
        4) verify_certificate ;;
        5) exit 0 ;;
        *) echo -e "\033[1;31mInvalid option!\033[0m" ;;
    esac
}

# Function to generate CA keys
generate_ca_keys() {
    read -p $'\033[1;33mEnter the file name for CA keys (without extension): \033[0m' ca_filename
    ./app 1 "$ca_filename"
    echo -e "\033[1;32mCA keys generated successfully!\033[0m"
}

# Function to generate user keys
generate_user_keys() {
    read -p $'\033[1;33mEnter the file name for User keys (without extension): \033[0m' user_filename
    ./app 2 "$user_filename"
    echo -e "\033[1;32mUser keys generated successfully!\033[0m"
}

# Function to sign a certificate
sign_certificate() {
    read -p $'\033[1;33mEnter the path to the certificate file: \033[0m' cert_file
    read -p $'\033[1;33mEnter the path to the CA private key: \033[0m' ca_key
    read -p $'\033[1;33mEnter the notbefore (yyyy-mm-dd): \033[0m' notbefore
    read -p $'\033[1;33mEnter the notafter (yyyy-mm-dd): \033[0m' notafter
    read -p $'\033[1;33mEnter the issuer name: \033[0m' issuer
    read -p $'\033[1;33mEnter your email : \033[0m' email
    read -p $'\033[1;33mEnter your Public Key file path : \033[0m' pubkey
    ./app 3 "$cert_file" "$ca_key" "$notbefore" "$notafter" "$issuer" "$email" "$pubkey"
    echo -e "\033[1;32mCertificate signed successfully!\033[0m"
}

# Function to verify a certificate
verify_certificate() {
    read -p $'\033[1;33mEnter the path to the certificate file: \033[0m' cert_file
    read -p $'\033[1;33mEnter the path to the CA public key: \033[0m' ca_pub_key
    ./app 4 "$cert_file" "$ca_pub_key"
}

# Main loop
display_credits
while true; do
    display_menu
    read_input
    read -p $'\033[1;33mPress any key to continue...\033[0m' -n1
    clear
done
