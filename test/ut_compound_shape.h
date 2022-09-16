#include "../src/shape.h"
#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/two_dimensional_coordinate.h"
#include <list>
#include <vector>
#include <exception>
class CompoundShapeTest : public ::testing::Test {
protected:
  void SetUp() override {

    r34 = new Rectangle("1",3, 4);
    r22 = new Rectangle("2",2, 2);
    e43 = new Ellipse("3",4, 3);
    r66 = new Rectangle("5",6, 6);
    r78 = new Rectangle("6",7, 8);
    e98 = new Ellipse("7",9, 8);
    e65 = new Ellipse("8",6, 5);
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    t345 = new Triangle("4",triangleVector);
    //shapeVector = new std::list<Shape *>;
    shapeVector.push_back(e43);
    shapeVector.push_back(r34);
    //shapeVector->push_back(r22);
    shapeVector.push_back(t345);

  }

  void TearDown() override {
      delete r34;
      delete r22;
      delete e43;
      delete t345;
      delete r66;
      delete r78;
      delete e98;
      delete e65;
  }

  Shape * r34;
  Shape * r22;
  Shape * t345;
  Shape * e43;

  Shape * r66;
  Shape * r78;
  Shape * e65;
  Shape * e98;

  std::vector<TwoDimensionalCoordinate*> triangleVector;
  std::list<Shape *> shapeVector ;
};

TEST_F(CompoundShapeTest, TestCompoundShapeColor){
  //std::cout << shapeVector << std::endl;
  Shape * mbox = new CompoundShape("7",shapeVector);

  ASSERT_EQ("transparent", mbox->color());
}

TEST_F(CompoundShapeTest, CreateCompoundShape){
  //std::cout << shapeVector << std::endl;
  CompoundShape mbox("4", shapeVector);
  ASSERT_EQ(3, mbox.getNumberOfComponents());
}

TEST_F(CompoundShapeTest, CompoundShapeArea){
  CompoundShape mbox("5", shapeVector);
  ASSERT_NEAR(55.699, mbox.area(),0.001);
}

TEST_F(CompoundShapeTest, CompoundShapePermiter){
  CompoundShape mbox("5", shapeVector);
  ASSERT_NEAR(48.849, mbox.perimeter(),0.001);
}

TEST_F(CompoundShapeTest, CompoundShapeInfo){
  CompoundShape mbox("5", shapeVector);
  ASSERT_EQ("Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", mbox.info());
}

TEST_F(CompoundShapeTest, CompoundShapeAdd){
  CompoundShape mbox("5", shapeVector);
  mbox.addShape(r22);
  ASSERT_EQ(4,mbox.getNumberOfComponents());
}

TEST_F(CompoundShapeTest, CompoundShapeGetById){
  CompoundShape mbox("5", shapeVector);
  ASSERT_EQ(e43,mbox.getShapeById("3"));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteById){
  CompoundShape mbox("5", shapeVector);
  mbox.deleteShapeById("3");
  ASSERT_EQ(2,mbox.getNumberOfComponents());
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteByIdExcpetion){
  CompoundShape mbox("5", shapeVector);
  try{
    mbox.deleteShapeById("6");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Expected delete shape but shape not found",e);
  }
}

TEST_F(CompoundShapeTest, CompoundShapeGetByIdExcpetion){
  CompoundShape mbox("5", shapeVector);
  try{
    mbox.getShapeById("6");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Expected get shape but shape not found",e);
  }
}

TEST_F(CompoundShapeTest, CompoundShapeGetById3Layer){

  Shape * mbox = new CompoundShape("9", shapeVector);
  shapeVector.clear();
  shapeVector.push_back(r66);
  shapeVector.push_back(r78);
  Shape * mbox2 = new CompoundShape("10", shapeVector);

  shapeVector.clear();
  shapeVector.push_back(e98);
  shapeVector.push_back(e65);

  Shape * mbox3 = new CompoundShape("11", shapeVector);
  mbox2->addShape(mbox3);
  mbox->addShape(mbox2);

  EXPECT_EQ(mbox2,mbox->getShapeById("10"));
  EXPECT_EQ(mbox3,mbox->getShapeById("11"));
  EXPECT_EQ(e98,mbox->getShapeById("7"));
  EXPECT_EQ(e65,mbox->getShapeById("8"));

  try{
    EXPECT_EQ(r22,mbox->getShapeById("112"));
  }catch(std::string e){
    ASSERT_EQ("Expected get shape but shape not found",e);
  }
}


TEST_F(CompoundShapeTest, DeleteShapeById_Lv3TreeStruct){
  Shape * mbox = new CompoundShape("9", shapeVector);
  shapeVector.clear();
  shapeVector.push_back(r66);
  shapeVector.push_back(r78);
  Shape * mbox2 = new CompoundShape("10", shapeVector);

  shapeVector.clear();
  shapeVector.push_back(e98);
  shapeVector.push_back(e65);
  Shape * mbox3 = new CompoundShape("11", shapeVector);

  mbox2->addShape(mbox3);
  mbox->addShape(mbox2);
  EXPECT_EQ(e98,mbox->getShapeById("7"));

  try{
    mbox->deleteShapeById("7");
    mbox->deleteShapeById("7");
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Expected delete shape but shape not found",e);
  }
}

/*TEST_F(CompoundShapeTest, compoundShapeConstructorException){
  shapeVector.clear();
  try{
    Shape * mbox = new CompoundShape("9", shapeVector);
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("This is not a compound shape!",e);
  }
}*/

TEST_F(CompoundShapeTest, CompoundShapeTypeTest){
  Shape * mbox = new CompoundShape("9", shapeVector);
  ASSERT_EQ("Compound Shape",mbox->type());
}
