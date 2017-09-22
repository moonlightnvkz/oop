//
// Created by akarpovskii on 18.09.17.
//

#include <gtest/gtest.h>
#include <functional>
#include "../include/ObjectPool.hpp"

class TestObject {
public:
    TestObject() {
        ++Constructed;
        ptr = new char;
    }

    ~TestObject() {
        ++Destructed;
        delete ptr;
    }

    static int Constructed;

    static int Destructed;
private:
    char *ptr;
};

int TestObject::Constructed = 0;

int TestObject::Destructed = 0;

class ObjectPoolTest : public ::testing::Test {
    void SetUp() override {
        TestObject::Constructed = TestObject::Destructed = 0;
    }
};

TEST_F(ObjectPoolTest, ZeroObjPool) {
    ObjectPool<TestObject> pool(0);
    EXPECT_TRUE(pool.isFull());
    EXPECT_THROW(pool.alloc(), ObjectPoolIsFull);
    TestObject obj;
    EXPECT_THROW(pool.free(obj), std::invalid_argument);
}

TEST_F(ObjectPoolTest, AllocObjTest) {
    ObjectPool<TestObject> pool(2);

    EXPECT_FALSE(pool.isFull());

    EXPECT_NO_THROW(pool.alloc());

    EXPECT_FALSE(pool.isFull());

    EXPECT_NO_THROW(pool.alloc());

    EXPECT_TRUE(pool.isFull());

    EXPECT_THROW(pool.alloc(), ObjectPoolIsFull);

    EXPECT_TRUE(pool.isFull());

    EXPECT_EQ(TestObject::Constructed, 2);
}

TEST_F(ObjectPoolTest, FreeObjTest) {
    ObjectPool<TestObject> pool(2);

    TestObject &obj1 = pool.alloc();
    TestObject &obj2 = pool.alloc();

    auto another_obj = new TestObject;
    EXPECT_THROW(pool.free(*another_obj), std::invalid_argument);
    delete another_obj;

    EXPECT_NO_THROW(pool.free(obj1));
    EXPECT_FALSE(pool.isFull());
    EXPECT_NO_THROW(pool.free(pool.alloc()));
    EXPECT_NO_THROW(pool.free(obj2));
    EXPECT_FALSE(pool.isFull());
    EXPECT_EQ(TestObject::Constructed, TestObject::Destructed);
}

TEST_F(ObjectPoolTest, HundredObjFreeEachTest) {
    ObjectPool<TestObject> pool(100);
    std::vector<std::reference_wrapper<TestObject>> objects;
    for (int i = 0; i < 100; ++i) {
        objects.push_back(std::ref(pool.alloc()));
    }
    for (int i = 0; i < 100; ++i) {
        pool.free(objects[i]);
    }
    EXPECT_EQ(TestObject::Constructed, TestObject::Destructed);
}

TEST_F(ObjectPoolTest, HundredObjDeletePoolTest) {
    auto *pool = new ObjectPool<TestObject>(100);
    std::vector<std::reference_wrapper<TestObject>> objects;
    for (int i = 0; i < 100; ++i) {
        objects.push_back(std::ref(pool->alloc()));
    }
    delete(pool);
    EXPECT_EQ(TestObject::Constructed, TestObject::Destructed);
}