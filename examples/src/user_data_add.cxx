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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <stdexcept>

#include <virgil/crypto/VirgilByteArray.h>

#include <virgil/sdk/keys/client/KeysClient.h>
#include <virgil/sdk/keys/client/CredentialsExt.h>
#include <virgil/sdk/keys/io/Marshaller.h>
#include <virgil/sdk/keys/model/PublicKey.h>
#include <virgil/sdk/keys/model/UserData.h>

using virgil::crypto::VirgilByteArray;

using virgil::sdk::keys::client::KeysClient;
using virgil::sdk::keys::client::CredentialsExt;
using virgil::sdk::keys::io::Marshaller;
using virgil::sdk::keys::model::PublicKey;
using virgil::sdk::keys::model::UserData;

const std::string VIRGIL_PKI_URL_BASE = "https://keys.virgilsecurity.com/";
const std::string VIRGIL_APP_TOKEN = "ce7f9d8597a9bf047cb6cd349c83ef5c";
const std::string NEW_USER_EMAIL = "new.cpp.virgilsecurity@mailinator.com";


int main() {
    try {
        UserData userData = UserData::email(NEW_USER_EMAIL);

        std::cout << "Read virgil public key..." << std::endl;
        std::ifstream publicKeyFile("virgil_public.key", std::ios::in | std::ios::binary);
        if (!publicKeyFile) {
            throw std::runtime_error("can not read virgil public key: virgil_public.key");
        }
        std::string publicKeyData;
        std::copy(std::istreambuf_iterator<char>(publicKeyFile), std::istreambuf_iterator<char>(),
                std::back_inserter(publicKeyData));

        PublicKey publicKey = Marshaller<PublicKey>::fromJson(publicKeyData);

        std::cout << "Read private key..." << std::endl;
        std::ifstream privateKeyFile("private.key", std::ios::in | std::ios::binary);
        if (!privateKeyFile) {
            throw std::runtime_error("can not read private key: private.key");
        }
        VirgilByteArray privateKey;
        std::copy(std::istreambuf_iterator<char>(privateKeyFile), std::istreambuf_iterator<char>(),
                std::back_inserter(privateKey));

        CredentialsExt credentialsExt(publicKey.publicKeyId(), privateKey);

        std::cout << "Append new user email (" << NEW_USER_EMAIL << ") to Public Keys on the Virgil PKI service..." << std::endl;
        KeysClient keysClient(VIRGIL_APP_TOKEN, VIRGIL_PKI_URL_BASE);

        std::cout << "Call Keys service to create User Data instance." << std::endl;
        UserData userDataResponse = keysClient.userData().add(userData, credentialsExt);
        std::cout << "User Data instance successfully created in Public Keys service." << std::endl;
        std::cout << std::endl;

        std::cout << "Added user data id: " << userDataResponse.userDataId() << std::endl;
        std::cout << "Confirmation code can be found in the email." << std::endl;
        std::cout << "Now launch next command 'user_data_confirm <user_data_id> <confirmation_code>'" << std::endl;

    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
