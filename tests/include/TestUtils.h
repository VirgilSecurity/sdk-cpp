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


#ifndef VIRGIL_SDK_TESTUTILS_H
#define VIRGIL_SDK_TESTUTILS_H

#include <memory>
#include <string>
#include <ctime>
#include <virgil/sdk/jwt/Jwt.h>
#include <virgil/sdk/crypto/Crypto.h>
#include <virgil/sdk/cards/Card.h>

#include <TestConst.h>
#include <virgil/sdk/client/models/RawCardContent.h>

using virgil::sdk::crypto::Crypto;
using virgil::sdk::test::TestConst;

namespace virgil {
namespace sdk {
    namespace test {
        class TestUtils {
        public:
            TestUtils(TestConst consts) : consts(std::move(consts)), crypto_(std::make_shared<Crypto>()) {}

            jwt::Jwt getToken(const std::string& identity, int ttl = 1000) const;

            jwt::Jwt getTokenWithWrongPrivateKey(const std::string& identity, int ttl = 1000) const;

            bool isCardsEqual(const cards::Card& card1, const cards::Card& card2) const;

            bool isRawCardContentEqual(const client::models::RawCardContent& content1,
                                       const client::models::RawCardContent& content2) const;

            bool isRawSignaturesEqual(const std::vector<client::models::RawSignature>& signatures1,
                                      const std::vector<client::models::RawSignature>& signatures2) const;

            bool isCardSignaturesEqual(const std::vector<cards::CardSignature>& signatures1,
                                       const std::vector<cards::CardSignature>& signatures2) const;

            VirgilByteArray getRandomBytes(int size = 10) const;

            std::string getRandomString(int size = 10) const;

            const std::shared_ptr<Crypto>& crypto() const;

        private:
            const std::shared_ptr<Crypto> crypto_;
            TestConst consts;
        };
    }
}
}

#endif //VIRGIL_SDK_TESTUTILS_H
