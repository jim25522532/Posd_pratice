#include "../src/triangle.h"
#include "../src/two_dimensional_coordinate.h"
//test driven first not implement code first
//用ASSERT_TRUE不好,蓋房子要搭鷹架 ,軟體的鷹架即是測試 call "scafolding"
TEST(Shapes, CreateTriangle){
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  try{
    //vector not enough 3
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    Triangle triangle("1",triangleVector);
    FAIL();
  }catch(std::string e) {

    ASSERT_EQ("This is not a triangle!", e);
  }
  try{
    //測0 0 0 不符合規定的三角形
    triangleVector.clear();
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    Triangle triangle("1",triangleVector);
    ASSERT_NEAR(0.0,triangle.area(),0.001);
    FAIL();
  }catch(std::string e) {

    ASSERT_EQ("This is not a triangle!", e);
  }

  triangleVector.clear();
  triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
  triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
  triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
  Triangle triangle("1",triangleVector);

  ASSERT_NEAR(6,triangle.area(),0.001);
  ASSERT_NEAR(12.0,triangle.perimeter(),0.001);
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", triangle.info());

}
//做完一個測試,就做個code review 做code view讓程式更好


TEST(Shapes, InvalidOpeartionTriangleAddShape){
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  try{
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle t345("1",triangleVector);

    Shape * t456 = new Triangle("2",triangleVector);
    t345.addShape(t456);
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can add shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionTriangleDeleteShape){
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  try{
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle t345("1",triangleVector);

    t345.deleteShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can delete shape!", e);
  }
}

TEST(Shapes, InvalidOpeartionTriangleGetId){
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  try{
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle t345("1",triangleVector);
    t345.getShapeById("2");
    FAIL();
  }catch(std::string e) {
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}


TEST(Shapes, TriangleTypeTest){
  std::vector<TwoDimensionalCoordinate*> triangleVector;
  triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
  triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
  triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
  Triangle t345("1",triangleVector);

  ASSERT_EQ("Triangle",t345.type());
}
