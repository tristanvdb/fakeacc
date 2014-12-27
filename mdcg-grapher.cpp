
#include "MFB/Sage/driver.hpp"
#include "MFB/Sage/api.hpp"

#include "MDCG/model-builder.hpp"
#include "MDCG/model.hpp"

#include "AST2GraphViz/cluster.hpp"

#include "rose.h"

#include <cassert>

namespace MDCG {

namespace Model2GraphViz {

class Traversal : public AST2GraphViz::Cluster {
  public:
    typedef AST2GraphViz::GraphVizAttr<AST2GraphViz::EmptyAttr>::Inherited   Inherited;
    typedef AST2GraphViz::GraphVizAttr<AST2GraphViz::EmptyAttr>::Synthesized Synthesized;
    typedef AST2GraphViz::EmptyAttr::Inherited   UserInherited;
    typedef AST2GraphViz::EmptyAttr::Synthesized UserSynthesized;

    typedef AST2GraphViz::GraphVizTraversal<AST2GraphViz::EmptyAttr>::graph_t graph_t;

  public:
    Traversal() : AST2GraphViz::Cluster() {}
    virtual ~Traversal() {}

  protected:
    virtual void editNodeDesc(
                   SgNode * node,
                   const UserInherited & inherited_attr, const UserSynthesized & synthetized_attr,
                   AST2GraphViz::NodeDesc & node_desc
                 ) {
  Cluster::editNodeDesc(node, inherited_attr, synthetized_attr, node_desc);
  // TODO
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
  // TODO
  return suggested_graph;
    }
};

}

}

SgDeclarationStatement * getTypeDecl(MDCG::Model::type_t type, std::string & type_chain) {
  assert(type != NULL);
  while (  type != NULL &&
           type->node->kind != MDCG::Model::node_t<MDCG::Model::e_model_type>::e_class_type &&
           type->node->kind != MDCG::Model::node_t<MDCG::Model::e_model_type>::e_enum_type
        ) {
    switch (type->node->kind) {
      case MDCG::Model::node_t<MDCG::Model::e_model_type>::e_array_type:
        assert(type->node->base_type != NULL);
        type = type->node->base_type;
        type_chain += "array of ";
        break;
      case MDCG::Model::node_t<MDCG::Model::e_model_type>::e_pointer_type:
        assert(type->node->base_type != NULL);
        type = type->node->base_type;
        type_chain += "pointer on ";
        break;
      case MDCG::Model::node_t<MDCG::Model::e_model_type>::e_reference_type:
        assert(type->node->base_type != NULL);
        type = type->node->base_type;
        type_chain += "reference on ";
        break;
      case MDCG::Model::node_t<MDCG::Model::e_model_type>::e_typedef_type:
        assert(type->node->base_type != NULL);
        type = type->node->base_type;
        type_chain += "typedef of ";
        break;
      default:
        type = NULL;
        break;
    }
  }

  if (type == NULL) return NULL;

  assert(type->node->kind != MDCG::Model::node_t<MDCG::Model::e_model_type>::e_class_type ||
         type->node->kind != MDCG::Model::node_t<MDCG::Model::e_model_type>::e_enum_type);

  SgDeclarationStatement * decl = NULL;
  if (type->node->kind == MDCG::Model::node_t<MDCG::Model::e_model_type>::e_class_type) {
    SgClassSymbol * class_sym = type->node->base_class->node->symbol;
    assert(class_sym != NULL);
    decl = class_sym->get_declaration();
    assert(decl != NULL);
  }
  else if (type->node->kind == MDCG::Model::node_t<MDCG::Model::e_model_type>::e_enum_type) {
    SgEnumSymbol * enum_sym = type->node->enum_symbol;
    assert(enum_sym != NULL);
    decl = enum_sym->get_declaration();
    assert(decl != NULL);
  }
  assert(decl != NULL);
  decl = decl->get_definingDeclaration();
  assert(decl != NULL);

  return decl;
}

void addTypeEdge(SgNode * node, MDCG::Model::type_t type, MDCG::Model2GraphViz::Traversal & traversal, std::string label = std::string()) {
  std::string type_chain;
  SgDeclarationStatement * decl = getTypeDecl(type, type_chain);

  if (decl == NULL) return;

  AST2GraphViz::EdgeDesc edge_desc;
    edge_desc.label = "type";
    edge_desc.color = "blue";
    edge_desc.constraint = true;

  if (label.length() != 0)
    edge_desc.label = label + " " + edge_desc.label;
  if (type_chain.length() != 0)
    edge_desc.label += " (" + type_chain.substr(0, type_chain.length()-1) + ")";

  traversal.addEdge(node, decl, edge_desc);
}

int main(int argc, char ** argv) {
  SgProject * project = new SgProject::SgProject(argc, argv);

  MFB::Driver<MFB::Sage> driver(project);

  MDCG::ModelBuilder model_builder(driver);

  unsigned model_id = model_builder.create();

  model_builder.add(model_id, "loop",   ".", "h");
  model_builder.add(model_id, "kernel", ".", "h");
//  model_builder.add(model_id, "data",   ".", "c");
//  model_builder.add(model_id, "foo",    ".", "c");

  MDCG::Model2GraphViz::Traversal traversal;

  std::vector<SgSourceFile *> files = SageInterface::querySubTree<SgSourceFile>(project);
  std::vector<SgSourceFile *>::iterator it_file;
  for (it_file = files.begin(); it_file != files.end(); it_file++) {
    std::string filename = (*it_file)->get_sourceFileNameWithoutPath();
    std::cerr << "filename = " << filename << ", ext = " << filename.substr(filename.length()-2) << std::endl;
    if (filename.substr(filename.length()-2) == ".h")
      traversal.traverseWithinFile(*it_file, traversal.makeAttribute());
  }

  const MDCG::Model::model_t & model = model_builder.get(model_id);

  std::vector<MDCG::Model::variable_t>::const_iterator it_variable;
  for (it_variable = model.variables.begin(); it_variable != model.variables.end(); it_variable++) {
    SgVariableSymbol * var_sym = (*it_variable)->node->symbol;
    assert(var_sym != NULL);
    SgInitializedName * init_name = var_sym->get_declaration();
    assert(init_name != NULL);

    addTypeEdge(init_name, (*it_variable)->node->type, traversal);
  }
  std::vector<MDCG::Model::field_t>::const_iterator it_field;
  for (it_field = model.fields.begin(); it_field != model.fields.end(); it_field++) {
    SgVariableSymbol * field_sym = (*it_field)->node->symbol;
    assert(field_sym != NULL);
    SgInitializedName * init_name = field_sym->get_declaration();
    assert(init_name != NULL);

    addTypeEdge(init_name, (*it_field)->node->type, traversal);
  }
  std::vector<MDCG::Model::function_t>::const_iterator it_function;
  for (it_function = model.functions.begin(); it_function != model.functions.end(); it_function++) {
    SgFunctionSymbol * func_sym = (*it_function)->node->symbol;
    assert(func_sym != NULL);
    SgFunctionDeclaration * func_decl = func_sym->get_declaration();
    assert(func_decl != NULL);

    addTypeEdge(func_decl, (*it_function)->node->return_type, traversal, "return");

    std::vector<MDCG::Model::type_t>::iterator it_arg_type;
    unsigned arg_cnt = 0;
    for (it_arg_type = (*it_function)->node->args_types.begin(); it_arg_type != (*it_function)->node->args_types.end(); it_arg_type++) {
      std::ostringstream oss; oss << "arg[" << arg_cnt++ << "]";
      addTypeEdge(func_decl, *it_arg_type, traversal, oss.str());
    }
  }
  std::vector<MDCG::Model::class_t>::const_iterator it_class;
  for (it_class = model.classes.begin(); it_class != model.classes.end(); it_class++) {
    SgClassSymbol * class_sym = (*it_class)->node->symbol;
    assert(class_sym != NULL);
    SgClassDeclaration * class_decl = class_sym->get_declaration();
    assert(class_decl != NULL);
    class_decl = isSgClassDeclaration(class_decl->get_definingDeclaration());
    assert(class_decl != NULL);

    std::vector<MDCG::Model::type_t>::iterator it_type;
    for (it_type = (*it_class)->scope->type_children.begin(); it_type != (*it_class)->scope->type_children.end(); it_type++) {
      addTypeEdge(class_decl, *it_type, traversal);
    }
    std::vector<MDCG::Model::class_t>::iterator it_class_;
    for (it_class_ = (*it_class)->scope->class_children.begin(); it_class_ != (*it_class)->scope->class_children.end(); it_class_++) {
      SgClassSymbol * class_sym_ = (*it_class_)->node->symbol;
      assert(class_sym_ != NULL);
      SgClassDeclaration * class_decl_ = class_sym_->get_declaration();
      assert(class_decl_ != NULL);
      class_decl_ = isSgClassDeclaration(class_decl_->get_definingDeclaration());
      assert(class_decl_ != NULL);

      AST2GraphViz::EdgeDesc edge_desc;
        edge_desc.label = "class";
        edge_desc.color = "red";
        edge_desc.constraint = true;

      traversal.addEdge(class_decl, class_decl_, edge_desc);
    }
    std::vector<MDCG::Model::field_t>::iterator it_field;
    unsigned field_cnt = 0;
    for (it_field = (*it_class)->scope->field_children.begin(); it_field != (*it_class)->scope->field_children.end(); it_field++) {
      SgVariableSymbol * field_sym = (*it_field)->node->symbol;
      assert(field_sym != NULL);
      SgInitializedName * init_name = field_sym->get_declaration();
      assert(init_name != NULL);

      std::ostringstream oss; oss << "field[" << field_cnt++ << "]";

      AST2GraphViz::EdgeDesc edge_desc;
        edge_desc.label = oss.str();
        edge_desc.color = "green";
        edge_desc.constraint = true;

      traversal.addEdge(class_decl, init_name, edge_desc);
    }
  }

  std::ofstream dot_file;
  dot_file.open("mdcg.dot");
  traversal.toDot(dot_file, "model");
  dot_file.close();

  dot_file.open("model.dot");
  model.toDot(dot_file);
  dot_file.close();

  dot_file.open("model-function.dot");
  model.toDot(dot_file, "", true, false, false);
  dot_file.close();

  dot_file.open("model-variable.dot");
  model.toDot(dot_file, "", false, true, false);
  dot_file.close();

  dot_file.open("model-class.dot");
  model.toDot(dot_file, "", false, false, true);
  dot_file.close();

  return 0;
}

