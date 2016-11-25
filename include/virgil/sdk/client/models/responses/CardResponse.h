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


#ifndef VIRGIL_SDK_CARDRESPONSE_H
#define VIRGIL_SDK_CARDRESPONSE_H

#include <unordered_map>
#include <virgil/sdk/Common.h>
#include <virgil/sdk/client/models/Card.h>
#include <virgil/sdk/client/models/snapshotmodels/CreateCardSnapshotModel.h>

using virgil::sdk::client::models::Card;
using virgil::sdk::client::models::snapshotmodels::CreateCardSnapshotModel;

namespace virgil {
namespace sdk {
namespace client {
namespace models {
    namespace responses {
        class CardResponse {
        public:
            Card buildCard() const;

            CardResponse(unordered_map<string, VirgilByteArray> signatures,
                    VirgilByteArray snapshot,
                    CreateCardSnapshotModel model,
                    string identifier,
                    string createdAt,
                    string cardVersion);

            const std::unordered_map<std::string, VirgilByteArray>& signatures() const { return signatures_; };
            const VirgilByteArray& snapshot() const { return snapshot_; };
            const CreateCardSnapshotModel& model() const { return model_; };
            const std::string& identifier() const { return identifier_; };
            const std::string& createdAt() const { return createdAt_; };
            const std::string& cardVersion() const { return cardVersion_; };


        private:
            std::unordered_map<std::string, VirgilByteArray> signatures_;
            VirgilByteArray snapshot_;
            CreateCardSnapshotModel model_;
            std::string identifier_;
            std::string createdAt_;
            std::string cardVersion_;
        };
    }
}
}
}
}

#endif //VIRGIL_SDK_CARDRESPONSE_H
