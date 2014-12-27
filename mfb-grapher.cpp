
#include "MFB/Sage/driver.hpp"
#include "MFB/Sage/api.hpp"

#include "AST2GraphViz/cluster.hpp"

#include "rose.h"

#include <cassert>

namespace MFB {

namespace API2GraphViz {

class Traversal : public AST2GraphViz::Cluster {
  public:
    typedef AST2GraphViz::GraphVizAttr<AST2GraphViz::EmptyAttr>::Inherited   Inherited;
    typedef AST2GraphViz::GraphVizAttr<AST2GraphViz::EmptyAttr>::Synthesized Synthesized;
    typedef AST2GraphViz::EmptyAttr::Inherited   UserInherited;
    typedef AST2GraphViz::EmptyAttr::Synthesized UserSynthesized;

    typedef AST2GraphViz::GraphVizTraversal<AST2GraphViz::EmptyAttr>::graph_t graph_t;

  public:
    Traversal(api_t * api_) : AST2GraphViz::Cluster(), api(api_) {}
    virtual ~Traversal() {}

  protected:
    api_t * api;

    virtual void editNodeDesc(
                   SgNode * node,
                   const UserInherited & inherited_attr, const UserSynthesized & synthetized_attr,
                   AST2GraphViz::NodeDesc & node_desc
                 ) {
  Cluster::editNodeDesc(node, inherited_attr, synthetized_attr, node_desc);

  if (isSgEnumDeclaration(node->get_parent())) {
    SgInitializedName * init_name = isSgInitializedName(node);
    assert(init_name != NULL);
    std::ostringstream oss_label; oss_label << "Enumerator:\\n" << init_name->get_name().getString();
    node_desc.label = oss_label.str();
    node_desc.shape = "box";
    node_desc.color = "black";
    node_desc.fillcolor = "lightsalmon";
  }
    }

    virtual graph_t * getGraphInherited(
                   graph_t * suggested_graph, SgNode * node, SgNode * parent,
                   const UserInheritedAttr & inherited_attr
                 ) {
  if (isSgGlobal(node)) return NULL;
  if (isSgVariableDeclaration(node)) return NULL;
  if (node->get_parent() != NULL && isSgEnumDeclaration(node->get_parent()->get_parent())) {
    stopAtNode(node);
    return NULL;
  }
  return Cluster::getGraphInherited(suggested_graph, node, parent, inherited_attr);
    }

    virtual graph_t * getGraphSynthesized(
                   graph_t * suggested_graph, SgNode * node, SgNode * parent,
                   const UserInheritedAttr & inherited_attr, const UserSynthesizedAttr & synthetized_attr
                 ) {
  if (suggested_graph == NULL) return NULL;

  SgInitializedName * init_name = isSgInitializedName(node);
  SgClassDeclaration * class_decl = isSgClassDeclaration(node);
  SgFunctionDeclaration * func_decl = isSgFunctionDeclaration(node);
  SgMemberFunctionDeclaration * method_decl = isSgMemberFunctionDeclaration(node);
//Sg *  = is(node);

  if (init_name != NULL) {
    SgSymbol * sym = init_name->search_for_symbol_from_symbol_table();
    if (sym == NULL) {
      std::cerr << "SgInitializedName cannot find symbol." << std::endl;
      return suggested_graph;
    }
    SgVariableSymbol * var_sym = isSgVariableSymbol(sym);
    if (var_sym == NULL) {
      std::cerr << "SgInitializedName not a VariableSymbol." << std::endl;
      return suggested_graph;
    }
    std::set<SgVariableSymbol *>::iterator it_variable = api->variable_symbols.find(var_sym);
    if (it_variable == api->variable_symbols.end()) {
      std::cerr << "SgInitializedName not in API." << std::endl;
      return suggested_graph;
    }
    std::ostringstream oss; oss << "var_" << node;
    suggested_graph = suggested_graph->getSubgraph(oss.str());
    suggested_graph->filled = true;
    suggested_graph->color = "green";
  }
  else if (class_decl != NULL) {
    SgSymbol * sym = class_decl->search_for_symbol_from_symbol_table();
    if (sym == NULL) {
      std::cerr << "SgClassDeclaration cannot find symbol." << std::endl;
      return suggested_graph;
    }
    SgClassSymbol * class_sym = isSgClassSymbol(sym);
    if (class_sym == NULL) {
      std::cerr << "SgClassDeclaration not a VariableSymbol." << std::endl;
      return suggested_graph;
    }
    std::set<SgClassSymbol *>::iterator it_class = api->class_symbols.find(class_sym);
    if (it_class == api->class_symbols.end()) {
      std::cerr << "SgClassDeclaration not in API." << std::endl;
      return suggested_graph;
    }
    std::ostringstream oss; oss << "class_" << node;
    suggested_graph = suggested_graph->getSubgraph(oss.str());
    suggested_graph->filled = true;
    suggested_graph->color = "blue";
  }
  else if (method_decl != NULL) {
    SgSymbol * sym = method_decl->search_for_symbol_from_symbol_table();
    if (sym == NULL) {
      std::cerr << "SgMemberFunctionDeclaration cannot find symbol." << std::endl;
      return suggested_graph;
    }
    SgMemberFunctionSymbol * method_sym = isSgMemberFunctionSymbol(sym);
    if (method_sym == NULL) {
      std::cerr << "SgFunctionDeclaration not a MemberFunctionSymbol." << std::endl;
      return suggested_graph;
    }
    std::set<SgMemberFunctionSymbol *>::iterator it_method = api->member_function_symbols.find(method_sym);
    if (it_method == api->member_function_symbols.end()) {
      std::cerr << "SgMemberFunctionDeclaration not in API." << std::endl;
      return suggested_graph;
    }
    std::ostringstream oss; oss << "method_" << node;
    suggested_graph = suggested_graph->getSubgraph(oss.str());
    suggested_graph->filled = true;
    suggested_graph->color = "orange";
  }
  else if (func_decl != NULL) {
    SgSymbol * sym = func_decl->search_for_symbol_from_symbol_table();
    if (sym == NULL) {
      std::cerr << "SgFunctionDeclaration cannot find symbol." << std::endl;
      return suggested_graph;
    }
    SgFunctionSymbol * func_sym = isSgFunctionSymbol(sym);
    if (func_sym == NULL) {
      std::cerr << "SgFunctionDeclaration not a FunctionSymbol." << std::endl;
      return suggested_graph;
    }
    std::set<SgFunctionSymbol *>::iterator it_func = api->function_symbols.find(func_sym);
    if (it_func == api->function_symbols.end()) {
      std::cerr << "SgFunctionDeclaration not in API." << std::endl;
      return suggested_graph;
    }
    std::ostringstream oss; oss << "func_" << node;
    suggested_graph = suggested_graph->getSubgraph(oss.str());
    suggested_graph->filled = true;
    suggested_graph->color = "red";
  }
  return suggested_graph;
    }
};

}

}

int main(int argc, char ** argv) {
  SgProject * project = new SgProject::SgProject(argc, argv);

  MFB::Driver<MFB::Sage> driver(project);

  driver.add(boost::filesystem::path("loop.h"));
  driver.add(boost::filesystem::path("kernel.h"));
  driver.add(boost::filesystem::path("data.c"));
  driver.add(boost::filesystem::path("foo.c"));

  MFB::API2GraphViz::Traversal traversal(driver.getAPI());

  std::vector<SgSourceFile *> files = SageInterface::querySubTree<SgSourceFile>(project);
  std::vector<SgSourceFile *>::iterator it_file;
  for (it_file = files.begin(); it_file != files.end(); it_file++) {
    std::ofstream dot_file; std::ostringstream oss;
    oss << (*it_file)->get_sourceFileNameWithoutPath() << ".dot";
    dot_file.open(oss.str().c_str());
    traversal.traverseWithinFile(*it_file, traversal.makeAttribute());
    traversal.toDot(dot_file, "api");
    traversal.reset();
    dot_file.close();
  }

  return 0;
}

