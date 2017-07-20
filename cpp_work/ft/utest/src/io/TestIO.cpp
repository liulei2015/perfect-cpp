#include "utest.h"
#include "l0-infra/base/BaseTypes.h"

#include <array>
#include <fstream>
#include <iostream>
#include <string>

using std::array;
using std::ifstream;
using std::string;
using std::ios;

UTESTING_NS_BEGIN

struct TestIO : testing::Test
{

};

namespace
{
    using Array_3_Char_Elem = array<char, 3>;
    using Array2D_Char = array<Array_3_Char_Elem, 3>;

    using Array_3_U32_Elem = array<U32, 3>;
    using Array2D_U32 = array<Array_3_U32_Elem, 3>;

    using Array_5_U32_Elem = array<U32, 5>;
    using Array2D_5_U32 = array<Array_5_U32_Elem, 5>;

    Array2D_Char show =
    {
        'A', 'B', 'C',
        'D', 'E', 'F',
        'G', 'H', 'I'
    };

    Array2D_Char expectedShow =
    {
        'A', 'B', 'C',
        'D', 'E', 'F',
        'G', 'H', 'I'
    };

    Array2D_U32 expectedData =
    {
        1,0,1,
        0,1,1,
        1,1,0
    };

    Array2D_5_U32 expectedData2 =
    {
        1,0,0,1,1,
        0,0,1,1,1,
        1,1,1,0,0,
        1,1,0,0,1,
        0,0,0,0,1
    };


}

TEST_F(TestIO, should_test_simple_ok)
{
    ASSERT_TRUE(show == expectedShow);
}

namespace
{
    struct SaveDataBuffer
    {
        char saveBuffer[256];
        U32 bufferRealSize;
    };

    void setSaveDataBuffer(SaveDataBuffer& saveData, char* dataAddr)
    {
        saveData.bufferRealSize = 0;
        ifstream inFile(dataAddr);

        char buffer[256];
        if(!inFile.is_open())
        {
            std::cout << "Error open file";
            exit(1);
        }
        while(!inFile.eof())
        {
            inFile.getline(buffer, 100);
            std::cout << buffer << std::endl;
            U32 temp = 0;
            while(buffer[temp] != '\0')
            {
                saveData.saveBuffer[saveData.bufferRealSize] = buffer[temp];
                temp++;
                saveData.bufferRealSize++;
            }
        }
        inFile.close();
    }
    template<typename T>
    void assignDataContainer(const SaveDataBuffer& dataBuffer, T& container, U32 rowNum)
    {
        U32 j =0;
        for(U32 i = 0; i < dataBuffer.bufferRealSize; ++i)
        {
            container[j][i%rowNum] = dataBuffer.saveBuffer[i] - '0';
            if((i+1)%rowNum == 0)
                j++;
        }
    }
}

TEST_F(TestIO, file_read_ok)
{
    SaveDataBuffer saveData;
    char* dataAddr = "/home/szdev/liulei/dev/cpp/perfect_cpp/cpp_work/ft/utest/src/io/data.txt";
    setSaveDataBuffer(saveData, dataAddr);

    Array2D_U32 dataContainer;

    assignDataContainer<Array2D_U32>(saveData, dataContainer, 3);

    ASSERT_TRUE(dataContainer == expectedData);
}

TEST_F(TestIO, file_read_data2_ok)
{
    SaveDataBuffer saveData;
    char* dataAddr = "/home/szdev/liulei/dev/cpp/perfect_cpp/cpp_work/ft/utest/src/io/data2.txt";
    setSaveDataBuffer(saveData, dataAddr);

    Array2D_5_U32 dataContainer;

    assignDataContainer<Array2D_5_U32>(saveData, dataContainer, 5);

    ASSERT_TRUE(dataContainer == expectedData2);
}

UTESTING_NS_END


