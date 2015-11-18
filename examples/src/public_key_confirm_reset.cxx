/**
 * Copyright (C) 2015 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#include <virgil/crypto/VirgilByteArray.h>

#include <virgil/sdk/keys/client/Credentials.h>
#include <virgil/sdk/keys/client/KeysClient.h>
#include <virgil/sdk/keys/io/Marshaller.h>
#include <virgil/sdk/keys/model/PublicKey.h>

using virgil::crypto::VirgilByteArray;

using virgil::sdk::keys::client::Credentials;
using virgil::sdk::keys::client::KeysClient;
using virgil::sdk::keys::io::Marshaller;
using virgil::sdk::keys::model::PublicKey;

const std::string VIRGIL_PKI_URL_BASE = "https://keys.virgilsecurity.com/";
const std::string VIRGIL_APP_TOKEN = "ce7f9d8597a9bf047cb6cd349c83ef5c";


int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << std::string("USAGE: ") + argv[0] + " <action_token> <confirmation_codes>" << std::endl;
        return 0;
    }
    try {
        const std::string actionToken = argv[1];
        const std::string confirmationCodes = argv[2];

        std::cout << "Read old virgil public key..." << std::endl;
        std::ifstream oldPublicKeyFile("virgil_public.key", std::ios::in | std::ios::binary);
        if (!oldPublicKeyFile.good()) {
            throw std::runtime_error("can not read virgil public key: virgil_public.key");
        }
        std::string oldPublicKeyData((std::istreambuf_iterator<char>(oldPublicKeyFile)),
                std::istreambuf_iterator<char>());

        PublicKey oldPublicKey = Marshaller<PublicKey>::fromJson(oldPublicKeyData);

        std::cout << "Read new private key..." << std::endl;
        std::ifstream newPrivateKeyFile("private.key", std::ios::in | std::ios::binary);
        if (!newPrivateKeyFile.good()) {
            throw std::runtime_error("can not read private key: private.key");
        }
        VirgilByteArray newPrivateKey((std::istreambuf_iterator<char>(newPrivateKeyFile)),
                std::istreambuf_iterator<char>());

        Credentials newKeyCredentials(newPrivateKey);

        std::cout << "Create Keys Service HTTP Client" << std::endl;
        KeysClient keysClient(VIRGIL_APP_TOKEN, VIRGIL_PKI_URL_BASE);

        std::cout << "Call Keys service to confirm reset Public Key instance." << std::endl;
        keysClient.publicKey().confirmReset(oldPublicKey.publicKeyId(), newKeyCredentials,
                actionToken, {confirmationCodes});
        std::cout << "Public Key instance successfully confirm reset." << std::endl;
        
    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}