# Installation

Unix install instructions:

    git clone https://github.com/nicoaw/rsa.git
    cd rsa
    cmake src/
    make
    sudo make install

# Description

rsa is a small command-line program to encrypt and decrypt files using the RSA algorithm. It should work on all major platforms (Linux, Mac, and Windows).

    rsa [options]

# Options

    -d [ --decrypt ] arg  specifies the input file for decryption
    -e [ --encrypt ] arg  specifies the input file for encryption
    -h [ --help ]         produce help messages
    -k [ --key ] arg      specifies the key file
    -o [ --output ] arg   specify the output file

# Usage

PRIVATEKEYFILE must be of the format: `p q e` where `p, q, and e` are primes.
PUBLICKEYFILE must be of the format: `n e` where `n=p*q` and `e` is prime.
INPUTFILE can contain any text.

To encrypt a file type:

    rsa -k PUBLICKEYFILE -e INPUTFILE


To decrypt a file type:

    rsa -k PRIVATEKEYFILE -d INPUTFILE

# Example

    cat plain.txt
    Hello, World! 1234
    
    cat public_key.txt
    519920270270461174069 22801760557
    
    rsa -k public_key.txt -e plain.txt -o cypher.txt
    
    cat cypher.txt
    447910219675640659069 209490328261467208463 133689882439015810412 133689882439015810412 302625408265942438770 139739471252456673482 515002159753950190017 53759273218032910532 302625408265942438770 423744606139235176051 133689882439015810412 320253366732901807900 509173901502128805409 515002159753950190017 122606388417236079863 443242243700101472134 457127956542821683965 80080169254082940269 191434783268805632588
    
    cat private_key.txt
    22801761379 22801759111 22801760557
    
    rsa -k private_key.txt -d cypher.txt -o decrypted.txt
    
    cat decrypted.txt
    Hello, World! 1234
