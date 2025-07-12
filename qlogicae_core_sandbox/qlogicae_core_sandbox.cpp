#pragma once

#include "pch.h"

struct JwtVerificationResult {
    bool is_successful = false;
    std::string message;
    std::string subject;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> payloads;
};

const jwt::algorithm::es256k& get_es256k_signer(const std::string& pub, const std::string& priv) {
    static const jwt::algorithm::es256k signer(pub, priv, "", "");
    return signer;
}

const jwt::algorithm::es256k& get_es256k_verifier(const std::string& pub) {
    static const jwt::algorithm::es256k verifier(pub, "", "", "");
    return verifier;
}

std::string create_jwt_es256k(const std::string& subject,
    const std::string& issuer,
    const std::string& pub_key,
    const std::string& priv_key,
    std::chrono::seconds lifetime,
    const std::map<std::string, std::string>& claims) {
    auto now = std::chrono::system_clock::now();

    auto builder = jwt::create()
        .set_type("JWT")
        .set_issuer(issuer)
        .set_subject(subject)
        .set_issued_at(now);

    if (lifetime.count() > 0)
        builder.set_expires_at(now + lifetime);

    for (const auto& [k, v] : claims)
        builder.set_payload_claim(k, jwt::claim(v));

    return builder.sign(get_es256k_signer(pub_key, priv_key));
}

JwtVerificationResult verify_jwt_es256k(const std::string& token,
    const std::string& expected_issuer,
    const std::string& pub_key) {
    JwtVerificationResult result;

    try {
        auto decoded = jwt::decode(token);

        if (decoded.get_issuer() != expected_issuer) {
            result.message = "Invalid issuer";
            return result;
        }

        jwt::verify()
            .allow_algorithm(get_es256k_verifier(pub_key))
            .with_issuer(expected_issuer)
            .leeway(30)
            .verify(decoded);

        result.is_successful = true;
        result.subject = decoded.get_subject();

        for (const auto& [k, v] : decoded.get_header_json())
            result.headers[k] = v.serialize();

        for (const auto& [k, v] : decoded.get_payload_json())
            result.payloads[k] = v.serialize();
    }
    catch (const std::exception& ex) {
        result.message = std::string("JWT verification failed: ") + ex.what();
    }

    return result;
}

int main() {
    if (sodium_init() < 0) {
        std::cerr << "Failed to initialize libsodium" << std::endl;
        return 1;
    }

    std::string password = "strong_password";
    
    std::string es256k_priv_key = R"(-----BEGIN EC PRIVATE KEY-----
MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK
oUQDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKaK9EDZi0mZ7VUeeNKq476CU5X
940yusahgneePQrDMF2nWFEtBCOiXQ==
-----END EC PRIVATE KEY-----)";

    std::string es256k_pub_key = R"(-----BEGIN PUBLIC KEY-----
MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa
K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==
-----END PUBLIC KEY-----)";

    auto token = create_jwt_es256k(
        "user123", "auth0", es256k_pub_key, es256k_priv_key,
        std::chrono::seconds{ 3600 },
        { { "role", "admin" }, { "feature", "billing" } });

    auto result = verify_jwt_es256k(token, "auth0", es256k_pub_key);
    if (result.is_successful) {
        std::cout << "JWT verified. Subject: " << result.subject << "\n";
    }
    else {
        std::cerr << result.message << "\n";
    }


    return 0;
}
