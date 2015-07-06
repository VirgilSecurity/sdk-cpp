/**
 * Copyright (C) 2014 Virgil Security Inc.
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

#include <cstddef>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdexcept>

#include <virgil/crypto/VirgilByteArray.h>
using virgil::crypto::VirgilByteArray;
#include <virgil/crypto/VirgilStreamCipher.h>
using virgil::crypto::VirgilStreamCipher;

#include <virgil/crypto/stream/VirgilStreamDataSource.h>
using virgil::crypto::stream::VirgilStreamDataSource;
#include <virgil/crypto/stream/VirgilStreamDataSink.h>
using virgil::crypto::stream::VirgilStreamDataSink;

#include <virgil/crypto/foundation/VirgilBase64.h>
using virgil::crypto::foundation::VirgilBase64;

#include <virgil/sdk/keys/model/PublicKey.h>
using virgil::sdk::keys::model::PublicKey;
#include <virgil/sdk/keys/model/UserDataType.h>
using virgil::sdk::keys::model::UserDataType;

#include <virgil/sdk/keys/http/Connection.h>
using virgil::sdk::keys::http::Connection;
#include <virgil/sdk/keys/client/KeysClient.h>
using virgil::sdk::keys::client::KeysClient;

static const std::string VIRGIL_PKI_URL_BASE = "https://keys.virgilsecurity.com/v1/";
static const std::string VIRGIL_PKI_APP_TOKEN = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
static const std::string USER_EMAIL = "test.virgilsecurity@mailinator.com";

#define MAKE_URL(base, path) (base path)

int main() {
    try {
        std::cout << "Prepare input file: test.txt..." << std::endl;
        std::ifstream inFile("test.txt", std::ios::in | std::ios::binary);
        if (!inFile.good()) {
            throw std::runtime_error("can not read file: test.txt");
        }

        std::cout << "Prepare output file: test.txt.enc..." << std::endl;
        std::ofstream outFile("test.txt.enc", std::ios::out | std::ios::binary);
        if (!outFile.good()) {
            throw std::runtime_error("can not write file: test.txt.enc");
        }

        std::cout << "Initialize cipher..." << std::endl;
        VirgilStreamCipher cipher;

        std::cout << "Get recipient ("<< USER_EMAIL << ") information from the Virgil PKI service..." << std::endl;
        KeysClient keysClient(std::make_shared<Connection>(VIRGIL_PKI_APP_TOKEN, VIRGIL_PKI_URL_BASE));
        std::vector<PublicKey> publicKeys = keysClient.publicKey().search(USER_EMAIL, UserDataType::emailId);
        if (publicKeys.empty()) {
            throw std::runtime_error(std::string("Recipient with id: ") + USER_EMAIL + " not found.");
        }
        std::cout << "Add recipient..." << std::endl;
        PublicKey publicKey = publicKeys.front();
        cipher.addKeyRecipient(virgil::crypto::str2bytes(publicKey.publicKeyId()), publicKey.key());

        std::cout << "Encrypt and store results..." << std::endl;
        VirgilStreamDataSource dataSource(inFile);
        VirgilStreamDataSink dataSink(outFile);
        cipher.encrypt(dataSource, dataSink, true);

        std::cout << "Encrypted data is successfully stored in the output file..." << std::endl;
    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
    }
    return 0;
}
