#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/crypto.h>
#include <string>

using namespace eosio;
using namespace std;

#define EOS_SYMBOL S(4, EOS)
#define LOG_CONTRACT N(dexaraniiznx)

class [[eosio::contract("rng_dex")]] rng : public eosio::contract {
public:
  using contract::contract;
        rng(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}
        
        [[eosio::action]]
        void genrandomint();

        [[eosio::action]]
        void randomint(uint32_t from, uint32_t to);


        [[eosio::action]]
        void notify(name user, uint32_t number, uint32_t v1);

private:

  void printmsg(name user, std::string _msg) {
    action(
      permission_level(name(get_self()), name("active")),
      get_self(),
      name("notify"),
      std::make_tuple(user, _msg)
    ).send();
  }

    uint8_t char2int(char input);

    void string2seed(const string& str, checksum256& seed);

    void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
    {
        /* Store the original string in the array, so we can loop the rest
         * of the algorithm. */
        tokens.push_back(str);

        // Store the split index in a 'size_t' (unsigned integer) type.
        size_t splitAt;
        // Store the size of what we're splicing out.
        size_t splitLen = splitBy.size();
        // Create a string for temporarily storing the fragment we're processing.
        std::string frag;
        // Loop infinitely - break is internal.
        while(true)
        {
            /* Store the last string in the vector, which is the only logical
             * candidate for processing. */
            frag = tokens.back();
            /* The index where the split is. */
            splitAt = frag.find(splitBy);
            // If we didn't find a new split point...
            if(splitAt == string::npos)
            {
                // Break the loop and (implicitly) return.
                break;
            }
            /* Put everything from the left side of the split where the string
             * being processed used to be. */
            tokens.back() = frag.substr(0, splitAt);
            /* Push everything from the right side of the split to the next empty
             * index in the vector. */
            tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
        }
    }
};
