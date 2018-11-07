/**
 * Copyright (C) 2015-2018 Virgil Security Inc.
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
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 */

#ifndef VIRGIL_SDK_JWTVERIFIER_H
#define VIRGIL_SDK_JWTVERIFIER_H

#include <memory>
#include <virgil/sdk/crypto/Crypto.h>
#include <virgil/sdk/jwt/Jwt.h>

namespace virgil {
    namespace sdk {
        namespace jwt {
            /*!
             * @brief Class responsible for verification of JWTs
             */
            class JwtVerifier {
            public:
                /*!
                 * @brief Constructor
                 * @param apiPublicKey Public Key which should be used to verify signatures
                 * @param apiPublicKeyIdentifier identifier of public key which should be used to verify signatures
                 * @param crypto std::shared_ptr to Crypto instance
                 */
                JwtVerifier(crypto::keys::PublicKey apiPublicKey,
                            std::string apiPublicKeyIdentifier,
                            std::shared_ptr<crypto::Crypto> crypto);

                /*!
                 * @brief Verifies Jwt signature
                 * @param token Jwt to be verified
                 * @return true if token is verified, false otherwise
                 */
                bool verifyToken(const Jwt& token) const;

                /*!
                 * @brief Getter
                 * @return Public Key which Verifier uses to verify signatures
                 */
                const crypto::keys::PublicKey& apiPublicKey() const;

                /*!
                 * @brief Getter
                 * @return identifier of public key which Verifier uses to verify signatures
                 */
                const std::string& apiPublicKeyIdentifier() const;

                /*!
                 * @brief Getter
                 * @return std::shared_ptr to Crypto instance
                 */
                const std::shared_ptr<crypto::Crypto>& crypto() const;

            private:
                crypto::keys::PublicKey apiPublicKey_;
                std::string apiPublicKeyIdentifier_;
                std::shared_ptr<crypto::Crypto> crypto_;
            };
        }
    }
}

#endif //VIRGIL_SDK_JWTVERIFIER_H