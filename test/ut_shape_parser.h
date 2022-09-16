#include "../src/shape_parser.h"
#include "../src/shape.h"
#include <deque>

class ShapeParserTest : public ::testing::Test {
protected:
  void SetUp() override {


  }

  void TearDown() override {

  }

};


TEST_F(ShapeParserTest, parser_triangle) {
    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST_F(ShapeParserTest, rectangleParser){
  ShapeParser sp("Rectangle (2.000, 2.000)");
  sp.parser();
  std::deque<Shape*> results = sp.getResult();
  ASSERT_EQ(1, results.size());
  ASSERT_EQ("Rectangle (2.000, 2.000)", results[0]->info());
}


TEST_F(ShapeParserTest, ellipseParser){
  ShapeParser sp("Ellipse (4.000, 3.000)");
  sp.parser();
  std::deque<Shape*> results = sp.getResult();
  ASSERT_EQ(1, results.size());
  ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
}


TEST_F(ShapeParserTest, parser_multi_simple_shapes) {

    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

}


TEST_F(ShapeParserTest, parser_empty_compoundShape) {

    ShapeParser sp("CompoundShape {}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_rectangle) {

    ShapeParser sp("CompoundShape {Rectangle (3.000, 4.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Rectangle (3.000, 4.000)}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_ellipse) {

    ShapeParser sp("CompoundShape {Ellipse (4.200, 3.700)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Ellipse (4.200, 3.700)}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_trinalge) {

    ShapeParser sp("CompoundShape {Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_multi_simple_shapes) {

    ShapeParser sp("CompoundShape {Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), Ellipse (4.200, 3.700), Rectangle (3.000, 4.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Ellipse (4.200, 3.700), Rectangle (3.000, 4.000)}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_multi_simple_shapes_with_one_shape_contain_invalid_argument_that_should_be_ignored) {

    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Ellipse (4.200, 3.700, 12.502), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[1]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[2]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_a_empty_compoundShape) {

    ShapeParser sp("CompoundShape {CompoundShape {}}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    EXPECT_EQ("Compound Shape {Compound Shape {}}", results[0]->info());
}

TEST_F(ShapeParserTest, parser_compoundShape_that_contains_multi_simple_shapes_and_a_empty_compoundShape) {

    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), CompoundShape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)}, Rectangle (3.000, 4.000), CompoundShape {}, Ellipse (4.200, 3.700)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(5, results.size());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}


TEST_F(ShapeParserTest, parser_compoundShape_and_multi_shapes_at_same_time ) {

    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), CompoundShape {Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)}, Rectangle (3.000, 4.000), CompoundShape {}, Ellipse (4.200, 3.700)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(5, results.size());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}