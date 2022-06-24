#ifndef INCLUDED_INC_PRIMITIVE_H
#define INCLUDED_INC_PRIMITIVE_H

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>

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
    //      Primitive
    // 
    //========================================================================================
    class Primitive
    {
    protected:
        ID3D11VertexShader* vertexShader;
        ID3D11PixelShader*  pixelShader;
        ID3D11InputLayout*  inputLayout;
        ID3D11Buffer*       vertexBuffer;

    public:
        Primitive(ID3D11Device* device, size_t vertexNum);
        virtual ~Primitive();

        virtual void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float width,    float height,
            float pivotX,   float pivotY,
            float rotation,
            float red, float green, float blue, float alpha
        ) = 0;

    };

    //========================================================================================
    // 
    //      PrimitiveRect
    // 
    //========================================================================================
    class PrimitiveRect : public Primitive
    {
    private:
        static constexpr size_t VERTEX_NUM = 4;

    public:
        PrimitiveRect(ID3D11Device* device) : Primitive{device, VERTEX_NUM} {}
        ~PrimitiveRect() override {}

        void Render(
            ID3D11DeviceContext* immediateContext,
            float posX,     float posY,
            float width,    float height,
            float pivotX,   float pivotY,
            float rotation,
            float red, float green, float blue, float alpha
        ) override;

    };

}

#endif // !INCLUDED_INC_PRIMITIVE_H