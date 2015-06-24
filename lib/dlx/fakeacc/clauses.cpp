
#include "DLX/Core/clauses.hpp"
#include "DLX/Core/frontend.hpp"
#include "DLX/FakeACC/language.hpp"

#include <cassert>

class SgLocatedNode;

namespace DLX {

namespace Directives {

template <>
generic_clause_t<FakeACC::language_t> * buildClause<FakeACC::language_t>(FakeACC::language_t::clause_kinds_e kind) {
  switch (kind) {
    case FakeACC::language_t::e_clause_data:
      return new clause_t<FakeACC::language_t, FakeACC::language_t::e_clause_data>();
    case FakeACC::language_t::e_clause_tile:
      return new clause_t<FakeACC::language_t, FakeACC::language_t::e_clause_tile>();
    case FakeACC::language_t::e_clause_last:
      assert(false);
    default:
     assert(false);
  }
}
 
template <>
bool parseClauseParameters<FakeACC::language_t>(
  std::string & directive_str,
  SgLocatedNode * directive_node,
  generic_clause_t<FakeACC::language_t> * clause
) {
  switch (clause->kind) {
    case FakeACC::language_t::e_clause_data:
      return Frontend::Frontend<FakeACC::language_t>::parseClauseParameters<FakeACC::language_t::e_clause_data>(
        directive_str, directive_node, (clause_t<FakeACC::language_t, FakeACC::language_t::e_clause_data> *)clause
      );
    case FakeACC::language_t::e_clause_tile:
      return Frontend::Frontend<FakeACC::language_t>::parseClauseParameters<FakeACC::language_t::e_clause_tile>(
        directive_str, directive_node, (clause_t<FakeACC::language_t, FakeACC::language_t::e_clause_tile> *)clause
      );
    case FakeACC::language_t::e_clause_last:
      assert(false);
    default:
      assert(false);
  }
}

}

}

