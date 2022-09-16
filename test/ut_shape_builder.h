#include "../src/shape_builder.h"


class ShapeBuilderTest : public ::testing::Test {
protected:
  void SetUp() override {


  }

  void TearDown() override {

  }

};


TEST_F(ShapeBuilderTest, build_rectangle) {
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildRectangle(2.000,2.000);
    std::deque<Shape*> results = sb->getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (2.000, 2.000)", results[0]->info());
}

TEST_F(ShapeBuilderTest, build_ellipse) {
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildEllipse(4.000,3.000);
    std::deque<Shape*> results = sb->getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
}

TEST_F(ShapeBuilderTest, build_triangle) {
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb->getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST_F(ShapeBuilderTest, build_multi_simple_shapes) {
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildRectangle(2.000,2.000);
    sb->buildRectangle(2.000,2.000);
    sb->buildEllipse(4.000,3.000);
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb->getResult();

    ASSERT_EQ(4, results.size());
    EXPECT_EQ("Rectangle (2.000, 2.000)", results[0]->info());
    EXPECT_EQ("Rectangle (2.000, 2.000)", results[1]->info());
    EXPECT_EQ("Ellipse (4.000, 3.000)", results[2]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[3]->info());
}

TEST_F(ShapeBuilderTest, build_empty_compoundShape) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {}",result[0]->info());

}

TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_rectangle) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildRectangle(2.000,2.000);
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {Rectangle (2.000, 2.000)}",result[0]->info());

}

TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_ellipse) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildEllipse(4.000,3.000);
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {Ellipse (4.000, 3.000)}",result[0]->info());

}

TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_trinalge) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}",result[0]->info());

}

TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_a_empty_compoundShape) {
  ShapeBuilder * sb = new ShapeBuilder();;
  sb->buildCompoundShapeBegin();
  sb->buildCompoundShapeBegin();
  sb->buildCompoundShapeEnd();
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {Compound Shape {}}",result[0]->info());

}

TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_multi_simple_shapes ) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildRectangle(2.000,2.000);
  sb->buildEllipse(4.000,3.000);
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());
  ASSERT_EQ("Compound Shape {Rectangle (2.000, 2.000), Ellipse (4.000, 3.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}",result[0]->info());
}


TEST_F(ShapeBuilderTest, build_compoundShape_that_contains_multi_simple_shapes_and_a_empty_compoundShape ) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildCompoundShapeBegin();
  sb->buildRectangle(2.000,2.000);
  sb->buildEllipse(4.000,3.000);
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeBegin();
  sb->buildCompoundShapeEnd();
  sb->buildCompoundShapeEnd();
  std::deque<Shape*> result = sb->getResult();
  ASSERT_EQ(1,result.size());

}

TEST_F(ShapeBuilderTest, build_compoundShape_and_multi_shapes_at_same_time ) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildTriangle(0, 0, 0, -3, -4, 0); //0
  sb->buildTriangle(0, 0, 0, -3, -4, 0); //1
  sb->buildCompoundShapeBegin();        //2
  sb->buildRectangle(2.000,2.000);
  sb->buildEllipse(4.000,3.000);
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeEnd();
  sb->buildRectangle(2.000,2.000);  //3
  sb->buildCompoundShapeBegin();    //4
  sb->buildCompoundShapeEnd();
  sb->buildEllipse(4.000,3.000);
  std::deque<Shape*> result = sb->getResult();
  EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])",result[0]->info());
  EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])",result[1]->info());
  EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Ellipse (4.000, 3.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}",result[2]->info());
  EXPECT_EQ("Rectangle (2.000, 2.000)",result[3]->info());
  EXPECT_EQ("Compound Shape {}",result[4]->info());
  EXPECT_EQ("Ellipse (4.000, 3.000)",result[5]->info());
}


TEST_F(ShapeBuilderTest, build_level_3_compoundShape_and_multi_shapes_at_same_time ) {
  ShapeBuilder * sb = new ShapeBuilder();
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeBegin();
  sb->buildRectangle(2.000,2.000);
  sb->buildEllipse(4.000,3.000);
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeBegin();
  sb->buildEllipse(4.000,3.000);
  sb->buildTriangle(0, 0, 0, -3, -4, 0);
  sb->buildCompoundShapeEnd();
  sb->buildCompoundShapeEnd();
  sb->buildRectangle(2.000,2.000);
  sb->buildCompoundShapeBegin();
  sb->buildCompoundShapeEnd();
  sb->buildEllipse(4.000,3.000);
  sb->buildEllipse(4.000,3.000);
  std::deque<Shape*> result = sb->getResult();
  EXPECT_EQ(6,result.size());
  EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])",result[0]->info());
  EXPECT_EQ("Compound Shape {Rectangle (2.000, 2.000), Ellipse (4.000, 3.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Compound Shape {Ellipse (4.000, 3.000), Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}}",result[1]->info());
  EXPECT_EQ("Rectangle (2.000, 2.000)",result[2]->info());
  EXPECT_EQ("Compound Shape {}",result[3]->info());
  EXPECT_EQ("Ellipse (4.000, 3.000)",result[4]->info());
  EXPECT_EQ("Ellipse (4.000, 3.000)",result[5]->info());
}