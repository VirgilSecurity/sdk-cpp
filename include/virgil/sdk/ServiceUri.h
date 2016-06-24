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

#ifndef VIRGIL_SDK_SERVICE_URI_H
#define VIRGIL_SDK_SERVICE_URI_H

#include <string>

namespace virgil {
namespace sdk {

    /**
     * @brief This class provide base URIs for the Virgil Security services
     */
    class ServiceUri {
    public:
        /**
         * @property kIdentityServiceUri
         * @brief Default base address of the Virgil Identity Service
         */
        static const std::string kIdentityServiceUri;
        /**
         * @property kKeysServiceUri
         * @brief Default base address of the Virgil Keys Service
         */
        static const std::string kKeysServiceUri;
        /**
         * @property kPrivateKeyServiceUri
         * @brief Default base address of the Virgil Private Keys Service
         */
        static const std::string kPrivateKeyServiceUri;
        /**
         * @property kCAServiceUri
         * @brief Default base address of the Virgil CA Service
         */
        static const std::string kCAServiceUri;
        
    public:
        /**
         * @brief Use default services URIs
         */
        ServiceUri();

        /**
         * @brief Use user defined services URIs
         *
         * @param identityService - base address of the Virgil Identity Service
         * @param keysService - base address of the Virgil Keys Service
         * @param privateKeyService - base address of the Virgil Private Keys Service
         *
         * @note Pass only base address of service without trailing slash, i.e. https://keys.virgilsecurity.com
         */
        ServiceUri(const std::string& identityService, const std::string& keysService,
                   const std::string& privateKeyService, const std::string& caService);

    public:
        /**
         * @brief Return base URI of the Virgil Identity Service
         */
        std::string getIdentityService() const;
        /**
         * @brief Return base URI of the Virgil Keys Service
         */
        std::string getPublicKeyService() const;
        /**
         * @brief Return base URI of the Virgil Private Keys Service
         */
        std::string getPrivateKeyService() const;
        /**
         * @brief Return base URI of the Virgil CA Service
         */
        std::string getCAService() const;

    private:
        std::string identityService_;
        std::string keysService_;
        std::string privateKeyService_;
        std::string caService_;
    };
}
}

#endif /* VIRGIL_SDK_SERVICE_URI_H */
