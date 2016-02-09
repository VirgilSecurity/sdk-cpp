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

#include <json.hpp>

#include <virgil/sdk/io/Marshaller.h>
#include <virgil/sdk/util/JsonKey.h>
#include <virgil/sdk/model/IdentityToken.h>

#include <virgil/crypto/foundation/VirgilBase64.h>

using json = nlohmann::json;

using virgil::sdk::util::JsonKey;
using virgil::sdk::model::IdentityToken;
using virgil::sdk::model::IdentityType;
using virgil::sdk::model::Identity;

using virgil::crypto::foundation::VirgilBase64;


namespace virgil { namespace sdk { namespace io {
    /**
     * @brief Marshaller<IdentityToken> specialization.
     */
    template <>
    class Marshaller<IdentityToken> {
    public:
        template <int INDENT = -1>
        static std::string toJson(const IdentityToken& identityToken) {
            json jsonIdentityToken = {
                { JsonKey::type, identityToken.getIdentity().getTypeAsString() },
                { JsonKey::value, identityToken.getIdentity().getValue() },
                { JsonKey::validationToken, identityToken.getValidationToken() }
            };

            return jsonIdentityToken.dump(INDENT);
        }

        static IdentityToken fromJson(const std::string& jsonString) {
            json typeJson = json::parse(jsonString);

            std::string typeStr = typeJson[JsonKey::type];
            IdentityType identityType = virgil::sdk::model::fromString(typeStr);
            std::string value = typeJson[JsonKey::value];     
            std::string validationToken = typeJson[JsonKey::validationToken];
            Identity identity(value, identityType);

            return IdentityToken(identity, validationToken);
        }

    private:
        Marshaller() {};
    };
}}}

void marshaller_identity_token_init() {
    virgil::sdk::io::Marshaller<IdentityToken>::toJson(IdentityToken());
    virgil::sdk::io::Marshaller<IdentityToken>::toJson<2>(IdentityToken());
    virgil::sdk::io::Marshaller<IdentityToken>::toJson<4>(IdentityToken());
    virgil::sdk::io::Marshaller<IdentityToken>::fromJson("");
}