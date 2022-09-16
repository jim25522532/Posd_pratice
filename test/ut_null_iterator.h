#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/triangle.h"
class NullIteratorTest : public ::testing::Test {
protected:
  void SetUp() override {
    r34 = new Rectangle("1",3, 4);
    e54 = new Ellipse("2",5,4);
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    t345 = new Triangle("4",triangleVector);
  }

  void TearDown() override {
    delete r34;
    delete e54;
  }
  Shape * r34;
  Shape * e54;
  Shape * t345;
  std::vector<TwoDimensionalCoordinate*> triangleVector;
};

TEST_F(NullIteratorTest,createNullIteratorTest){
  Iterator * it = r34->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NullIteratorTest,exception_for_rectangle_iterate_first){
   Iterator * it = r34->createIterator();
  try{
    it->first();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_rectangle_iterate_next){
   Iterator * it = r34->createIterator();
  try{
    it->next();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_rectangle_iterate_current_item){
   Iterator * it = r34->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}


TEST_F(NullIteratorTest,ellipse_iterate_is_done){
  Iterator * it = e54->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NullIteratorTest,exception_for_ellipse_iterate_first){
   Iterator * it = e54->createIterator();
  try{
    it->first();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_ellipse_iterate_next){
   Iterator * it = e54->createIterator();
  try{
    it->next();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_ellipse_iterate_current_item){
   Iterator * it = e54->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,triangle_iterate_is_done){
  Iterator * it = t345->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NullIteratorTest,exception_for_triangle_iterate_first){
   Iterator * it = t345->createIterator();
  try{
    it->first();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_triangle_iterate_next){
   Iterator * it = t345->createIterator();
  try{
    it->next();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}

TEST_F(NullIteratorTest,exception_for_triangle_iterate_current_item){
   Iterator * it = t345->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!",e);
  }
}
