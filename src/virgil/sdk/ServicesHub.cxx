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
#include <vector>

#include <virgil/crypto/VirgilByteArray.h>

#include <virgil/sdk/ServicesHub.h>
#include <virgil/sdk/client/IdentityClient.h>
#include <virgil/sdk/client/PrivateKeysClient.h>
#include <virgil/sdk/client/PublicKeysClient.h>
#include <virgil/sdk/client/CardsClient.h>
#include <virgil/sdk/ServiceUri.h>

using virgil::crypto::VirgilByteArray;

using virgil::sdk::ServicesHub;
using virgil::sdk::client::IdentityClient;
using virgil::sdk::client::PrivateKeysClient;
using virgil::sdk::client::PublicKeysClient;
using virgil::sdk::client::CardsClient;
using virgil::sdk::model::Card;
using virgil::sdk::ServiceUri;

const std::string kIdentityServiceApplicationId = "com.virgilsecurity.identity";
const std::string kPublicKeyServiceApplicationId = "com.virgilsecurity.keys";
const std::string kPrivateKeyServiceApplicationId = "com.virgilsecurity.private-keys";

namespace virgil {
namespace sdk {
    class ServicesHubImpl {
    public:
        explicit ServicesHubImpl(const std::string& accessToken, const ServiceUri& baseServiceUri)
                : identityClient(accessToken, baseServiceUri.getIdentityService()),
                  publicKeysClient(accessToken, baseServiceUri.getPublicKeyService()),
                  cardsClient(accessToken, baseServiceUri.getPublicKeyService()),
                  privateKeysClient(accessToken, baseServiceUri.getPrivateKeyService()) {
        }

    public:
        IdentityClient identityClient;
        PublicKeysClient publicKeysClient;
        CardsClient cardsClient;
        PrivateKeysClient privateKeysClient;
    };
}
}

ServicesHub::ServicesHub(const std::string& accessToken, const ServiceUri& baseServiceUri)
        : accessToken_(accessToken),
          virgilUri_(baseServiceUri),
          impl_(std::make_shared<virgil::sdk::ServicesHubImpl>(accessToken_, virgilUri_)) {
}

IdentityClient& ServicesHub::identity() {
    return impl_->identityClient;
}

PrivateKeysClient& ServicesHub::privateKeys() {
    return impl_->privateKeysClient;
}

PublicKeysClient& ServicesHub::publicKeys() {
    return impl_->publicKeysClient;
}

CardsClient& ServicesHub::cards() {
    return impl_->cardsClient;
}

void ServicesHub::loadServicesCard() {
    auto identityServiceCards = impl_->cardsClient.getServiceCard(kIdentityServiceApplicationId);
    auto publicKeysServiceCards = impl_->cardsClient.getServiceCard(kPublicKeyServiceApplicationId);
    auto privateKeysServiceCards = impl_->cardsClient.getServiceCard(kPrivateKeyServiceApplicationId);

    auto identityServiceCard = identityServiceCards.at(0);
    auto publicKeysServiceCard = publicKeysServiceCards.at(0);
    auto privateKeysServiceCard = privateKeysServiceCards.at(0);

    impl_->identityClient.setServiceCard(identityServiceCard);
    impl_->publicKeysClient.setServiceCard(publicKeysServiceCard);
    impl_->cardsClient.setServiceCard(publicKeysServiceCard);
    impl_->privateKeysClient.setServiceCard(privateKeysServiceCard);
}
