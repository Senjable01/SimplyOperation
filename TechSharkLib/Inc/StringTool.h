#ifndef INCLUDED_STRING_MAKER_H
#define INCLUDED_STRING_MAKER_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< macro >-------------------------------------------------------------------------

#define USE_STRING_STREAM 1

//------< include >-----------------------------------------------------------------------
#include <sstream>
#include <string>
#include <utility>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    namespace string
    {
        //========================================================================================
        // 
        //      WideStringMaker
        // 
        //========================================================================================
        class WideStringMaker
        {
        private:
            #if USE_STRING_STREAM
            std::wstringstream wStrStream;

            #else
            std::wstring wString;

            #endif // USE_STRING_STREAM
            void Input() {}

        public:
            WideStringMaker() : 
                #if USE_STRING_STREAM
                wStrStream{}
                #else
                wString{L""}
                #endif // USE_STRING_STREAM
            {
            }
            template<typename Arg, typename... Args> void Input(Arg arg, Args&&... args)
            {
                #if USE_STRING_STREAM
                wStrStream << arg;

                #else
                wString += std::to_wstring<Arg>(arg);

                #endif // USE_STRING_STREAM
                Input(std::forward<Args>(args)...);
            }
            std::wstring Output()
            {
                #if USE_STRING_STREAM
                std::wstring output = wStrStream.str();

                #else
                std::wstring output = wString;

                #endif // USE_STRING_STREAM
                Clear();
                return output;
            }
            void Clear()
            {
                #if USE_STRING_STREAM
                wStrStream.clear(std::wstringstream::goodbit);
                wStrStream.str(L"");

                #else
                wString.clear();

                #endif // USE_STRING_STREAM

            }
            void LineBreak()
            {
                wStrStream << std::endl;
            }

        };

        //------< function >----------------------------------------------------------------------

        /// <summary>
        /// �p�X�̃t�@�C�������A�w�肵���p�X/�t�@�C�����֒u��������B
        /// </summary>
        /// <param name="src">���ƂȂ�p�X</param>
        /// <param name="dst">�u��������p�X/�t�@�C����</param>
        /// <returns>
        /// src=L"Data/box.obj", dst=L"box.mtl"�Ȃ�AL"Data/box.mtl"��Ԃ��B
        /// L"Data/box.obj", L"tex/box.mtl"�Ȃ�AL"Data/tex/box.mtl"��Ԃ��B
        /// </returns>
        std::wstring ReplaceFileName(std::wstring src, const std::wstring& dst);

    }
}

#undef USE_STRING_STREAM

#endif // !INCLUDED_STRING_MAKER_H