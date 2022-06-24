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
        /// パスのファイル名を、指定したパス/ファイル名へ置き換える。
        /// </summary>
        /// <param name="src">元となるパス</param>
        /// <param name="dst">置き換えるパス/ファイル名</param>
        /// <returns>
        /// src=L"Data/box.obj", dst=L"box.mtl"なら、L"Data/box.mtl"を返す。
        /// L"Data/box.obj", L"tex/box.mtl"なら、L"Data/tex/box.mtl"を返す。
        /// </returns>
        std::wstring ReplaceFileName(std::wstring src, const std::wstring& dst);

    }
}

#undef USE_STRING_STREAM

#endif // !INCLUDED_STRING_MAKER_H