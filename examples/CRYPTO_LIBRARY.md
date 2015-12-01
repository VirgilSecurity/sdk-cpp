# C++ Crypto Library

- [Generate Keys](#generate-keys)
- [Encrypt and Decrypt data using keys](#encrypt-and-decrypt-using-keys)
- [Encrypt and Decrypt data using password](#encrypt-and-decrypt-using-password)
- [Encrypt data for multiple recipients](#encrypt-using-multiple-recipients)
- [Sign and Verify data](#sign-and-verify-data)

## <a name="generate-keys"></a> Generate Keys \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/keygen.cxx)\]

```cpp
// Specify password in the constructor to store private key encrypted.
// VirgilByteArray pwd = virgil::crypto::str2bytes("strong private key password");
// VirgilKeyPair newKeyPair(pwd);

VirgilKeyPair newKeyPair;
VirgilByteArray publicKey = newKeyPair.publicKey();
VirgilByteArray privateKey = newKeyPair.privateKey();
```

## <a name="encrypt-and-decrypt-using-keys"></a> Encrypt and Decrypt data using keys

### Encrypt data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/encrypt_with_key.cxx)\]

```cpp
VirgilStreamCipher cipher;
cipher.addKeyRecipient(publicKeyId, publicKey.key());
cipher.encrypt(dataSource, dataSink, true);
```

### Decrypt data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/decrypt_with_key.cxx)\]

```cpp
VirgilStreamCipher cipher;
// using private key with password
// cipher.decryptWithKey(dataSource, dataSink, publicKeyId, privateKey, privateKeyPass);
cipher.decryptWithKey(dataSource, dataSink, publicKeyId, privateKey);
```

## <a name="encrypt-and-decrypt-using-password"></a> Encrypt and Decrypt data using password

### Encrypt data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/encrypt_with_pass.cxx)\]

```cpp
VirgilStreamCipher cipher;
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.addPasswordRecipient(recipientPwd);
cipher.encrypt(dataSource, dataSink, true);
```

### Decrypt data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/decrypt_with_pass.cxx)\]

```cpp
VirgilStreamCipher cipher;
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.decryptWithPassword(dataSource, dataSink, recipientPwd);
```


## <a name="encrypt-using-multiple-recipients"></a> Encrypt data for multiple recipients

### Encrypt data \[[src]((https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/encrypt_with_multiple_recipients.cxx)\]

```cpp
VirgilStreamCipher cipher;
cipher.addKeyRecipient(alicePublicKeyId, alicePublicKey.key());
cipher.addKeyRecipient(bobPublicKeyId, bobPublicKey.key());
VirgilByteArray recipientPwd = virgil::crypto::str2bytes("strong password");
cipher.addPasswordRecipient(recipientPwd);
cipher.encrypt(dataSource, dataSink, true);
```

## <a name="sign-and-verify-data"></a> Sign and Verify data

### Sign data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/sign.cxx)\]

```cpp
VirgilStreamSigner signer;
// if Signer has a private key with password
// std::string privateKeyPass = "strong private key password";
// VirgilByteArray sign = signer.sign(dataSource, privateKey, privateKeyPass);
VirgilByteArray sign = signer.sign(dataSource, privateKey);
```

### Verify data \[[src](https://github.com/VirgilSecurity/virgil-sdk-cpp/blob/develop/examples/src/verify.cxx)\]

```cpp
VirgilStreamSigner signer;
bool verified = signer.verify(dataSource, sign, publicKey.key());
```
