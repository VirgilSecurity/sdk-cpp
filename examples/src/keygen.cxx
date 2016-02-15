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

#include <virgil/crypto/VirgilByteArray.h>
#include <virgil/crypto/VirgilKeyPair.h>

namespace vcrypto = virgil::crypto;

const std::string PRIVATE_KEY_PASSWORD = "qwerty";

int main() {
    try {
        std::cout << "Generate keys"
                  << "\n";
        // Specify password in the constructor to make private key encrypted.
        vcrypto::VirgilKeyPair newKeyPair(vcrypto::str2bytes(PRIVATE_KEY_PASSWORD));

        std::cout << "Store public key: new_public.key ..."
                  << "\n";
        std::ofstream publicKeyStream("new_public.key", std::ios::out | std::ios::binary);
        if (!publicKeyStream) {
            throw std::runtime_error("can not write file: new_public.key");
        }
        vcrypto::VirgilByteArray publicKey = newKeyPair.publicKey();
        std::copy(publicKey.begin(), publicKey.end(), std::ostreambuf_iterator<char>(publicKeyStream));

        std::cout << "Store private key: new_private.key ..."
                  << "\n";
        std::ofstream privateKeyStream("new_private.key", std::ios::out | std::ios::binary);
        if (!privateKeyStream) {
            throw std::runtime_error("can not write file: new_private.key");
        }
        vcrypto::VirgilByteArray privateKey = newKeyPair.privateKey();
        std::copy(privateKey.begin(), privateKey.end(), std::ostreambuf_iterator<char>(privateKeyStream));

    } catch (std::exception& exception) {
        std::cerr << exception.what() << "\n";
        return 1;
    }

    return 0;
}
