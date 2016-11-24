/**
 * Copyright (C) 2016 Virgil Security Inc.
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


#ifndef VIRGIL_SDK_CRYPTOINTERFACE_H
#define VIRGIL_SDK_CRYPTOINTERFACE_H

#include <virgil/sdk/Common.h>
#include <virgil/sdk/crypto/keys/KeyPair.h>
#include <virgil/sdk/crypto/Fingerprint.h>

using virgil::sdk::crypto::keys::PrivateKey;
using virgil::sdk::crypto::keys::PublicKey;
using virgil::sdk::crypto::keys::KeyPair;

namespace virgil {
namespace sdk {
    namespace crypto {
        class CryptoInterface {
        public:
            virtual KeyPair generateKeyPair() const = 0;
            virtual PrivateKey importPrivateKey(const VirgilByteArray &data, const std::string& password = "") const = 0;
            virtual PublicKey importPublicKey(const VirgilByteArray &data) const = 0;
            virtual PublicKey extractPublicKeyFromPrivateKey(const PrivateKey &privateKey) const = 0;
            virtual VirgilByteArray exportPrivateKey(const PrivateKey &privateKey, const std::string &password = "") const = 0;
            virtual VirgilByteArray exportPublicKey(const PublicKey &publicKey) const = 0;

            virtual VirgilByteArray encrypt(const VirgilByteArray &data, const std::vector<PublicKey> &recipients) const = 0;
            virtual void encrypt(std::istream &istream, std::ostream &ostream, const std::vector<PublicKey> &recipients) const = 0;
            virtual bool verify(const VirgilByteArray &data, const VirgilByteArray &signature, const PublicKey &signerPublicKey) const = 0;
            virtual bool verify(std::istream &istream, const VirgilByteArray &signature, const PublicKey &signerPublicKey) const = 0;
            virtual VirgilByteArray decrypt(const VirgilByteArray &data, const PrivateKey &privateKey) const = 0;
            virtual void decrypt(std::istream &istream, std::ostream &ostream, const PrivateKey &privateKey) const = 0;
            virtual VirgilByteArray signThenEncrypt(const VirgilByteArray &data, const PrivateKey &privateKey, const std::vector<PublicKey> &recipients) const = 0;
            virtual VirgilByteArray decryptThenVerify(const VirgilByteArray &data, const PrivateKey &privateKey, const PublicKey &signerPublicKey) const = 0;
            virtual VirgilByteArray generateSignature(const VirgilByteArray &data, const PrivateKey &privateKey) const = 0;
            virtual VirgilByteArray generateSignature(std::istream &istream, const PrivateKey &privateKey) const = 0;
            virtual Fingerprint calculateFingerprint(const VirgilByteArray &data) const = 0;

            virtual ~CryptoInterface(){}
        };
    }
}
}

#endif //VIRGIL_SDK_CRYPTOINTERFACE_H
