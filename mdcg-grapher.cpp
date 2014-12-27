
#include "MFB/Sage/driver.hpp"
#include "MFB/Sage/api.hpp"

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
    Traversal(const Model::model_t & model_) : AST2GraphViz::Cluster(), model(model_) {}
    virtual ~Traversal() {}

  protected:
    const Model::model_t & model;

    virtual void editNodeDesc(
                   SgNode * node,
                   const UserInherited & inherited_attr, const UserSynthesized & synthetized_attr,
                   AST2GraphViz::NodeDesc & node_desc
                 ) {
  // TODO
    }

    virtual graph_t * getGraphInherited(
                   graph_t * suggested_graph, SgNode * node, SgNode * parent,
                   const UserInheritedAttr & inherited_attr
                 ) {
  // TODO
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

int main(int argc, char ** argv) {
  SgProject * project = new SgProject::SgProject(argc, argv);

  MFB::Driver<MFB::Sage> driver(project);

  MDCG::ModelBuilder model_builder(driver);

  unsigned model_id = model_builder.create();

  model_builder.add(model_id, "loop",   "", "h");
  model_builder.add(model_id, "kernel", "", "h");
  model_builder.add(model_id, "data",   "", "c");
  model_builder.add(model_id, "foo",    "", "c");

  MFB::API2GraphViz::Traversal traversal(model_builder.get(model_id));

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

