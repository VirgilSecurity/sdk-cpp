#ifndef VIRGIL_SDK_SERVICE_CARDS_H
#define VIRGIL_SDK_SERVICE_CARDS_H

#include <virgil/sdk/model/Card.h>

namespace virgil {
namespace sdk {
    /**
     * @brief This class specify interface which provide Virgil Services Cards
     */
    class ServiceCards {
    public:
        /**
         * @brief Return Virgil Card of Virgil Keys Service
         *
         * @note This card is used for two clients: PublicKeysKlient and CardsClient
         */
        virtual virgil::sdk::model::Card getKeysServiceCard() const = 0;
        /**
         * @brief Return Virgil Card of Virgil PrivateKeys Service
         */
        virtual virgil::sdk::model::Card getPrivateKeysServiceCard() const = 0;
        /**
         * @brief Return Virgil Card of Virgil Identity Service
         */
        virtual virgil::sdk::model::Card getIdentityServiceCard() const = 0;
        /**
         * @brief Empty destructor
         */
        // clang-format off
    virtual ~ServiceCards() noexcept {}
        // clang-format on
    };
} // sdk
} // virgil

#endif /* VIRGIL_SDK_SERVICE_CARDS_H */
