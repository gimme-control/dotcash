#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <iostream>

EVP_PKEY* generate_rsa_key() {
    EVP_PKEY* pkey = EVP_PKEY_new();
    if (!pkey) return nullptr;

    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4); 

    if (RSA_generate_key_ex(rsa, 3072, e, nullptr) != 1) {
        RSA_free(rsa);
        EVP_PKEY_free(pkey);
        BN_free(e);
        return nullptr;
    }

    EVP_PKEY_assign_RSA(pkey, rsa);
    BN_free(e);
    return pkey;
}

void save_keys(EVP_PKEY* pkey) {
    FILE* priv = fopen("private.pem", "wb");
    FILE* pub  = fopen("public.pem", "wb");

    PEM_write_PrivateKey(priv, pkey, nullptr, nullptr, 0, nullptr, nullptr);
    PEM_write_PUBKEY(pub, pkey);

    fclose(priv);
    fclose(pub);
}


#include <vector>
#include <cstring>

std::vector<unsigned char> sign_message(EVP_PKEY* pkey, const std::string& msg) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    std::vector<unsigned char> signature;

    EVP_DigestSignInit(ctx, nullptr, EVP_sha256(), nullptr, pkey);
    EVP_DigestSignUpdate(ctx, msg.data(), msg.size());

    size_t sig_len;
    EVP_DigestSignFinal(ctx, nullptr, &sig_len);

    signature.resize(sig_len);
    EVP_DigestSignFinal(ctx, signature.data(), &sig_len);
    signature.resize(sig_len);

    EVP_MD_CTX_free(ctx);
    return signature;
}


bool verify_signature(EVP_PKEY* pubkey,
                      const std::string& msg,
                      const std::vector<unsigned char>& sig) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pubkey);
    EVP_DigestVerifyUpdate(ctx, msg.data(), msg.size());

    int result = EVP_DigestVerifyFinal(ctx, sig.data(), sig.size());
    EVP_MD_CTX_free(ctx);

    return result == 1;
}


int main() {
    OpenSSL_add_all_algorithms();

    EVP_PKEY* key = generate_rsa_key();
    if (!key) {
        std::cerr << "Key generation failed\n";
        return 1;
    }

    save_keys(key);

    std::string message = "Hello secure world!";
    auto signature = sign_message(key, message);

    // Load public key from file
    FILE* pubf = fopen("public.pem", "rb");
    EVP_PKEY* pubkey = PEM_read_PUBKEY(pubf, nullptr, nullptr, nullptr);
    fclose(pubf);

    bool ok = verify_signature(pubkey, message, signature);
    std::cout << "Signature valid: " << (ok ? "YES" : "NO") << "\n";

    EVP_PKEY_free(pubkey);
    EVP_PKEY_free(key);
    EVP_cleanup();

    return 0; 
}
