//------< include >---------------------------------------------------------------------- -
#include "../Inc/BinaryData.h"
#include <fstream>
#include <crtdbg.h>

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

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void BinaryData::Read(const char* resourcePath)
    {
        #ifdef C_LANGUAGE_VER
        FILE* pFile;

        // ファイルを開く
        fopen_s(
            &pFile,         // 開いたファイルのアドレスを渡すストリーム
            resourcePath,   // ファイル名
            "rb"            // モード ... 読み込み + バイナリ？
        );
        _ASSERT_EXPR_A(pFile, "Binary File not found");

        // ストリームのファイル位置を動かす
        fseek(
            pFile,      // 操作するファイル
            0L,         // オフセット
            SEEK_END    // ファイルの終わり
        );
        // ストリームのファイル位置を取得
        size = ftell(pFile);

        data = std::make_unique<char[]>(size);
        // ストリームのファイル位置を動かす
        fseek(
            pFile,
            0,
            SEEK_SET // ファイルの始め
        );


        // ファイル読み取り
        fread(
            data.get(), // 読み取ったデータの格納先
            size,       // 読み取るデータのサイズ
            1u,         // 読み取るデータの数
            pFile       // 読み取るデータ
        );
        fclose(pFile);

        #endif // C_LANGUAGE_VER

        /* 初期設定 */
        size = 0L;

        std::ifstream sFile;
        sFile.open(
            resourcePath,
            std::ios::in | std::ios::binary
        );
        _ASSERT_EXPR(sFile.is_open(), "Binary File is not found.");

        /* シークポインタを動かしサイズを取得 */
        sFile.seekg(0, std::ios::end);
        size = static_cast<long>(sFile.tellg());
        _ASSERT_EXPR(size != 0L, "Binary Size is zero.");
        sFile.seekg(0, std::ios::beg);

        /* ファイルからデータを読み取り */
        data = std::make_unique<char[]>(size);
        sFile.read(data.get(), size);

        /* ファイルからデータを読み取り */
        sFile.close();

    }
    void BinaryData::Read(const wchar_t* resourcePath)
    {
        size = 0L;

        std::ifstream sFile;
        sFile.open(
            resourcePath,
            std::ios::in | std::ios::binary
        );
        _ASSERT_EXPR(sFile.is_open(), "Binary File is not found.");

        /* シークポインタを動かしサイズを取得 */
        sFile.seekg(0, std::ios::end);
        size = static_cast<long>(sFile.tellg());
        _ASSERT_EXPR(size != 0L, "Binary Size is zero.");
        sFile.seekg(0, std::ios::beg);

        /* ファイルからデータを読み取り */
        data = std::make_unique<char[]>(size);
        sFile.read(data.get(), size);

        /* ファイルからデータを読み取り */
        sFile.close();

    }
}