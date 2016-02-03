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

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

#include <virgil/sdk/VirgilHub.h>
#include <virgil/sdk/VirgilUri.h>

using virgil::crypto::VirgilByteArray;

using virgil::sdk::VirgilHub;
using virgil::sdk::VirgilUri;
using virgil::sdk::model::VirgilCard;

const std::string VIRGIL_ACCESS_TOKEN = 
        "eyJpZCI6IjIxMDk4ZjhlLWFjMzQtNGFkYy04YTBmLWFkZmM1YzBhNWE0OSIsImFwcGxpY2"
        "F0aW9uX2NhcmRfaWQiOiI2OWRlYzc1MC1hMDNmLTRmNmYtYTJlYi1iNTE2MzJkZmE3MTIiL"
        "CJ0dGwiOi0xLCJjdGwiOi0xLCJwcm9sb25nIjowfQ==.MIGaMA0GCWCGSAFlAwQCAgUABIGI"
        "MIGFAkEAhc7LGcy2qyRBJLsZu1Casdr6pcoub/pR3j1SB4E0HFx+XlfPqE9xIViG/Em3l+y2"
        "EkFvvjbSWdaMkHroO+UmOQJAMMEZB7rAynJuUog8ZbxabsYZ5TUtnOfRCIdkjYq+26BDIA7d"
        "n9lSE1s8TstZHP9f/ICmc2SMgAV7okyyomm5uQ==";


const std::string VIRGIL_IDENTITY_SERVICE_URI_BASE = "https://identity-stg.virgilsecurity.com";
const std::string VIRGIL_PUBLIC_KEYS_SERVICE_URI_BASE = "https://keys-stg.virgilsecurity.com";
const std::string VIRGIL_PRIVATE_KEYS_SERVICE_URI_BASE = "https://private-stg.virgilsecurity.com";

const std::string kIdentityServiceApplicationId = "com.virgilsecurity.identity";
const std::string kPublicKeyServiceApplicationId = "com.virgilsecurity.keys";
const std::string kPrivateKeyServiceApplicationId = "com.virgilsecurity.private-keys";


int main() {
    try {
        VirgilUri virgilUri(
				VIRGIL_IDENTITY_SERVICE_URI_BASE,
				VIRGIL_PUBLIC_KEYS_SERVICE_URI_BASE,
       			VIRGIL_PRIVATE_KEYS_SERVICE_URI_BASE
        );

        VirgilHub virgilHub(VIRGIL_ACCESS_TOKEN, virgilUri);
        auto identityServiceVirgilCards = virgilHub.cards().getServiceCard(kIdentityServiceApplicationId);
        auto publicKeysServiceVirgilCards = virgilHub.cards().getServiceCard(kPublicKeyServiceApplicationId);
        auto privateKeysServiceVirgilCards = virgilHub.cards().getServiceCard(kPrivateKeyServiceApplicationId);

        VirgilByteArray identityServicePublicKey = identityServiceVirgilCards.at(0).getPublicKey().getKey();
        VirgilByteArray publicKeysServicePublicKey = publicKeysServiceVirgilCards.at(0).getPublicKey().getKey();
        VirgilByteArray privateKeysServicePublicKey = privateKeysServiceVirgilCards.at(0).getPublicKey().getKey();

        virgilHub.identity().setServicePublicKey(identityServicePublicKey);
        virgilHub.publicKeys().setServicePublicKey(publicKeysServicePublicKey);
        virgilHub.cards().setServicePublicKey(publicKeysServicePublicKey);
        virgilHub.privateKeys().setServicePublicKey(privateKeysServicePublicKey);

    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
