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

        // �t�@�C�����J��
        fopen_s(
            &pFile,         // �J�����t�@�C���̃A�h���X��n���X�g���[��
            resourcePath,   // �t�@�C����
            "rb"            // ���[�h ... �ǂݍ��� + �o�C�i���H
        );
        _ASSERT_EXPR_A(pFile, "Binary File not found");

        // �X�g���[���̃t�@�C���ʒu�𓮂���
        fseek(
            pFile,      // ���삷��t�@�C��
            0L,         // �I�t�Z�b�g
            SEEK_END    // �t�@�C���̏I���
        );
        // �X�g���[���̃t�@�C���ʒu���擾
        size = ftell(pFile);

        data = std::make_unique<char[]>(size);
        // �X�g���[���̃t�@�C���ʒu�𓮂���
        fseek(
            pFile,
            0,
            SEEK_SET // �t�@�C���̎n��
        );


        // �t�@�C���ǂݎ��
        fread(
            data.get(), // �ǂݎ�����f�[�^�̊i�[��
            size,       // �ǂݎ��f�[�^�̃T�C�Y
            1u,         // �ǂݎ��f�[�^�̐�
            pFile       // �ǂݎ��f�[�^
        );
        fclose(pFile);

        #endif // C_LANGUAGE_VER

        /* �����ݒ� */
        size = 0L;

        std::ifstream sFile;
        sFile.open(
            resourcePath,
            std::ios::in | std::ios::binary
        );
        _ASSERT_EXPR(sFile.is_open(), "Binary File is not found.");

        /* �V�[�N�|�C���^�𓮂����T�C�Y���擾 */
        sFile.seekg(0, std::ios::end);
        size = static_cast<long>(sFile.tellg());
        _ASSERT_EXPR(size != 0L, "Binary Size is zero.");
        sFile.seekg(0, std::ios::beg);

        /* �t�@�C������f�[�^��ǂݎ�� */
        data = std::make_unique<char[]>(size);
        sFile.read(data.get(), size);

        /* �t�@�C������f�[�^��ǂݎ�� */
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

        /* �V�[�N�|�C���^�𓮂����T�C�Y���擾 */
        sFile.seekg(0, std::ios::end);
        size = static_cast<long>(sFile.tellg());
        _ASSERT_EXPR(size != 0L, "Binary Size is zero.");
        sFile.seekg(0, std::ios::beg);

        /* �t�@�C������f�[�^��ǂݎ�� */
        data = std::make_unique<char[]>(size);
        sFile.read(data.get(), size);

        /* �t�@�C������f�[�^��ǂݎ�� */
        sFile.close();

    }
}