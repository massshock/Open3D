// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "open3d/utility/IJsonConvertible.h"

#include <json/json.h>

#include "tests/UnitTest.h"

namespace open3d {
namespace tests {

// ----------------------------------------------------------------------------
// Test the conversion of Eigen::Vector3d to and from JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenVector3dToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Vector3d v3d = Eigen::Vector3d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Vector3d ref;

        status = utility::IJsonConvertible::EigenVector3dToJsonArray(
                v3d, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenVector3dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, v3d);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of Eigen::Vector4d to and from JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenVector4dToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Vector4d v4d = Eigen::Vector4d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Vector4d ref;

        status = utility::IJsonConvertible::EigenVector4dToJsonArray(
                v4d, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenVector4dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, v4d);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of Eigen::Matrix3d to and from JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenMatrix3dToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Matrix3d m3d = Eigen::Matrix3d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Matrix3d ref;

        status = utility::IJsonConvertible::EigenMatrix3dToJsonArray(
                m3d, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenMatrix3dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, m3d);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of Eigen::Matrix4d to and from JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenMatrix4dToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Matrix4d m4d = Eigen::Matrix4d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Matrix4d ref;

        status = utility::IJsonConvertible::EigenMatrix4dToJsonArray(
                m4d, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenMatrix4dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, m4d);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of unaligned Eigen::Matrix4d to and from
// JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenMatrix4d_uToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Matrix4d_u m4d_u = Eigen::Matrix4d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Matrix4d_u ref;

        status = utility::IJsonConvertible::EigenMatrix4dToJsonArray(
                m4d_u, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenMatrix4dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, m4d_u);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of Eigen::Matrix6d to and from JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenMatrix6dToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Matrix6d m6d = Eigen::Matrix6d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Matrix6d ref;

        status = utility::IJsonConvertible::EigenMatrix6dToJsonArray(
                m6d, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenMatrix6dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, m6d);
    }
}

// ----------------------------------------------------------------------------
// Test the conversion of unaligned Eigen::Matrix6d to and from
// JsonArray.
// ----------------------------------------------------------------------------
TEST(IJsonConvertible, EigenMatrix6d_uToFromJsonArray) {
    int loops = 10000;
    srand((unsigned int)time(0));
    for (int i = 0; i < loops; i++) {
        Eigen::Matrix6d_u m6d_u = Eigen::Matrix6d::Random();

        bool status = false;
        Json::Value json_value;
        Eigen::Matrix6d_u ref;

        status = utility::IJsonConvertible::EigenMatrix6dToJsonArray(
                m6d_u, json_value);
        EXPECT_TRUE(status);

        status = utility::IJsonConvertible::EigenMatrix6dFromJsonArray(
                ref, json_value);
        EXPECT_TRUE(status);

        ExpectEQ(ref, m6d_u);
    }
}

}  // namespace tests
}  // namespace open3d
