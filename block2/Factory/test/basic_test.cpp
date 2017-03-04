//
// Created by moonlightnvkz on 18.02.17.
//
#include <string>
#include <tuple>
#include <experimental/tuple>
#include <gtest/gtest.h>

extern "C" {
#include "../src/new.h"
#include "../src/objects.h"
}

using namespace std;

static testing::AssertionResult is_output_equal(void *obj, const char *msg) {
    testing::internal::CaptureStdout();
    draw(obj);
    std::string output = testing::internal::GetCapturedStdout();
    if (output == msg) {
        return testing::AssertionSuccess();
    } else {
        return testing::AssertionFailure();
    }
}

TEST(Draw_Test, Draw_Test_Point_Draw__Test) {
    void *p = new_2(Point, 1, 2);
    ASSERT_TRUE(is_output_equal(p, "point at 1,2\n"));
    delete_2(p);
}

TEST(Draw_Test, Draw_Test_Circle_Draw__Test) {
    void *p = new_2(Circle, 1, 2, 3);
    ASSERT_TRUE(is_output_equal(p, "circle at 1,2 rad 3\n"));
    delete_2(p);
}

TEST(Draw_Test, Draw_Test_Rect_Draw__Test) {
    void *p = new_2(Rect, 1, 2, 3, 4);
    ASSERT_TRUE(is_output_equal(p, "rect at 1,2 width 3 height 4\n"));
    delete_2(p);
}

TEST(Draw_Test, Draw_Test_Line_Draw__Test) {
    void *p = new_2(Line, 1, 2, 3, 4);
    ASSERT_TRUE(is_output_equal(p, "line from 1,2 to 3,4\n"));
    delete_2(p);
}

