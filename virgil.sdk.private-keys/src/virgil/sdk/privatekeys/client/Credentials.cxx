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

#include <algorithm>

#include <virgil/sdk/privatekeys/client/Credentials.h>

using virgil::sdk::privatekeys::client::Credentials;

Credentials::Credentials(const std::string& publicKeyId, const std::vector<unsigned char>& privateKey,
        const std::string& privateKeyPassword)
        : publicKeyId_(publicKeyId), privateKey_(privateKey), privateKeyPassword_(privateKeyPassword) {
}

Credentials::Credentials(const std::vector<unsigned char>& privateKey, const std::string& privateKeyPassword)
        : publicKeyId_(), privateKey_(privateKey), privateKeyPassword_(privateKeyPassword) {
}

bool Credentials::isValid() const {
    return !privateKey_.empty();
}

void Credentials::cleanup() noexcept {
    std::fill(privateKey_.begin(), privateKey_.end(), 0);
    std::fill(privateKeyPassword_.begin(), privateKeyPassword_.end(), 0);

    publicKeyId_.resize(0);
    privateKey_.resize(0);
    privateKeyPassword_.resize(0);
}

Credentials::~Credentials() noexcept {
    cleanup();
}

const std::string& Credentials::publicKeyId() const {
    return publicKeyId_;
}

const std::vector<unsigned char>& Credentials::privateKey() const {
    return privateKey_;
}

const std::string& Credentials::privateKeyPassword() const {
    return privateKeyPassword_;
}


