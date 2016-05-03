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

#include <virgil/sdk/models/IdentityModel.h>
#include <virgil/sdk/dto/Identity.h>

using virgil::sdk::models::IdentityModel;
using virgil::sdk::dto::Identity;

IdentityModel::IdentityModel(const std::string& id, const std::string& createdAt, const std::string& value,
                             const IdentityModel::Type& type)
        : id_(id), createdAt_(createdAt), value_(value), type_(type) {
}

const std::string IdentityModel::getId() const {
    return id_;
}

const std::string IdentityModel::getCreatedAt() const {
    return createdAt_;
}

const std::string IdentityModel::getValue() const {
    return value_;
}

const IdentityModel::Type IdentityModel::getType() const {
    return type_;
}

std::string virgil::sdk::models::toString(const IdentityModel::Type& identityType) {
    if (identityType == IdentityModel::Type::Email) {
        return std::string("email");
    } else if (identityType == IdentityModel::Type::Application) {
        return std::string("application");
    } else {
        return std::string();
    }
}

IdentityModel::Type virgil::sdk::models::fromString(const std::string& identityType) {
    if (identityType == "email") {
        return IdentityModel::Type::Email;
    } else if (identityType == "application") {
        return IdentityModel::Type::Application;
    } else {
        return IdentityModel::Type::None;
    }
}
