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

#ifndef VIRGIL_SDK_PRIVATE_KEYS_CLIENT_H
#define VIRGIL_SDK_PRIVATE_KEYS_CLIENT_H

#include <virgil/sdk/client/PrivateKeysClientBase.h>
#include <virgil/sdk/http/Response.h>


namespace virgil { namespace sdk { namespace client {
    /**
     * @brief Entrypoint for interacting with Virgil Private Keys Service PKI.
     */
    class PrivateKeysClient final : public PrivateKeysClientBase {
    public:
        PrivateKeysClient(const std::string& accessToken, const std::string& baseServiceUri);

        virgil::sdk::model::VirgilCard getServiceVirgilCard() const override;

        void setServiceVirgilCard(const virgil::sdk::model::VirgilCard& privateKeysServiceCard) override;


        void stash(const std::string& virgilCardId, const Credentials& credentials) override;

        virgil::sdk::model::PrivateKey get(const std::string& virgilCardId,
                const virgil::sdk::model::IdentityToken& identityToken) override;

        void destroy(const std::string& virgilCardId, const virgil::crypto::VirgilByteArray& publicKey,
                const Credentials& credentials) override;

    private:
        std::string accessToken_;
        std::string baseServiceUri_;
        virgil::sdk::model::VirgilCard privateKeysServiceCard_;

    private:
        void verifyResponse(const virgil::sdk::http::Response& response);
    };

}}}

#endif /* VIRGIL_SDK_PRIVATE_KEYS_CLIENT_H */