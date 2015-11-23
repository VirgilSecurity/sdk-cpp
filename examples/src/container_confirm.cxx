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
#include <stdexcept>
#include <string>

#include <virgil/sdk/privatekeys/client/PrivateKeysClient.h>

using virgil::sdk::privatekeys::client::PrivateKeysClient;

const std::string VIRGIL_PK_URL_BASE = "https://keys-private.virgilsecurity.com";
const std::string VIRGIL_APP_TOKEN = "ce7f9d8597a9bf047cb6cd349c83ef5c";


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << std::string("USAGE: ") + argv[0] + " <confirmation_code>" << std::endl;
        return 0;
    }

    try {
        const std::string kConfirmationToken = argv[1];
        std::cout << "Create Private Keys Service HTTP Client." << std::endl;
        PrivateKeysClient privateKeysClient(VIRGIL_APP_TOKEN, VIRGIL_PK_URL_BASE);

        std::cout << "Call the Private Key service to persist the container." << std::endl;
        privateKeysClient.container().confirm(kConfirmationToken);
        std::cout << "Container successfully persisted." << std::endl;

    } catch (std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
