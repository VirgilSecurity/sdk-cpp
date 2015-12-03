# C++ Crypto Library

- [Generate Keys](#generate-keys)
- [Encrypt and Decrypt data using keys](#encrypt-and-decrypt-data-using-keys)
- [Encrypt and Decrypt data using password](#encrypt-and-decrypt-data-using-password)
- [Encrypt data for multiple recipients](#encrypt-data-for-multiple-recipients)
- [Sign and Verify data](#sign-and-verify-data)

## Generate Keys

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/keygen.cxx)\]

```cpp
// Specify password in the constructor to store private key encrypted.
// VirgilByteArray pwd = virgil::crypto::str2bytes("strong private key password");
// VirgilKeyPair newKeyPair(pwd);

VirgilKeyPair newKeyPair;
VirgilByteArray publicKey = newKeyPair.publicKey();
VirgilByteArray privateKey = newKeyPair.privateKey();
```

## Encrypt and Decrypt data using keys

### Encrypt data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/encrypt_with_key.cxx)\]

```cpp
VirgilStreamCipher cipher;
cipher.addKeyRecipient(publicKeyId, publicKey.key());
cipher.encrypt(dataSource, dataSink, true);
```

### Decrypt data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/decrypt_with_key.cxx)\]

```cpp
VirgilStreamCipher cipher;
// using private key with password
// cipher.decryptWithKey(dataSource, dataSink, publicKeyId, privateKey, privateKeyPwd);
cipher.decryptWithKey(dataSource, dataSink, publicKeyId, privateKey);
```

## Encrypt and Decrypt data using password

### Encrypt data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/encrypt_with_pass.cxx)\]

```cpp
VirgilStreamCipher cipher;
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.addPasswordRecipient(recipientPwd);
cipher.encrypt(dataSource, dataSink, true);
```

### Decrypt data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/decrypt_with_pass.cxx)\]

```cpp
VirgilStreamCipher cipher;
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.decryptWithPassword(dataSource, dataSink, recipientPwd);
```


## Encrypt data for multiple recipients

### Encrypt data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/encrypt_with_multiple_recipients.cxx)\]

```cpp
VirgilStreamCipher cipher;
cipher.addKeyRecipient(alicePublicKeyId, alicePublicKey.key());
cipher.addKeyRecipient(bobPublicKeyId, bobPublicKey.key());
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.addPasswordRecipient(recipientPwd);
cipher.encrypt(dataSource, dataSink, true);
```

## Sign and Verify data

### Sign data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/sign.cxx)\]

```cpp
VirgilStreamSigner signer;
// if Signer has a private key with password
// std::string privateKeyPwd = "strong private key password";
// VirgilByteArray sign = signer.sign(dataSource, privateKey, privateKeyPwd);
VirgilByteArray sign = signer.sign(dataSource, privateKey);
```

### Verify data

\[[Full source code](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/release/examples/src/verify.cxx)\]

```cpp
VirgilStreamSigner signer;
bool verified = signer.verify(dataSource, sign, publicKey.key());
```
