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

#include <virgil/sdk/ServiceUri.h>

using virgil::sdk::ServiceUri;

#if defined(VIRGIL_IDENTITY_SERVICE_URI)
const std::string ServiceUri::kIdentityServiceUri = VIRGIL_IDENTITY_SERVICE_URI;
#else
const std::string ServiceUri::kIdentityServiceUri = "https://identity.virgilsecurity.com";
#endif

#if defined(VIRGIL_KEYS_SERVICE_URI)
const std::string ServiceUri::kKeysServiceUri = VIRGIL_KEYS_SERVICE_URI;
#else
const std::string ServiceUri::kKeysServiceUri = "https://keys.virgilsecurity.com";
#endif

#if defined(VIRGIL_PRIVATE_KEYS_SERVICE_URI)
const std::string ServiceUri::kPrivateKeyServiceUri = VIRGIL_PRIVATE_KEYS_SERVICE_URI;
#else
const std::string ServiceUri::kPrivateKeyServiceUri = "https://keys-private.virgilsecurity.com";
#endif

ServiceUri::ServiceUri()
        : identityService_(kIdentityServiceUri),
          keysService_(kKeysServiceUri),
          privateKeyService_(kPrivateKeyServiceUri) {
}

ServiceUri::ServiceUri(const std::string& identityService, const std::string& keysService,
                       const std::string& privateKeyService)
        : identityService_(identityService),
          keysService_(keysService),
          privateKeyService_(privateKeyService) {
}

std::string ServiceUri::getIdentityService() const {
    return identityService_;
}

std::string ServiceUri::getPublicKeyService() const {
    return keysService_;
}

std::string ServiceUri::getPrivateKeyService() const {
    return privateKeyService_;
}
