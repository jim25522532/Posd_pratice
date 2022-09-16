#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/shape_iterator.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/utility.h"
class UtUlityTest : public ::testing::Test {
protected:
  void SetUp() override {

    r34 = new Rectangle("4",2, 2);
    e43 = new Ellipse("3",3, 1);
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    t345 = new Triangle("2",triangleVector,"YELLOW");
    shapeVector.push_back(t345);
    mbox2 = new CompoundShape("1",shapeVector);
    //mbox2->addShape(t345);
    shapeVector.clear();
    shapeVector.push_back(e43);
    shapeVector.push_back(r34);
    mbox = new CompoundShape("0",shapeVector);
    mbox->addShape(mbox2);
  }

  void TearDown() override {
    delete r34;
    delete e43;
    delete t345;
    delete mbox;
    delete mbox2;
  }

  Shape * r34;
  Shape * e43;
  Shape * t345;

  Shape * mbox;
  Shape * mbox2;
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  std::list<Shape *> shapeVector ;
  std::deque<Shape *> dq;
};

TEST_F(UtUlityTest,createUtUlityTest){

  Shape * temp = getShapeById(mbox,"2");
  ASSERT_EQ(t345,temp);
}

TEST_F(UtUlityTest,exception_for_rectangle_get_shape_by_id){
  try{
    getShapeById(r34,"4");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!",e);
  }
}

TEST_F(UtUlityTest,exception_for_rectangle_filter_shape){
  try{
    dq = filterShape(r34, AreaFilter(50, 1));
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can filter shape!",e);
  }
}

TEST_F(UtUlityTest,exception_for_ellipse_get_shape_by_id){
  try{
    getShapeById(e43,"5");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!",e);
  }
}

TEST_F(UtUlityTest,exception_for_ellipse_filter_shape){
  try{
    dq = filterShape(e43, AreaFilter(50, 1));
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can filter shape!",e);
  }
}

TEST_F(UtUlityTest,exception_for_triangle_get_shape_by_id){
  try{
    getShapeById(t345,"6");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!",e);
  }
}

TEST_F(UtUlityTest,exception_for_triangle_filter_shape){
  try{
    dq = filterShape(t345, AreaFilter(50, 1));
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can filter shape!",e);
  }
}

TEST_F(UtUlityTest,compound_shape_get_shape_by_id){

  Shape * temp = getShapeById(mbox,"2");
  ASSERT_EQ(t345,temp);
}

TEST_F(UtUlityTest,compound_shape_filter_shape_by_area){

    dq = filterShape(mbox, AreaFilter(50, 1));
    ASSERT_EQ(e43,dq[0]);
    ASSERT_EQ(r34,dq[1]);
    ASSERT_EQ(mbox2,dq[2]);
    ASSERT_EQ(t345,dq[3]);
}

TEST_F(UtUlityTest,compound_shape_filter_shape_by_perimeter){

    dq = filterShape(mbox, PerimeterFilter(50, 1));
    ASSERT_EQ(e43,dq[0]);
    ASSERT_EQ(r34,dq[1]);
    ASSERT_EQ(mbox2,dq[2]);
    ASSERT_EQ(t345,dq[3]);
}

TEST_F(UtUlityTest,compound_shape_filter_shape_by_type){

    dq = filterShape(mbox, TypeFilter("Triangle"));
    ASSERT_EQ(t345,dq[0]);
}

TEST_F(UtUlityTest,compound_shape_filter_shape_by_color){
    try{
      dq = filterShape(t345, ColorFilter("YELLOW"));
      FAIL();
    }catch(std::string e){
      ASSERT_EQ("Only compound shape can filter shape!",e);
    }
}

TEST_F(UtUlityTest,UtUlityExceptionTest){
  try{
    Shape * temp = getShapeById(mbox,"0");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Expected get shape but shape not found",e);
  }

}


TEST_F(UtUlityTest,UtUlitygetByExceptionTest){
  try{
    Shape * temp = getShapeById(r34,"0");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!",e);
  }

}
