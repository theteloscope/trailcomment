#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT trailcomment : public contract {
  public:
    using contract::contract;

    ACTION comment(name sender, uint64_t id, string comment);
    ACTION erase(name sender, uint64_t id);

  private:
    TABLE comments {
      uint64_t id;
      string  comment;
      uint32_t date;
      auto primary_key() const { return id; }
    };
    typedef multi_index<name("comments"), comments> comments_table;
};

EOSIO_DISPATCH(trailcomment, (comment)(erase))