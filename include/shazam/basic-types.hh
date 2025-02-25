#ifndef _SHAZAM_BASIC_TYPES_HEADER
#define _SHAZAM_BASIC_TYPES_HEADER

#include <string>
#include <memory>

namespace shazam {
    /* Represents the status of the file on the program. */
    enum EFileStatus {
        VALID_FILE,
        NON_EXISTENT,
        IS_DIRECTORY,
        NON_PERMISSIVE,
        NON_READABLE
    };

    /* Result used when comparing hash sums. */
    enum ComparationResult {
        MATCH, NOT_MATCH
    };

    /* Struct used to store hash sums. */
    struct HashSum {
      const std::string filename;
      const std::string hashType;
      const std::string hashSum;
    };

    /* The result of the hash sum comparation */
    struct FileHashSumComparationResult {
        const std::string filename;
        const std::string hashType;
        const std::string originalHashSum;
        const std::string currentHashSum;
        const ComparationResult result;
    };

    /* Constant array with the types of hash sums supported
     * by this program.
     * */
    constexpr std::array<const char*, 5> HASH_TYPES = {
        "MD5",  "SHA1",  "SHA256", "SHA384",  "SHA512"
    };
};

#endif /* _SHAZAM_BASIC_TYPES_HEADER */
