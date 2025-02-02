/*##########################################################################################

    PAX SAPIENTICA Library 💀🌿🌏

    [Planning]		2023 As Project
    [Production]	2023 As Project
    [Contact Us]	wanotaitei@gmail.com			https://github.com/AsPJT/PAX_SAPIENTICA
    [License]		Distributed under the CC0 1.0.	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#include <gtest/gtest.h>

#include <PAX_SAPIENTICA/File.hpp>

TEST (FileUnitTest, readFile) {
    const std::string file_path = "../data/test_file.txt";
    const std::vector<std::string> expected = {
        "Test",
        "file"
    };
    const std::vector<std::string> actual = paxs::File::readFile(file_path);
    ASSERT_EQ(expected, actual);
}

TEST (FileUnitTest, readCSV) {
    const std::string file_path = "../data/test_file.csv";
    const std::vector<std::vector<std::string>> expected = {
        {"Test", "file"},
        {"Test2", "file2"}
    };
    const std::vector<std::vector<std::string>> actual = paxs::File::readCSV(file_path);
    ASSERT_EQ(expected, actual);
}

TEST (FileUnitTest, readTSV) {
    const std::string file_path = "../data/test_file.tsv";
    const std::vector<std::vector<std::string>> expected = {
        {"Test", "file"},
        {"Test2", "file2"}
    };
    const std::vector<std::vector<std::string>> actual = paxs::File::readTSV(file_path);
    ASSERT_EQ(expected, actual);
}

TEST (FileUnitTest, getFileNames) {
    const std::string file_path = "../data";
    const std::vector<std::string> expected = {
        file_path + "/test_file.csv",
        file_path + "/test_file.tsv",
        file_path + "/test_file.txt"
    };
    std::vector<std::string> actual = paxs::File::getFileNames(file_path);

    std::sort(actual.begin(), actual.end());
    
    ASSERT_EQ(expected, actual);

}
