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
#include <stdexcept>
#include <string>

#include <virgil/sdk/VirgilHub.h>
#include <virgil/sdk/VirgilUri.h>

namespace vsdk = virgil::sdk;
namespace vcrypto = virgil::crypto;

const std::string VIRGIL_ACCESS_TOKEN = "eyJpZCI6IjFkNzgzNTA1LTk1NGMtNDJhZC1hZThjLWQyOGFiYmN"
        "hMGM1NyIsImFwcGxpY2F0aW9uX2NhcmRfaWQiOiIwNGYyY2Y2NS1iZDY2LTQ3N2EtOGFiZi1hMDAyYWY4Yj"
        "dmZWYiLCJ0dGwiOi0xLCJjdGwiOi0xLCJwcm9sb25nIjowfQ==.MIGZMA0GCWCGSAFlAwQCAgUABIGHMIGE"
        "AkAV1PHR3JaDsZBCl+6r/N5R5dATW9tcS4c44SwNeTQkHfEAlNboLpBBAwUtGhQbadRd4N4gxgm31sajEOJ"
        "IYiGIAkADCz+MncOO74UVEEot5NEaCtvWT7fIW9WaF6JdH47Z7kTp0gAnq67cPbS0NDUyovAqILjmOmg1zA"
        "L8A4+ii+zd";

const std::string PRIVATE_KEY_PASSWORD = "qwerty";


int main(int argc, char **argv) {
    if (argc < 5) {
        std::cerr << std::string("USAGE: ") + argv[0]
                + " <user_email>"
                + " <owner_card_id>"
                + " <validation_token>"
                + " <path_private_key>"
                 << "\n";
        return 1;
    }

    try {
        std::string userEmail = argv[1];
        std::string ownerCardId = argv[2];
        std::string token = argv[3];
        std::string pathPrivateKey = argv[4];

        vsdk::VirgilHub virgilHub(VIRGIL_ACCESS_TOKEN);
        virgilHub.loadServicePublicKeys();

        vsdk::model::Identity identity(userEmail, vsdk::model::IdentityType::Email);
        vsdk::model::ValidationToken validationToken(identity, token);

        std::cout << "Prepare private key file: " << pathPrivateKey << "\n";
        std::cout << "Read private key..." << "\n";
        std::ifstream inPrivateKeyFile(pathPrivateKey, std::ios::in | std::ios::binary);
        if (!inPrivateKeyFile) {
            throw std::runtime_error("can not read private key: " + pathPrivateKey);
        }
        vcrypto::VirgilByteArray privateKey;
        std::copy(std::istreambuf_iterator<char>(inPrivateKeyFile), std::istreambuf_iterator<char>(),
                std::back_inserter(privateKey));

        vsdk::Credentials credentials(privateKey, PRIVATE_KEY_PASSWORD);

        std::cout << "Revoke a Virgil Card" << "\n";
        virgilHub.cards().revoke(ownerCardId, validationToken, credentials);

    } catch (std::exception& exception) {
        std::cerr << exception.what() << "\n";
        return 1;
    }

    return 0;
}
