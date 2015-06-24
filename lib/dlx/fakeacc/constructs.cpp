
#include "DLX/Core/constructs.hpp"
#include "DLX/Core/frontend.hpp"
#include "DLX/Core/directives.hpp"
#include "DLX/FakeACC/language.hpp"

#include <cassert>

class SgLocatedNode;

namespace DLX {

namespace Directives {

template <>
generic_construct_t<FakeACC::language_t> * buildConstruct<FakeACC::language_t>(FakeACC::language_t::construct_kinds_e kind) {
  switch (kind) {
    case FakeACC::language_t::e_construct_kernel:
     return new construct_t<FakeACC::language_t, FakeACC::language_t::e_construct_kernel>();
    case FakeACC::language_t::e_construct_loop:
     return new construct_t<FakeACC::language_t, FakeACC::language_t::e_construct_loop>();
    case FakeACC::language_t::e_construct_last:
     assert(false);
    default:
     assert(false);
  }
}

template <>
bool findAssociatedNodes<FakeACC::language_t>(
  SgLocatedNode * directive_node,
  generic_construct_t<FakeACC::language_t> * construct,
  const std::map<SgLocatedNode *, directive_t<FakeACC::language_t> *> & translation_map
) {
  switch (construct->kind) {
    case FakeACC::language_t::e_construct_kernel:
     return Frontend::Frontend<FakeACC::language_t>::findAssociatedNodes<FakeACC::language_t::e_construct_kernel>(
       directive_node, (construct_t<FakeACC::language_t, FakeACC::language_t::e_construct_kernel> *)construct, translation_map
     );
    case FakeACC::language_t::e_construct_loop:
     return Frontend::Frontend<FakeACC::language_t>::findAssociatedNodes<FakeACC::language_t::e_construct_loop>(
       directive_node, (construct_t<FakeACC::language_t, FakeACC::language_t::e_construct_loop> *)construct, translation_map
     );
    case FakeACC::language_t::e_construct_last:
     assert(false);
    default:
     assert(false);
  }
}

}

}

