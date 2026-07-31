#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonWebTokenCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    class JsonWebTokenCryptographyManagerTest: public ::testing::Test
    {
    public:
        JsonWebTokenCryptographyManagerTest()
        {
            manager.configurations.issuer = "test_issuer";
            manager.configurations.lifetime = std::chrono::seconds{10};
            manager.configurations.claims = {{"claim1","value1"}};
        }

        JsonWebTokenCryptographyManager manager;

        const std::string test_private_key =
            "-----BEGIN EC PRIVATE KEY-----\n"
            "MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK\n"
            "oUQDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKaK9EDZi0mZ7VUeeNKq476CU5X\n"
            "940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
            "-----END EC PRIVATE KEY-----";

        const std::string test_public_key =
            "-----BEGIN PUBLIC KEY-----\n"
            "MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa\n"
            "K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
            "-----END PUBLIC KEY-----";
    };

    struct JsonWebTokenParameter
    {
        std::string text;
        std::string public_key;
        std::string private_key;
        bool expected_success;
    };

    class JsonWebTokenParameterizedTest: public JsonWebTokenCryptographyManagerTest,
        public ::testing::WithParamInterface<JsonWebTokenParameter>
    {
    };
}

#endif
