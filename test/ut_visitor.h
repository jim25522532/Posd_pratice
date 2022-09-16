#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/visitor.h"
#include "../src/area_visitor.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/compound_shape.h"
#include <list>
#include <string>
#include <vector>
#include "../src/info_visitor.h"
class VisitorTest : public ::testing::Test {
protected:
  void SetUp() override {
    r34 = new Rectangle(3, 4);
    r66 = new Rectangle("5",6, 6);
    r78 = new Rectangle("6",7, 8);

    e43 = new Ellipse(3.712, 2.556);

    e98 = new Ellipse("7",9, 8);
    e65 = new Ellipse("8",6, 5);

    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    t345 = new Triangle(triangleVector);
    shapeVector.push_back(r34);
    shapeVector.push_back(e43);
    shapeVector.push_back(t345);
    mbox = new CompoundShape("1", shapeVector);
    sv = new AreaVisitor();
    av = new AreaVisitor();
    iv = new InfoVisitor();
    iv2 = new InfoVisitor();

  }

  void TearDown() override {
    delete r34;
    delete e43;
    delete t345;
    delete mbox;
    delete sv;
    delete iv;
    delete av;
    delete iv2;
    delete r66;
    delete r78;

    delete e98;
    delete e65;
  }

  Shape * r34;
  Shape * r66;
  Shape * r78;

  Shape * e43;
  Shape * e98;
  Shape * e65;

  Shape * t345;
  Shape * mbox;
  std::list<Shape *> shapeVector ;
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  Visitor * sv;
  Visitor * iv;
  AreaVisitor * av;
  InfoVisitor * iv2;

};

TEST_F(VisitorTest,visitRectangleAreaWithPolymorphism){
  r34->accept(sv);
  ASSERT_EQ(12.0,(dynamic_cast<AreaVisitor*>(sv))->area());
}


TEST_F(VisitorTest,visitEllipseleAreaWithPolymorphism){
  e43->accept(sv);
  ASSERT_NEAR(29.807,(dynamic_cast<AreaVisitor*>(sv))->area(),0.001);
}

TEST_F(VisitorTest,visitTriangleleAreaWithPolymorphism){
  t345->accept(sv);
  ASSERT_NEAR(6.0,(dynamic_cast<AreaVisitor*>(sv))->area(),0.001);
}

TEST_F(VisitorTest,visitCompoundAreaWithPolymorphism){
  mbox->accept(sv);
  ASSERT_NEAR(47.807, (dynamic_cast<AreaVisitor*>(sv))->area(),0.001);
}

TEST_F(VisitorTest,visitRectangleAreaBaseTypeTest){
  r34->accept(av);
  ASSERT_EQ(12.0,av->area());
}


TEST_F(VisitorTest,visitEllipseleAreaBaseTypeTest){
  e43->accept(av);
  ASSERT_NEAR(29.807,av->area(),0.001);
}

TEST_F(VisitorTest,visitTriangleleAreaBaseTypeTest){
  t345->accept(av);
  ASSERT_NEAR(6.0,av->area(),0.001);
}

TEST_F(VisitorTest,visitCompoundAreaBaseTypeTest){
  mbox->accept(av);
  ASSERT_NEAR(47.807, av->area(),0.001);
}

TEST_F(VisitorTest,rectangleInfoVisitorTest){
  r34->accept(iv);
  ASSERT_EQ("Rectangle (3.000, 4.000)",(dynamic_cast<InfoVisitor*>(iv))->info());
}

TEST_F(VisitorTest,ellipseInfoVisitorTest){
  e43->accept(iv);
  ASSERT_EQ("Ellipse (3.712, 2.556)",(dynamic_cast<InfoVisitor*>(iv))->info());
}

TEST_F(VisitorTest,triangleInfoVisitorTest){
  t345->accept(iv);
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", (dynamic_cast<InfoVisitor*>(iv))->info());
}

TEST_F(VisitorTest,compoundShapeInfoVisitorTest){
  mbox->accept(iv);
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (3.712, 2.556), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", (dynamic_cast<InfoVisitor*>(iv))->info());
}

TEST_F(VisitorTest,visitRectangleInfoBaseTypeTest){
  r34->accept(iv2);
  ASSERT_EQ("Rectangle (3.000, 4.000)",iv2->info());
}

TEST_F(VisitorTest,visitEllipseInfoBaseTypeTest){
  e43->accept(iv2);
  ASSERT_EQ("Ellipse (3.712, 2.556)",iv2->info());
}

TEST_F(VisitorTest,visitTriangleInfoBaseTypeTest){
  t345->accept(iv2);
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", iv2->info());
}

TEST_F(VisitorTest,visitCompoundInfoBaseTypeTest){
  mbox->accept(iv2);
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Ellipse (3.712, 2.556), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", iv2->info());
}

TEST_F(VisitorTest,compound_shape_info_level_3_tree_structure){
  shapeVector.clear();
  shapeVector.push_back(r34);
  Shape * mbox1 = new CompoundShape("11", shapeVector);
  shapeVector.clear();
  shapeVector.push_back(r66);
  Shape * mbox2 = new CompoundShape("12", shapeVector);

  shapeVector.clear();
  shapeVector.push_back(e98);

  Shape * mbox3 = new CompoundShape("13", shapeVector);
  mbox2->addShape(mbox3);
  mbox1->addShape(mbox2);

  mbox1->accept(iv2);
  EXPECT_EQ("Compound Shape {Rectangle (3.000, 4.000), Compound Shape {Rectangle (6.000, 6.000), Compound Shape {Ellipse (9.000, 8.000)}}}", iv2->info());
}

TEST_F(VisitorTest,compound_shape_area_level_3_tree_structure){
  shapeVector.clear();
  shapeVector.push_back(r34);
  Shape * mbox1 = new CompoundShape("11", shapeVector);
  shapeVector.clear();
  shapeVector.push_back(r66);
  Shape * mbox2 = new CompoundShape("12", shapeVector);

  shapeVector.clear();
  shapeVector.push_back(e98);

  Shape * mbox3 = new CompoundShape("13", shapeVector);
  mbox2->addShape(mbox3);
  mbox1->addShape(mbox2);

  mbox1->accept(av);
  ASSERT_NEAR(274.194, av->area(),0.001);
}
