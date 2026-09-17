#ifndef LUCID_DRIFT_VECCOL_H
#define LUCID_DRIFT_VECCOL_H


namespace LDDrift
{
    class VecCol final
    {
    public:
        float R{}, G{}, B{}, A{};
        VecCol();
        VecCol(float red, float green, float blue, float alpha);
        void Red();
        void Green();
        void Blue();
        void Yellow();
        void Orange();
        void Purple();
        void White();
        void Black();
        void SetColor(const float& red, const float& green, const float& blue, const float& alpha);
        ~VecCol();
    };
}


#endif
