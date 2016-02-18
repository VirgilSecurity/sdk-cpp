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

#include <virgil/sdk/endpoints/PublicKeysEndpointUri.h>

using virgil::sdk::endpoints::PublicKeysEndpointUri;

std::string PublicKeysEndpointUri::publicKeyGet(const std::string& publicKeyId) {
    return "/v3/public-key/" + publicKeyId;
}

std::string PublicKeysEndpointUri::publicKeyRevoke(const std::string& publicKeyId) {
    return "/v3/public-key/" + publicKeyId;
}

std::string PublicKeysEndpointUri::cardCreate() {
    return "/v3/virgil-card";
}

std::string PublicKeysEndpointUri::cardGet(const std::string& cardId) {
    return "/v3/virgil-card/" + cardId;
}

std::string PublicKeysEndpointUri::cardSearch() {
    return "/v3/virgil-card/actions/search";
}

std::string PublicKeysEndpointUri::cardSearchApp() {
    return "/v3/virgil-card/actions/search/app";
}

std::string PublicKeysEndpointUri::cardSign(const std::string& cardId) {
    return "/v3/virgil-card/" + cardId + "/actions/sign";
}

std::string PublicKeysEndpointUri::cardUnsign(const std::string& cardId) {
    return "/v3/virgil-card/" + cardId + "/actions/unsign";
}

std::string PublicKeysEndpointUri::cardRevoke(const std::string& cardId) {
    return "/v3/virgil-card/" + cardId;
}
