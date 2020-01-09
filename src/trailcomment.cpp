#include <trailcomment.hpp>
#include <eosio/system.hpp>

ACTION trailcomment::comment(name sender, uint64_t id, string comment) {
  require_auth(sender);

  // Init the _comment table
  comments_table _comments(get_self(), sender.value);
  auto it_comment = _comments.find( id );
  uint32_t date = eosio::current_time_point().sec_since_epoch();

  if(it_comment != _comments.end()) {
    _comments.modify(it_comment, get_self(), [&]( auto& row ) {
    row.comment = comment;
    row.date = date;
    });
  }

  else { 
    _comments.emplace(sender,[&]( auto& row ) {
    row.id = id;
    row.comment = comment;
    row.date = date;
    });
  }
  
}

ACTION trailcomment::erase(name sender, uint64_t id) {
  require_auth(sender);

  // Init the _comment table
  comments_table _comments(get_self(), sender.value);
  auto it_comment = _comments.find( id );
  check(it_comment != _comments.end(), "Can't find comment");

  _comments.erase(it_comment);

}
