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

#include <string>

#include <virgil/crypto/VirgilByteArray.h>
#include <virgil/crypto/VirgilSigner.h>
#include <virgil/crypto/foundation/VirgilBase64.h>

#include <virgil/sdk/client/ResponseVerify.h>
#include <virgil/sdk/http/Headers.h>

using virgil::crypto::VirgilByteArray;
using virgil::crypto::VirgilSigner;
using virgil::crypto::foundation::VirgilBase64;

using virgil::sdk::http::Response;

using virgil::sdk::http::kHeaderField_ResponseId;
using virgil::sdk::http::kHeaderField_ResponseSign;


bool virgil::sdk::client::verifyResponse(const Response& response, const VirgilByteArray& publicKey) {
    auto responseHeader = response.header();
    std::string responseData = responseHeader[kHeaderField_ResponseId] + response.body();
    std::string responseSign = responseHeader[kHeaderField_ResponseSign];

    VirgilSigner signer;
    bool verifed = signer.verify(VirgilBase64::decode(responseData), VirgilBase64::decode(responseSign), publicKey);
    return verifed;
}
