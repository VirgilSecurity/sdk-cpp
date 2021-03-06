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

#include <catch.hpp>

#include <thread>
#include <memory>

#include <TestConst.h>
#include <TestUtils.h>
#include <TestData.h>

#include <virgil/sdk/cards/CardManager.h>
#include <virgil/sdk/cards/verification/VirgilCardVerifier.h>
#include <virgil/sdk/util/JsonUtils.h>
#include <virgil/sdk/util/JsonKey.h>
#include <virgil/sdk/jwt/JwtVerifier.h>
#include <virgil/sdk/jwt/JwtGenerator.h>

using virgil::sdk::crypto::Crypto;
using virgil::sdk::test::TestUtils;
using virgil::sdk::VirgilBase64;
using virgil::sdk::VirgilByteArrayUtils;
using virgil::sdk::cards::CardManager;
using virgil::sdk::cards::verification::VirgilCardVerifier;
using virgil::sdk::util::JsonUtils;
using virgil::sdk::cards::ModelSigner;
using virgil::sdk::cards::verification::VerifierCredentials;
using virgil::sdk::cards::verification::Whitelist;

const auto testData = virgil::sdk::test::TestData();

TEST_CASE("test001_STC_8", "[signer_verifier]") {
    TestConst consts;
    TestUtils utils(consts);

    auto signer = ModelSigner(utils.crypto());
    auto keyPair1 = utils.crypto()->generateKeyPair();
    auto randomBytes = utils.getRandomBytes();

    auto rawCard = RawSignedModel(randomBytes);
    signer.selfSign(rawCard, keyPair1.privateKey());
    REQUIRE(rawCard.signatures().size() == 1);

    bool errorWasThrown = false;
    try {
        signer.selfSign(rawCard, keyPair1.privateKey());
    } catch (...) {
        errorWasThrown = true;
    }
    REQUIRE(errorWasThrown);

    auto keyPair2 = utils.crypto()->generateKeyPair();
    signer.sign(rawCard, "test", keyPair2.privateKey());
    REQUIRE(rawCard.signatures().size() == 2);

    for (auto& signature : rawCard.signatures()) {
        if (signature.signer() == "self") {
            REQUIRE(utils.crypto()->verify(randomBytes, signature.signature(), keyPair1.publicKey()));
            REQUIRE(signature.snapshot().empty());
        }
        else if (signature.signer() == "test") {
            REQUIRE(utils.crypto()->verify(randomBytes, signature.signature(), keyPair2.publicKey()));
            REQUIRE(signature.snapshot().empty());
        }
        else
            FAIL();
    }

    errorWasThrown = false;
    try {
        signer.sign(rawCard, "test", keyPair2.privateKey());
    } catch (...) {
        errorWasThrown = true;
    }
    REQUIRE(errorWasThrown);
}

TEST_CASE("test002_STC_9", "[signer_verifier]") {
    TestConst consts;
    TestUtils utils(consts);

    auto signer = ModelSigner(utils.crypto());
    auto keyPair1 = utils.crypto()->generateKeyPair();
    auto randomBytes = utils.getRandomBytes();

    auto rawCard = RawSignedModel(randomBytes);

    std::unordered_map<std::string, std::string> dic = {
            {"key", "value"}
    };

    signer.selfSign(rawCard, keyPair1.privateKey(), dic);
    REQUIRE(rawCard.signatures().size() == 1);

    bool errorWasThrown = false;
    try {
        signer.selfSign(rawCard, keyPair1.privateKey(), dic);
    } catch (...) {
        errorWasThrown = true;
    }
    REQUIRE(errorWasThrown);

    auto keyPair2 = utils.crypto()->generateKeyPair();
    signer.sign(rawCard, "test", keyPair2.privateKey(), dic);
    REQUIRE(rawCard.signatures().size() == 2);

    for (auto& signature : rawCard.signatures()) {
        if (signature.signer() == "self") {
            auto cardSnapshot = rawCard.contentSnapshot();
            VirgilByteArrayUtils::append(cardSnapshot, signature.snapshot());
            REQUIRE(utils.crypto()->verify(cardSnapshot, signature.signature(), keyPair1.publicKey()));

            auto additionalDataStr = VirgilByteArrayUtils::bytesToString(signature.snapshot());
            auto additionalDataJson = nlohmann::json::parse(additionalDataStr);
            auto additionalData = JsonUtils::jsonToUnorderedMap(additionalDataJson);

            REQUIRE(additionalData == dic);
        }
        else if (signature.signer() == "test") {
            auto cardSnapshot = rawCard.contentSnapshot();
            VirgilByteArrayUtils::append(cardSnapshot, signature.snapshot());
            REQUIRE(utils.crypto()->verify(cardSnapshot, signature.signature(), keyPair2.publicKey()));

            auto additionalDataStr = VirgilByteArrayUtils::bytesToString(signature.snapshot());
            auto additionalDataJson = nlohmann::json::parse(additionalDataStr);
            auto additionalData = JsonUtils::jsonToUnorderedMap(additionalDataJson);

            REQUIRE(additionalData == dic);
        }
        else
            FAIL();
    }

    errorWasThrown = false;
    try {
        signer.sign(rawCard, "test", keyPair2.privateKey(), dic);
    } catch (...) {
        errorWasThrown = true;
    }
    REQUIRE(errorWasThrown);
}

TEST_CASE("test003_STC_10", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-10.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    auto privateKey1Str = testData.dict()["STC-10.private_key1_base64"];
    auto privateKey1Data = VirgilBase64::decode(privateKey1Str);
    auto privateKey1 = crypto->importPrivateKey(privateKey1Data);

    auto publicKey1 = crypto->extractPublicKeyFromPrivateKey(privateKey1);
    auto publicKey1Data = crypto->exportPublicKey(publicKey1);
    auto publicKey2Data = crypto->exportPublicKey(crypto->generateKeyPair().publicKey());
    auto publicKey3Data = crypto->exportPublicKey(crypto->generateKeyPair().publicKey());

    REQUIRE(verifier1->verifyCard(card));

    auto verifier2 = VirgilCardVerifier(crypto, {}, true, false);
    REQUIRE(verifier2.verifyCard(card));

    auto verifier3 = VirgilCardVerifier(crypto, {}, true, true);
    REQUIRE(verifier3.verifyCard(card));

    auto whitelist1 = Whitelist({VerifierCredentials("extra", publicKey1Data)});
    auto verifier4 = VirgilCardVerifier(crypto, {whitelist1});
    REQUIRE(verifier4.verifyCard(card));

    auto whitelist2 = Whitelist({VerifierCredentials("extra", publicKey1Data),
                                 VerifierCredentials("test1", publicKey2Data)});
    auto verifier5 = VirgilCardVerifier(crypto, {whitelist2});
    REQUIRE(verifier5.verifyCard(card));

    auto whitelist31 = Whitelist({VerifierCredentials("extra", publicKey1Data),
                                  VerifierCredentials("test1", publicKey2Data)});
    auto whitelist32 = Whitelist({VerifierCredentials("extra", publicKey3Data)});
    auto verifier6 = VirgilCardVerifier(crypto, {whitelist31, whitelist32});
    REQUIRE(!verifier6.verifyCard(card));
}

TEST_CASE("test004_STC_11", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-11.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    REQUIRE(verifier1->verifyCard(card));

    auto verifier2 = VirgilCardVerifier(crypto, {}, true, false);
    REQUIRE(!verifier2.verifyCard(card));
}

TEST_CASE("test005_STC_12", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-12.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    REQUIRE(verifier1->verifyCard(card));

    auto verifier2 = VirgilCardVerifier(crypto, {}, false, true);
    REQUIRE(!verifier2.verifyCard(card));
}

TEST_CASE("test006_STC_14", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-14.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    auto verifier2 = VirgilCardVerifier(crypto, {}, false, true);
    REQUIRE(!verifier2.verifyCard(card));
}

TEST_CASE("test007_STC_15", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-15.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    auto verifier2 = VirgilCardVerifier(crypto, {}, true, false);
    REQUIRE(!verifier2.verifyCard(card));
}

TEST_CASE("test008_STC_16", "[signer_verifier]") {
    auto crypto = std::make_shared<Crypto>();

    auto verifier1 = std::make_shared<VirgilCardVerifier>(crypto, std::vector<Whitelist>(), false, false);

    CardManager cardManager(crypto, nullptr, verifier1);

    auto cardStr = testData.dict()["STC-16.as_string"];
    auto card = cardManager.importCardFromBase64(cardStr);

    auto publicKeyStr = testData.dict()["STC-16.public_key1_base64"];
    auto publicKey1Data = VirgilBase64::decode(publicKeyStr);
    auto publicKey2Data = crypto->exportPublicKey(crypto->generateKeyPair().publicKey());

    auto whitelist1 = Whitelist({VerifierCredentials("extra", publicKey2Data)});
    auto verifier2 = VirgilCardVerifier(crypto, {whitelist1}, false, false);
    REQUIRE(!verifier2.verifyCard(card));

    auto whitelist2 = Whitelist({VerifierCredentials("extra", publicKey1Data)});
    auto verifier3 = VirgilCardVerifier(crypto, {whitelist2}, false, false);
    REQUIRE(verifier3.verifyCard(card));
}