#include "../src/folder.h"
#include "../src/app.h"
#include "../src/utility.h"

class UtlilityTestSuite: public testing::Test {
    protected:
    virtual void SetUp() {
        firefox = new App("1", "firefox", 62.38);
        twitter = new App("2", "twitter", 1.16);
        instagram = new App("3", "instagram", 77.77);
        netflix = new App("4", "netflix", 495.32);
        foodpanda = new App("5", "foodpanda", 14.796);
        messenger = new App("6", "messenger", 79.25);

        favorite = new Folder("7", "favorite");
        common = new Folder("8", "common");
        community = new Folder("9", "community");
        trash = new Folder("10", "trash");
        addNodes();
    }

    void addNodes() {
        favorite->addNode(firefox);
        favorite->addNode(twitter);
        favorite->addNode(common);
        common->addNode(instagram);
        common->addNode(community);
        common->addNode(netflix);
        community->addNode(foodpanda);
        community->addNode(messenger);
        community->addNode(trash);

    }

    Node* firefox;
    Node* twitter;
    Node* instagram;
    Node* netflix;
    Node* foodpanda;
    Node* messenger;

    Node* favorite;
    Node* common;
    Node* community;
    Node* trash;
};

TEST_F(UtlilityTestSuite, exception_for_app_filter_by_size) {
    try {
        filterNode(firefox, SizeFilter(100, 1));
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("Only folder can filter node!", e);
    }
}

TEST_F(UtlilityTestSuite, folder_filter_by_size_between_80_and_50) {
    std::deque<Node *> results = filterNode(favorite, SizeFilter(142.56, 74));

    ASSERT_EQ(3, results.size());
    
    EXPECT_EQ("3", results[0]->id());
    EXPECT_DOUBLE_EQ(77.77, results[0]->size());

    EXPECT_EQ("9", results[1]->id());
    EXPECT_DOUBLE_EQ(94.046, results[1]->size());

    EXPECT_EQ("6", results[2]->id());
    EXPECT_DOUBLE_EQ(79.25, results[2]->size());
}

TEST_F(UtlilityTestSuite, folder_filter_by_size_between_999_and_0) {
    std::deque<Node *> results = filterNode(favorite, SizeFilter(999, 0));

    ASSERT_EQ(9, results.size());

    EXPECT_EQ("1", results[0]->id());
    EXPECT_DOUBLE_EQ(62.38, results[0]->size());

    EXPECT_EQ("2", results[1]->id());
    EXPECT_DOUBLE_EQ(1.16, results[1]->size());

    EXPECT_EQ("8", results[2]->id());
    EXPECT_DOUBLE_EQ(667.136, results[2]->size());

    EXPECT_EQ("3", results[3]->id());
    EXPECT_DOUBLE_EQ(77.77, results[3]->size());

    EXPECT_EQ("9", results[4]->id());
    EXPECT_DOUBLE_EQ(94.046, results[4]->size());

    EXPECT_EQ("5", results[5]->id());
    EXPECT_DOUBLE_EQ(14.796, results[5]->size());

    EXPECT_EQ("6", results[6]->id());
    EXPECT_DOUBLE_EQ(79.25, results[6]->size());

    EXPECT_EQ("10", results[7]->id());
    EXPECT_DOUBLE_EQ(0, results[7]->size());

    EXPECT_EQ("4", results[8]->id());
    EXPECT_DOUBLE_EQ(495.32, results[8]->size());
}


TEST_F(UtlilityTestSuite, folder_filter_by_size_equal_to_zero) {
    std::deque<Node *> results = filterNode(favorite, SizeFilter(0, 0));
    ASSERT_EQ(1, results.size());

    EXPECT_EQ("10", results[0]->id());
    EXPECT_EQ(0, results[0]->size());
}
