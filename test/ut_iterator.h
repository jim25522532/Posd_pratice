#include "../src/shape.h"
#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/shape_iterator.h"
#include "../src/iterator.h"
#include <list>
#include <string>
class IteratorTest : public ::testing::Test {
protected:
  void SetUp() override {
    r34 = new Rectangle("1",3, 4);
    r22 = new Rectangle("2",2, 2);
    shapeVector.push_back(r34);
    shapeVector.push_back(r22);
    mbox = new CompoundShape("0",shapeVector);

  }

  void TearDown() override {
    delete r34;
    delete r22;
    delete mbox;

  }

  Shape * r34;
  Shape * r22;
  Shape * mbox;
  std::list<Shape *> shapeVector ;
};

TEST_F(IteratorTest,createIteratorTest){
  Iterator * it = mbox->createIterator();
  ASSERT_EQ(r34,it->currentItem());
}

TEST_F(IteratorTest,IteratorNextTest){
  Iterator * it = mbox->createIterator();
  it->next();
  ASSERT_EQ(r22,it->currentItem());
}

TEST_F(IteratorTest,IteratorisDoneTest){
  Iterator * it = mbox->createIterator();
  it->next();
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest,IteratorisFirstTest){
  Iterator * it = mbox->createIterator();
  it->next();
  it->next();
  it->first();
  ASSERT_EQ(r34,it->currentItem());
}

TEST_F(IteratorTest,IteratorNextExceptionTest){
  Iterator * it = mbox->createIterator();
  it->next();
  it->next();
  try{
    it->next();
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("Moving past the end!",e);
  }
}
