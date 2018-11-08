/**
 * Copyright (C) 2015-2018 Virgil Security Inc.
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
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 */

#ifndef VIRGIL_SDK_UTIL_JSON_KEY_H
#define VIRGIL_SDK_UTIL_JSON_KEY_H

#include <string>

namespace virgil {
namespace sdk {
    namespace util {
        /**
         * @brief This class holds string constants of Json keys.
         *
         * @note This class belongs to the **private** API
         */
        class JsonKey {
        public:
            //! @cond Doxygen_Suppress
            static const std::string Signer;
            static const std::string Snapshot;
            static const std::string Signature;
            static const std::string Signatures;
            static const std::string PublicKey;
            static const std::string ContentSnapshot;
            static const std::string PreviousCardId;
            static const std::string CreatedAt;
            static const std::string Identity;
            static const std::string Version;
            static const std::string Code;
            static const std::string Message;

            static const std::string Algorithm;
            static const std::string Type;
            static const std::string ContentType;
            static const std::string KeyIdentifier;

            static const std::string AppId;
            static const std::string IdentityJWT;
            static const std::string IssuedAt;
            static const std::string ExpiresAt;
            static const std::string AdditionalData;

            //! @endcond

            /*!
             * @brief Forbid creation.
             *
             */
            JsonKey() = delete;
        };
    }
}
}

#endif /* VIRGIL_SDK_UTIL_JSON_KEY_H */