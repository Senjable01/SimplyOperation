#ifndef INCLUDED_INC_BINARY_DATA_H
#define INCLUDED_INC_BINARY_DATA_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <memory>
#include <string>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //========================================================================================
    // 
    //      BinaryData
    // 
    //========================================================================================
    class BinaryData
    {
    private:
        std::unique_ptr<char[]> data;   // バイナリデータ
        long size;                      // バイナリデータサイズ

    public:
        BinaryData() : data{nullptr}, size{0L} {}
        BinaryData(const char* resourcePath) : data{nullptr}, size{0L}
        {
            Read(resourcePath);
        }
        BinaryData(const wchar_t* resourcePath) : data{nullptr}, size{0L}
        {
            Read(resourcePath);
        }

        void Read(const char* resourcePath);
        void Read(const wchar_t* resourcePath);

        const char* Data() const noexcept {return data.get();}
        long Size() const noexcept {return size;}

        operator bool() { return 0L < size; }

    };

}

#endif // !INCLUDED_INC_BINARY_DATA_H