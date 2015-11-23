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

#include <virgil/sdk/keys/io/Marshaller.h>
#include <virgil/sdk/keys/model/PublicKey.h>

#include <virgil/sdk/privatekeys/client/CredentialsExt.h>
#include <virgil/sdk/privatekeys/client/PrivateKeysClient.h>
#include <virgil/sdk/privatekeys/model/ContainerType.h>
#include <virgil/sdk/privatekeys/model/UserData.h>

using virgil::crypto::VirgilByteArray;

using virgil::sdk::keys::io::Marshaller;
using virgil::sdk::keys::model::PublicKey;

using virgil::sdk::privatekeys::client::CredentialsExt;
using virgil::sdk::privatekeys::client::PrivateKeysClient;
using virgil::sdk::privatekeys::model::ContainerType;
using virgil::sdk::privatekeys::model::UserData;

const std::string VIRGIL_PK_URL_BASE = "https://keys-private.virgilsecurity.com";
const std::string VIRGIL_APP_TOKEN = "ce7f9d8597a9bf047cb6cd349c83ef5c";
const std::string USER_EMAIL = "test.virgil-cpp@mailinator.com";
const std::string CONTAINER_PASSWORD = "123456789";

const std::string CONTAINER_NEW_PASSWORD = "987654321";


int main() {
    try {
        std::cout << "Read virgil public key..." << std::endl;
        std::ifstream publicKeyFile("virgil_public.key", std::ios::in | std::ios::binary);
        if (!publicKeyFile.good()) {
            throw std::runtime_error("can not read virgil public key: virgil_public.key");
        }
        std::string publicKeyData((std::istreambuf_iterator<char>(publicKeyFile)),
                std::istreambuf_iterator<char>());

        PublicKey publicKey = Marshaller<PublicKey>::fromJson(publicKeyData);

        std::cout << "Read private key..." << std::endl;
        std::ifstream keyFile("private.key", std::ios::in | std::ios::binary);
        if (!keyFile.good()) {
            throw std::runtime_error("can not read private key: private.key");
        }

        VirgilByteArray privateKey((std::istreambuf_iterator<char>(keyFile)),
                std::istreambuf_iterator<char>());

        CredentialsExt credentials(publicKey.publicKeyId(), privateKey);

        std::cout << "Create Private Keys Service HTTP Client." << std::endl;
        PrivateKeysClient privateKeysClient(VIRGIL_APP_TOKEN, VIRGIL_PK_URL_BASE);

        std::cout << "Authenticate session..." << std::endl;
        UserData userData = UserData::email(USER_EMAIL);
        privateKeysClient.authenticate(userData, CONTAINER_PASSWORD);

        std::cout << "Call the Private Key service to update Container instance." << std::endl;
        privateKeysClient.container().update(credentials, CONTAINER_NEW_PASSWORD);
        std::cout << "Container instance successfully update in the Private Keys service." << std::endl;
        
    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
