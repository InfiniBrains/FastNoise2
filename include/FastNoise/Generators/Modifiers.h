#pragma once
#include "Generator.h"

namespace FastNoise
{
    class DomainScale : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }
        void SetScale( float value ) { mScale = value; }

    protected:
        GeneratorSource mSource;
        float mScale = 1.0f;

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &DomainScale::SetSource );
                this->AddVariable( "Scale", 1.0f, &DomainScale::SetScale );
            }
        };    
    };

    class DomainOffset : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }

        template<Dim D>
        void SetOffset( float value ) { mOffset[(int)D] = value; }

        template<Dim D>
        void SetOffset( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mOffset[(int)D], gen ); }

    protected:
        GeneratorSource mSource;
        PerDimensionVariable<HybridSource> mOffset;

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &DomainOffset::SetSource );
                this->AddPerDimensionHybridSource( "Offset", 0.0f, []( DomainOffset* p ) { return std::ref( p->mOffset ); } );
            }
        };    
    };


    class DomainRotate : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }

        void SetYaw(   float value ) { mYawCos   = cosf( value ); mYawSin   = sinf( value ); CalculateRotation(); }
        void SetPitch( float value ) { mPitchCos = cosf( value ); mPitchSin = sinf( value ); CalculateRotation(); }
        void SetRoll(  float value ) { mRollCos  = cosf( value ); mRollSin  = sinf( value ); CalculateRotation(); }

    protected:
        GeneratorSource mSource;
        float mYawCos   = 1.0f;
        float mYawSin   = 0.0f;
        float mPitchCos = 1.0f;
        float mPitchSin = 0.0f;
        float mRollCos  = 1.0f;
        float mRollSin  = 0.0f;

        float mXa = 1.0f;
        float mXb = 0.0f;
        float mXc = 0.0f;
        float mYa = 0.0f;
        float mYb = 1.0f;
        float mYc = 0.0f;
        float mZa = 0.0f;
        float mZb = 0.0f;
        float mZc = 1.0f;

        void CalculateRotation()
        {
            mXa = mYawCos * mPitchCos;
            mXb = mYawCos * mPitchSin * mRollSin - mYawSin * mRollCos;
            mXc = mYawCos * mPitchSin * mRollCos + mYawSin * mRollSin;

            mYa = mYawSin * mPitchCos;
            mYb = mYawSin * mPitchSin * mRollSin + mYawCos * mRollCos;
            mYc = mYawSin * mPitchSin * mRollCos - mYawCos * mRollSin;

            mZa = -mPitchSin;
            mZb = mPitchCos * mRollSin;
            mZc = mPitchCos * mRollCos;
        }

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &DomainRotate::SetSource );
                this->AddVariable( "Yaw",   0.0f, &DomainRotate::SetYaw );
                this->AddVariable( "Pitch", 0.0f, &DomainRotate::SetPitch );
                this->AddVariable( "Roll",  0.0f, &DomainRotate::SetRoll );
            }
        };    
    };

    class SeedOffset : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }
        void SetOffset( int32_t value ) { mOffset = value; }

    protected:
        GeneratorSource mSource;
        int32_t mOffset = 1;

        FASTNOISE_METADATA( Generator )

            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &SeedOffset::SetSource );
                this->AddVariable( "Seed Offset", 1, &SeedOffset::SetOffset );
            }
        };
    };

    class Remap : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }
        void SetRemap( float fromMin, float fromMax, float toMin, float toMax ) { mFromMin = fromMin; mFromMax = fromMax; mToMin = toMin; mToMax = toMax; }

    protected:
        GeneratorSource mSource;
        float mFromMin = -1.0f;
        float mFromMax = 1.0f;
        float mToMin = 0.0f;
        float mToMax = 1.0f;

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &Remap::SetSource );

                this->AddVariable( "From Min", -1.0f,
                    []( Remap* p, float f )
                {
                    p->mFromMin = f;
                });
                
                this->AddVariable( "From Max", 1.0f,
                    []( Remap* p, float f )
                {
                    p->mFromMax = f;
                });
                
                this->AddVariable( "To Min", 0.0f,
                    []( Remap* p, float f )
                {
                    p->mToMin = f;
                });

                this->AddVariable( "To Max", 1.0f,
                    []( Remap* p, float f )
                {
                    p->mToMax = f;
                });
            }
        };    
    };

    class ConvertRGBA8 : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }
        void SetMinMax( float min, float max ) { mMin = min; mMax = max; }

    protected:
        GeneratorSource mSource;
        float mMin = -1.0f;
        float mMax = 1.0f;

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {            
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &ConvertRGBA8::SetSource );

                 this->AddVariable( "Min", -1.0f,
                    []( ConvertRGBA8* p, float f )
                {
                    p->mMin = f;
                });

                this->AddVariable( "Max", 1.0f,
                    []( ConvertRGBA8* p, float f )
                {
                    p->mMax = f;
                });
            }
        };    
    };

    class Terrace : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }
        void SetMultiplier( float multiplier ) { mMultiplier = multiplier; mMultiplierRecip = 1 / multiplier; }
        void SetSmoothness( float smoothness ) { mSmoothness = smoothness; if( mSmoothness != 0.0f ) mSmoothnessRecip = 1 + 1 / smoothness; }

    protected:
        GeneratorSource mSource;
        float mMultiplier = 1.0f;
        float mMultiplierRecip = 1.0f;
        float mSmoothness = 0.0f;
        float mSmoothnessRecip = 0.0f;

        FASTNOISE_METADATA( Generator )
        
            Metadata( const char* className ) : Generator::Metadata( className )
            {            
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &Terrace::SetSource );
                this->AddVariable( "Multiplier", 1.0f, &Terrace::SetMultiplier );
                this->AddVariable( "Smoothness", 0.0f, &Terrace::SetSmoothness );
            }
        };    
    };

    class DomainAxisScale : public virtual Generator
    {
    public:
        void SetSource( SmartNodeArg<> gen ) { this->SetSourceMemberVariable( mSource, gen ); }

        template<Dim D>
        void SetScale( float value ) { mScale[(int)D] = value; }

    protected:
        GeneratorSource mSource;
        PerDimensionVariable<float> mScale;

        FASTNOISE_METADATA( Generator )

            Metadata( const char* className ) : Generator::Metadata( className )
            {
                groups.push_back( "Modifiers" );
                this->AddGeneratorSource( "Source", &DomainAxisScale::SetSource );
                this->AddPerDimensionVariable( "Scale", 1.0f, []( DomainAxisScale* p ) { return std::ref( p->mScale ); } );
            }
        };
    };
}
