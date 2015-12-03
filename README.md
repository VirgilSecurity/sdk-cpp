[![Build Status](https://travis-ci.org/VirgilSecurity/virgil-sdk-cpp.svg?branch=master)](https://travis-ci.org/VirgilSecurity/virgil-sdk-cpp)
[![GitHub license](https://img.shields.io/badge/license-BSD%203--Clause-blue.svg)](https://raw.githubusercontent.com/VirgilSecurity/virgil-sdk-cpp/release/LICENSE)
[![Documentation Developers](https://img.shields.io/badge/docs-developers-green.svg)](https://virgilsecurity.com/documents/cpp/quickstart)
[![Documentation Doxygen](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://VirgilSecurity.github.io/virgil-sdk-cpp)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/7135/badge.svg)](https://scan.coverity.com/projects/virgilsecurity-virgil-sdk-cpp)

# Virgil Security C++ SDKs

- [Introduction](#introduction)
- [Obtain Application Token](#obtain-application-token)
- [Usage examples](#usage-examples)
    - [Example 1: Generate keys](#example-1)
    - [Example 2: Register user](#example-2)
    - [Example 3: Get user's public key](#example-3)
    - [Example 4: Store private key](#example-4)
    - [Example 5: Get user's private key](#example-5)
    - [Example 6: Encrypt data](#example-6)
    - [Example 7: Sign data](#example-7)
    - [Example 8: Verify data](#example-8)
    - [Example 9: Decrypt data](#example-9)
- [More examples](#more-examples)
- [Build](#build)
- [See also](#see-also)
- [License](#license)
- [Contacts](#contacts)

## Introduction

This is quickstart guide that helps to start using C++ implementation of:

  * [Virgil Crypto Library](https://github.com/VirgilSecurity/virgil-crypto.git)
  * [Virgil Public Keys Service](https://virgilsecurity.com/documents/cpp/keys-service) and it's [SDK](https://github.com/VirgilSecurity/virgil-sdk-cpp/tree/release/virgil.sdk.keys)
  * [Virgil Private Keys Service](https://virgilsecurity.com/documents/cpp/keys-private-service) and it's [SDK](https://github.com/VirgilSecurity/virgil-sdk-cpp/tree/release/virgil.sdk.private-keys).

## <a name="obtain-application-token"></a> Obtain Application Token

First you must create a free Virgil Security developer account by [sign up](https://virgilsecurity.com/account/signup). Once you have your account you can [sign in](https://virgilsecurity.com/account/signin) and generate an app token for your application.

The app token provides authenticated secure access to Virgil’s Keys Service and is passed with each API call. The app token also allows the API to associate your app’s requests with your Virgil Security developer account.

Simply add your app token to the HTTP header for each request:

```
X-VIRGIL-APPLICATION-TOKEN: <YOUR_APPLICATION_TOKEN>
```

## Usage examples

This section describes common case library usage scenarios.
Full source code examples are available on [GitHub](https://github.com/VirgilSecurity/virgil-sdk-cpp/tree/release/examples/src) in public access, also see section [More examples](#more-examples).

### <a name="example-1"></a> Example 1: Generate keys

To use Virgil Security Services it is required to create public key and a private key. The public key can be made public to anyone using the [Virgil Public Keys Service] while the private key must be known only to the party or parties who will decrypt the data encrypted with the public key.

> **Private keys should never be stored verbatim or in plain text on the local computer.**<br>
> \- If you need to store a private key, you should use a secure key container depending on your platform. You also can use Virgil Security Services. This will allows you to easily synchronize private keys between clients devices and applications. Please read more about [Virgil Private Keys Service](https://virgilsecurity.com/documents/cpp/keys-private-service).

The following code example creates a new public/private key pair.
``` {.cpp}
// Specify password in the constructor to store private key encrypted.
VirgilKeyPair newKeyPair;
VirgilByteArray publicKey = newKeyPair.publicKey();
VirgilByteArray privateKey = newKeyPair.privateKey();
```
### <a name="example-2"></a> Example 2: Register user

Once you've created a public key you may push it to Virgil’s Keys Service. This will allow other users to send you encrypted data using your public key.

This example shows how to upload a public key and register a new account on Virgil’s Keys Service.

``` {.cpp}
UserData userData = UserData::email("mail@server.com");
Credentials credentials(privateKey);
KeysClient keysClient("{Application Token}");
PublicKey virgilPublicKey = keysClient.publicKey().add(publicKey, {userData}, credentials);
```

Then Confirm User Data using your user data type (Currently supported only Email).

``` {.cpp}
auto userDataId = virgilPublicKey.userData().front().userDataId();
// Confirmation code you received on your email box.
auto confirmationCode = "";
KeysClient keysClient("{Application Token}");
keysClient.userData().confirm(userDataId, confirmationCode);
```

### <a name="example-3"></a> Example 3: Get user's public key

Get public key from Public Keys Service.

``` {.cpp}
KeysClient keysClient("{Application Token}");
PublicKey publicKey = keysClient.publicKey().grab("mail@server.com");
```


### <a name="example-4"></a> Example 4: Store private key

This example shows how to store private keys on Virgil Private Keys service using SDK, this step is optional and you can use your own secure storage.

``` {.cpp}
// Create client
PrivateKeysClient privateKeysClient("{Application Token}");

// Prepare parameters
CredentialsExt credentialsExt(publicKey.publicKeyId(), privateKey);
// ContainerType::Easy or ContainerType::Normal
auto containerType = ContainerType::Easy;
auto containerPassword = "123456789";

// Create container for private keys storage.
privateKeysClient.container().create(credentialsExt, containerType, containerPassword);

// Authenticate user with email and password
UserData userData = UserData::email("{User's email}");
privateKeysClient.auth().authenticate(userData, containerPassword);

// Push private key to the container.
privateKeysClient.privateKey().add(credentialsExt, containerPassword);
```

### <a name="example-5"></a> Example 5: Get user's private key

Get user's Private Key from the Virgil Private Keys service.

```cpp
PrivateKeysClient privateKeysClient("{Application Token}");
UserData userData = UserData::email("mail@server.com");
privateKeysClient.authenticate(userData, containerPassword);

// if the token has been received
// std::string authenticationToken = "";
// privateKeysClient.authenticate(authenticationToken);

PrivateKey privateKey = privateKeysClient.privateKey().get(publicKeyId, containerPassword);
```


### <a name="example-6"></a> Example 6: Encrypt data

The procedure for encrypting and decrypting documents is straightforward with this mental model. For example: if you want to encrypt the data to Bob, you encrypt it using Bobs's public key which you can get from Public Keys Service, and he decrypts it with his private key. If Bob wants to encrypt data to you, he encrypts it using your public key, and you decrypt it with your private key.

In code example below data encrypted with public key previously loaded from Virgil's Public Keys Service.

``` {.cpp}
VirgilCipher cipher;
cipher.addKeyRecipient(virgil::crypto::str2bytes(publicKey.publicKeyId()), publicKey.key());
VirgilByteArray encryptedData = cipher.encrypt(virgil::crypto::str2bytes("Data to be encrypted."), true);
```

### <a name="example-7"></a> Example 7: Sign data

Cryptographic digital signatures use public key algorithms to provide data integrity. When you sign data with a digital signature, someone else can verify the signature, and can prove that the data originated from you and was not altered after you signed it.

The following example applies a digital signature to public key identifier.

``` {.cpp}
VirgilSigner signer;
VirgilByteArray data = virgil::crypto::str2bytes("some data");
VirgilByteArray sign = signer.sign(data, privateKey);
```

### <a name="example-8"></a> Example 8: Verify data

To verify that data was signed by a particular party, you must have the following information:

* The public key of the party that signed the data.
* The digital signature.
* The data that was signed.

The following example verifies a digital signature which was signed by sender.

``` {.cpp}
bool verified = signer.verify(data, sign, publicKey.key());
```

### <a name="example-9"></a> Example 9: Decrypt data

The following example illustrates the decryption of encrypted data by public key.

``` {.cpp}
VirgilByteArray decryptedData = cipher.decrypt(encryptedData, publicKey.publicKeyId(), privateKey);
```
## Build

Run one of the following commands in the project's root folder.

  * Build Public Keys SDK

    * Unix:

            mkdir build && cd build && cmake -DVIRGIL_SDK_KEYS=ON .. && make -j4

    * Windows:

            mkdir build && cd build && cmake -DVIRGIL_SDK_KEYS=ON .. && nmake

  * Build Private Keys SDK

    * Unix:

            mkdir build && cd build && cmake -DVIRGIL_SDK_PRIVATE_KEYS=ON .. && make -j4

    * Windows:

            mkdir build && cd build && cmake -DVIRGIL_SDK_PRIVATE_KEYS=ON .. && nmake

  * Build Examples

    * Unix:

            mkdir build && cd build && cmake -DVIRGIL_EXAMPLES=ON .. && make -j4

    * Windows:

            mkdir build && cd build && cmake -DVIRGIL_EXAMPLES=ON .. && nmake


## More examples

* [Examples list](https://github.com/VirgilSecurity/virgil-sdk-cpp/tree/release/examples)

## See also

* [Virgil Security SDKs API](http://virgilsecurity.github.io/virgil-sdk-cpp)

## License

BSD 3-Clause. See [LICENSE](https://raw.githubusercontent.com/VirgilSecurity/virgil-sdk-cpp/release/LICENSE) for details.

## Contacts

Email: <support@virgilsecurity.com>
