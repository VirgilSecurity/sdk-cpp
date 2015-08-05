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

#ifndef VIRGIL_STRING_JSON_KEY_H
#define VIRGIL_STRING_JSON_KEY_H

#include <string>

namespace virgil { namespace sdk { namespace keys { namespace util {
    /**
     * @brief This class holds string constants of Json keys.
     */
    class JsonKey {
    public:
        static const std::string publicKey; /*!< Json key for public key object. */
        static const std::string publicKeys; /*!< Json key for public key objects. */
        static const std::string userData; /*!< Json key for user data object. */
        static const std::string className; /*!< Json key for user data class name. */
        static const std::string type; /*!< Json key for user data type. */
        static const std::string value; /*!< Json key for user data value. */
        static const std::string isConfirmed; /*!< Json key for user data status: is confirmed. */
        static const std::string error; /*!< Json key for error object. */
        static const std::string code; /*!< Json key for error code. */
        static const std::string id; /*!< Json key for id object. */
        static const std::string accountId; /*!< Json key for account GUID. */
        static const std::string publicKeyId; /*!< Json key for public key GUID. */
        static const std::string userDataId; /*!< Json key for user data GUID. */
        static const std::string expanded; /*!< Json key for expanded object. */
        static const std::string guid; /*!< Json key for guid value. */
    private:
        JsonKey();
    };
}}}}

#endif /* VIRGIL_STRING_JSON_KEY_H */
