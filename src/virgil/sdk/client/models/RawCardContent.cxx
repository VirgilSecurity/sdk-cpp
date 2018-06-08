/**
 * Copyright (C) 2018 Virgil Security Inc.
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

#include <virgil/sdk/client/models/RawCardContent.h>
#include <virgil/sdk/serialization/JsonSerializer.h>
#include <virgil/sdk/serialization/JsonDeserializer.h>

using virgil::sdk::client::models::RawCardContent;
using virgil::sdk::VirgilByteArray;
using virgil::sdk::serialization::JsonSerializer;
using virgil::sdk::serialization::JsonDeserializer;
using virgil::sdk::VirgilByteArrayUtils;

RawCardContent::RawCardContent(std::string identity,
                               VirgilByteArray publicKey,
                               std::time_t createdAt,
                               std::string previousCardId,
                               std::string version)
        : identity_(std::move(identity)), publicKey_(std::move(publicKey)), version_(std::move(version)),
          createdAt_(createdAt), previousCardId_(std::move(previousCardId)) {}

RawCardContent RawCardContent::parse(const VirgilByteArray &snapshot) {
    auto contentStr = VirgilByteArrayUtils::bytesToString(snapshot);

    return JsonDeserializer<RawCardContent>::fromJsonString(contentStr);
}

const std::string& RawCardContent::identity() const { return identity_; }

const VirgilByteArray& RawCardContent::publicKey() const { return publicKey_; }

const std::string& RawCardContent::version() const { return version_; }

const std::time_t& RawCardContent::createdAt() const { return createdAt_; }

const std::string& RawCardContent::previousCardId() const { return  previousCardId_; }

VirgilByteArray RawCardContent::snapshot() const {
    auto contentStr = JsonSerializer<RawCardContent>::toJson(*this);

    return VirgilByteArrayUtils::stringToBytes(contentStr);
}