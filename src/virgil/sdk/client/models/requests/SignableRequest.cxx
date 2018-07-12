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

#include <virgil/sdk/client/models/requests/SignableRequest.h>
#include <virgil/sdk/client/models/interfaces/SignableRequestInterface.h>
#include <virgil/sdk/client/models/serialization/JsonSerializer.h>
#include <virgil/sdk/client/models/requests/CreateCardRequest.h>
#include <virgil/sdk/client/models/requests/RevokeCardRequest.h>

using virgil::sdk::client::models::requests::SignableRequest;
using virgil::sdk::client::models::serialization::JsonSerializer;
using virgil::sdk::client::models::interfaces::SignableRequestInterface;
using virgil::sdk::client::models::requests::CreateCardRequest;
using virgil::sdk::client::models::requests::RevokeCardRequest;
using virgil::sdk::client::models::snapshotmodels::CreateCardSnapshotModel;
using virgil::sdk::client::models::snapshotmodels::RevokeCardSnapshotModel;

template <typename SnapshotModelType, typename DerivedClass>
std::string SignableRequest<SnapshotModelType, DerivedClass>::exportAsString() const {
    auto json = serialization::JsonSerializer<SignableRequestInterface>::toJson(*this);

    return VirgilBase64::encode(VirgilByteArrayUtils::stringToBytes(json));
}

/**
 * Explicit methods instantiation
 */
template std::string SignableRequest<CreateCardSnapshotModel, CreateCardRequest>::exportAsString() const;

template std::string SignableRequest<RevokeCardSnapshotModel, RevokeCardRequest>::exportAsString() const;